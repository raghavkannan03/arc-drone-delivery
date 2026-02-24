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