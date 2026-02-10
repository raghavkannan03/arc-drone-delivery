# Onboarding C++ AprilTag Detection

## Final Goal

A new team member can:

1. Stream the **ZED camera** from the Jetson over UDP (as defined in this repo: [https://github.com/purdue-arc/arc-drone-delivery/blob/main/streaming/README.md](https://github.com/purdue-arc/arc-drone-delivery/blob/main/streaming/README.md))
2. Ingest that stream **directly into OpenCV**
3. Run **C++ AprilTag detection**
4. Visualize detections live (ID + outline, optional pose)

### How it works

```jsx
Jetson Orin Nano (ZED)
 └─ GStreamer (H264 / RTP / UDP)
        ↓
Viewing Laptop
 └─ OpenCV VideoCapture (GStreamer backend)
        ↓
 C++ AprilTag Detector
```

VLC for Debugging

## Prerequisites (viewing computer)

OS: Ubuntu 22.04 (native, or WSL2 with GUI)

```bash
sudo apt update
sudo apt install -y \
  build-essential cmake git pkg-config \
  libopencv-dev \
  libeigen3-dev \
  gstreamer1.0-tools \
  gstreamer1.0-libav \
  gstreamer1.0-plugins-{base,good,bad,ugly}
```

Verify:

```bash
opencv_version
gst-launch-1.0 --version
```

## 1. Start the ZED UDP Stream (Jetson)

This is the pipeline from the streaming repo:

```bash
gst-launch-1.0 zedsrc stream-type=0 camera-resolution=3 ! \
video/x-raw, width=1280, height=720, framerate=15/1 ! videoconvert ! \
x264enc tune=zerolatency bitrate=1500 speed-preset=veryfast key-int-max=15 ! \
h264parse ! rtph264pay config-interval=1 pt=96 ! \
udpsink host=<VIEWING_COMPUTER_IP> port=5000 sync=false async=false
```

**Important notes:**

- `h264parse` ensures SPS/PPS headers (OpenCV needs this)
- `config-interval=1` sends headers repeatedly (critical)
- `sync=false` avoids latency buildup

## 2. Confirm streaming works

```bash
gst-launch-1.0 \
udpsrc port=5000 caps="application/x-rtp,media=video,encoding-name=H264,payload=96" ! \
rtph264depay ! avdec_h264 ! videoconvert ! autovideosink
```

If this does not work there are networking problems. Troubleshoot those first before proceeding.

## 3. OpenCV Pipeline

**GStreamer → OpenCV**

```cpp
std::string pipeline =
  "udpsrc port=5000 caps=application/x-rtp,media=video,encoding-name=H264,payload=96 ! "
  "rtph264depay ! avdec_h264 ! videoconvert ! appsink drop=1";
```

**Minimal Stream Viewer (C++)**

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::string pipeline =
      "udpsrc port=5000 caps=application/x-rtp,media=video,encoding-name=H264,payload=96 ! "
      "rtph264depay ! avdec_h264 ! videoconvert ! appsink drop=1";

    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open stream\n";
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::imshow("ZED Stream", frame);
        if (cv::waitKey(1) == 27) break;
    }
}
```

**Milestone:** If this runs, streaming is working.

## 4. AprilTag (C++)

### Library Choice

Use the **official apriltag C library** (UMich).

Clone:

```bash
git clone [https://github.com/AprilRobotics/apriltag.git](https://github.com/AprilRobotics/apriltag.git)
```

## 5. AprilTag detection pipeline (per frame)

- Convert frame → grayscale
- Wrap `cv::Mat` into `image_u8_t`
- Detect
- Draw results

### Core Detection Code (Inside Loop)

```cpp
cv::Mat gray;
cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

image_u8_t img = {
    .width = gray.cols,
    .height = gray.rows,
    .stride = gray.cols,
    .buf = gray.data
};

zarray_t* detections = apriltag_detector_detect(td, &img);

for (int i = 0; i < zarray_size(detections); i++) {
    apriltag_detection_t* det;
    zarray_get(detections, i, &det);

    // Draw outline
    for (int j = 0; j < 4; j++) {
        cv::line(frame,
            cv::Point(det->p[j][0], det->p[j][1]),
            cv::Point(det->p[(j+1)%4][0], det->p[(j+1)%4][1]),
            {0, 255, 0}, 2);
    }

    cv::putText(frame,
        std::to_string(det->id),
        cv::Point(det->c[0], det->c[1]),
        cv::FONT_HERSHEY_SIMPLEX, 0.6, {0,255,0}, 2);
}

apriltag_detections_destroy(detections);
```

## 6. CMake.txt

```cpp
cmake_minimum_required(VERSION 3.10)
project(zed_apriltag)

find_package(OpenCV REQUIRED)

add_subdirectory(apriltag)

add_executable(zed_apriltag main.cpp)
target_include_directories(zed_apriltag PRIVATE apriltag)
target_link_libraries(zed_apriltag apriltag ${OpenCV_LIBS})
```

## 7. Expected Performance

| Component | Value |
| --- | --- |
| Resolution | 1280×720 |
| FPS | ~15 |
| Latency | ~150–300 ms |
| Detection Rate | Real-time (CPU OK) |

If CPU becomes tight:

- Detect every **N frames**
- Reduce resolution to 960×540
- Use `tag36h11` only

## Goals:

- ZED stream visible via `gst-launch`
- OpenCV receives frames
- AprilTag IDs drawn correctly
- Code builds with one `cmake && make`

## Quick Start Example Repo

### 1) Install Dependencies

```bash
sudo apt update
sudo apt install -y \
  build-essential cmake git pkg-config \
  libopencv-dev libeigen3-dev \
  gstreamer1.0-tools gstreamer1.0-libav \
  gstreamer1.0-plugins-{base,good,bad,ugly}
```