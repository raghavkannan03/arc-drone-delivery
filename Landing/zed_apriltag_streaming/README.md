# ZED → Jetson → Laptop AprilTag Detection Pipeline

Production deployment guide for:

- **Jetson + ZED** → Camera + H264 RTP streaming  
- **Laptop (Ubuntu)** → RTP decode + OpenCV + AprilTag + Pose  

Designed for autonomous landing and precision navigation workflows.

---

# 1. System Architecture

```
ZED Camera
     ↓
Jetson (H264 encode + RTP UDP stream)
     ↓
WiFi / Ethernet
     ↓
Laptop (OpenCV decode + AprilTag + Pose)
```

### Responsibility Split

| Machine | Responsibility |
|----------|----------------|
| Jetson | Camera driver + hardware encoding |
| Laptop | RTP decode + AprilTag + Pose |
| Drone (future) | PX4 landing control |

---

# 2. Machine Setup

## 2.1 On the Jetson (Streamer)

### Step 1 — Find IP Addresses

On Jetson:
```bash
ip a
```

On laptop:
```bash
ip a
```

Record:

```
<JETSON_IP>
<LAPTOP_IP>
```

---

### Step 2 — Start ZED RTP Stream (Jetson)

#### Option A — Using ARC Streaming Script

```bash
cd arc-drone-delivery/streaming
./start_stream.sh <LAPTOP_IP>
```

#### Option B — Manual GStreamer

```bash
gst-launch-1.0 zedsrc ! \
video/x-raw,width=1280,height=720,framerate=15/1 ! \
omxh264enc ! rtph264pay ! \
udpsink host=<LAPTOP_IP> port=5000
```

or:
```bash
gst-launch-1.0 -v \
  zedsrc ! \
  video/x-raw,width=1280,height=720,framerate=15/1 ! \
  videoconvert ! \
  video/x-raw,format=I420 ! \
  x264enc tune=zerolatency speed-preset=ultrafast bitrate=4000 key-int-max=30 ! \
  rtph264pay config-interval=1 pt=96 mtu=1200! \
  udpsink host=<LAPTOP_IP> port=5000 sync=false async=false
```

This sends video to:

```
udp://<LAPTOP_IP>:5000
```

---

# 3. Laptop Setup (Detection + Pose)

## 3.1 Build (First Time Only)

```bash
unzip zed_apriltag_streaming_laptop_ready.zip
cd zed_apriltag_streaming

./scripts/setup_ubuntu.sh
./scripts/build.sh
```

---

# 4. Verify Networking (Critical Step)

Before running detection:

```bash
vlc udp://@:5000
```
or,
```bash
unset SESSION_MANAGER
```
then run this in the streaming directory to run streaming
```bash
vlc ./zed.sdp
```

If video appears:
- Networking is correct
- RTP stream is valid

Close VLC before running detection.

If nothing appears:

```bash
sudo ufw allow 5000/udp
ping <JETSON_IP>
```

Recommended:
- Same subnet
- No VPN
- 5GHz WiFi or Ethernet

---

# 5. Run AprilTag Detection (Laptop)

## 5.1 Stream Mode (Jetson → Laptop)

```bash
./build/zed_apriltag --port 5000
```

Connects to:

```
udp://@:5000
```

---

## 5.2 Pose Estimation Mode (Recommended)

```bash
./build/zed_apriltag \
  --port 5000 \
  --calib assets/your_calibration.yaml \
  --tag-size 0.162
```

### Parameters

| Argument | Description |
|----------|------------|
| `--calib` | Camera intrinsics YAML |
| `--tag-size` | Physical tag size (meters) |

### Output

- Tag ID
- Translation vector (`tvec`)
- Rotation vector (`rvec`)

Suitable for:
- Precision landing
- Drone-relative pose estimation
- SLAM integration

---

# 6. Laptop-Only Testing Mode

Useful for development without Jetson.

## 6.1 Webcam

```bash
./build/zed_apriltag --device 0
```

## 6.2 Video File

```bash
./build/zed_apriltag --video test.mp4
```

## 6.3 Pose with Webcam

```bash
./build/zed_apriltag \
  --device 0 \
  --calib assets/calibration.yaml \
  --tag-size 0.162
```

---

# 7. Clean Deployment Launch Order

1. Start stream on Jetson  
2. Confirm video with VLC on laptop  
3. Close VLC  
4. Run `zed_apriltag` on laptop  

---

# 8. Calibration Notes

For accurate pose estimation:

- Use ZED factory intrinsics or recalibrate
- Include distortion coefficients
- Measure tag size precisely (meters)

Pose error scales linearly with tag-size error.

---

# 9. Directory Structure

```
zed_apriltag_streaming/
├── CMakeLists.txt
├── include/
├── src/
│   └── main.cpp
├── assets/
│   └── calibration.yaml
├── scripts/
│   ├── setup_ubuntu.sh
│   ├── build.sh
│   ├── run_webcam.sh
│   ├── run_video.sh
│   └── run_udp.sh
└── README.md
```

---

# 10. Future Integrations

- ROS2 publisher node for pose
- MAVLink bridge to PX4
- Precision landing controller
- NTP time synchronization
- EKF fusion with VIO / GPS

---

# End of Deployment Guide