#include "cli.hpp"
#include "apriltag_detector.hpp"
#include "calibration.hpp"

#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <cmath>

static bool intrinsics_sane(const CameraIntrinsics& intr) {
  return intr.fx > 0.0 && intr.fy > 0.0 && intr.cx >= 0.0 && intr.cy >= 0.0;
}

static cv::Matx33d camera_matrix(const CameraIntrinsics& intr) {
  return cv::Matx33d(
      intr.fx, 0.0, intr.cx,
      0.0, intr.fy, intr.cy,
      0.0, 0.0, 1.0);
}

static void draw_pose_axes(cv::Mat& frame,
                           const TagDetection& d,
                           const CameraIntrinsics& intr,
                           double tag_size_m) {
  if (!d.has_pose || !intrinsics_sane(intr) || tag_size_m <= 0.0) return;

  const double axis_len = 0.5 * tag_size_m;
  std::vector<cv::Point3d> object_pts{
      {0.0, 0.0, 0.0},
      {axis_len, 0.0, 0.0},
      {0.0, axis_len, 0.0},
      {0.0, 0.0, axis_len},
  };

  cv::Mat rmat(3, 3, CV_64F);
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      rmat.at<double>(r, c) = d.R(r, c);
    }
  }
  cv::Mat rvec;
  cv::Rodrigues(rmat, rvec);

  cv::Mat tvec(3, 1, CV_64F);
  tvec.at<double>(0, 0) = d.t[0];
  tvec.at<double>(1, 0) = d.t[1];
  tvec.at<double>(2, 0) = d.t[2];

  std::vector<cv::Point2d> img_pts;
  cv::projectPoints(
      object_pts, rvec, tvec, camera_matrix(intr), cv::noArray(), img_pts);
  if (img_pts.size() != 4) return;

  cv::line(frame, img_pts[0], img_pts[1], cv::Scalar(0, 0, 255), 2);   // x (red)
  cv::line(frame, img_pts[0], img_pts[2], cv::Scalar(0, 255, 0), 2);   // y (green)
  cv::line(frame, img_pts[0], img_pts[3], cv::Scalar(255, 0, 0), 2);   // z (blue)
}

static void draw_detection(cv::Mat& frame, const TagDetection& d) {
  for (int i = 0; i < 4; i++) {
    cv::line(frame, d.p[i], d.p[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
  }
  cv::circle(frame, d.center, 4, cv::Scalar(0, 255, 0), -1);

  std::string label = d.family + ":" + std::to_string(d.id);
  if (d.has_pose) {
    double dist = std::sqrt(d.t[0]*d.t[0] + d.t[1]*d.t[1] + d.t[2]*d.t[2]);
    label += " dist=" + std::to_string(dist).substr(0,5) + "m";
    label += " err=" + std::to_string(d.reproj_err).substr(0,5);
  }

  cv::putText(frame, label, d.center + cv::Point2d(8, -8),
              cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,255,0), 2);
}

static cv::VideoCapture open_capture(const CliOptions& opt) {
  if (opt.source == InputSourceType::V4L2_DEVICE) {
    cv::VideoCapture cap(opt.device_index);
    return cap;
  }
  if (opt.source == InputSourceType::VIDEO_FILE) {
    cv::VideoCapture cap(opt.video_path);
    return cap;
  }
  // Default: GST pipeline
  cv::VideoCapture cap(opt.gst_pipeline, cv::CAP_GSTREAMER);
  return cap;
}

int main(int argc, char** argv) {
  CliOptions opt;
  try { opt = parse_cli(argc, argv); }
  catch (const std::exception& e) { std::cerr << e.what() << "\n"; return 2; }

  if (opt.show_help) { std::cout << help_text(); return 0; }

  cv::VideoCapture cap = open_capture(opt);
  if (!cap.isOpened()) {
    std::cerr << "Failed to open input.\n";
    if (opt.source == InputSourceType::GST_PIPELINE) {
      std::cerr << "Tried OpenCV+GStreamer pipeline:\n  " << opt.gst_pipeline << "\n";
      std::cerr << "Tip: verify decode with:\n"
                   "  gst-launch-1.0 udpsrc port=5000 caps=\"application/x-rtp,media=video,encoding-name=H264,payload=96\" ! "
                   "rtph264depay ! avdec_h264 ! videoconvert ! autovideosink\n";
    } else if (opt.source == InputSourceType::V4L2_DEVICE) {
      std::cerr << "Tried device index: " << opt.device_index << " (e.g., /dev/video" << opt.device_index << ")\n";
    } else {
      std::cerr << "Tried video file: " << opt.video_path << "\n";
    }
    return 1;
  }

  AprilTagDetector detector;
  detector.configure(opt.family, opt.threads, opt.decimate, opt.blur, opt.refine_edges);

  std::optional<CameraIntrinsics> intr;
  if (opt.calib_path) {
    intr = load_intrinsics_yaml(*opt.calib_path);
    if (!intr) {
      std::cerr << "Failed to load intrinsics from: " << *opt.calib_path << "\n";
    } else {
      std::cerr << "Loaded intrinsics from " << *opt.calib_path
                << " fx=" << intr->fx << " fy=" << intr->fy
                << " cx=" << intr->cx << " cy=" << intr->cy;
      if (intr->width > 0 && intr->height > 0) {
        std::cerr << " size=" << intr->width << "x" << intr->height;
      }
      std::cerr << "\n";
    }
  }

  // Allow --fx/--fy/--cx/--cy without --calib.
  if (!intr && (opt.fx || opt.fy || opt.cx || opt.cy)) intr = CameraIntrinsics{};
  if (intr) {
    if (opt.fx) intr->fx = *opt.fx;
    if (opt.fy) intr->fy = *opt.fy;
    if (opt.cx) intr->cx = *opt.cx;
    if (opt.cy) intr->cy = *opt.cy;
  }

  const bool have_intr = intr && intrinsics_sane(*intr);
  if (have_intr && opt.tag_size_m) {
    detector.enable_pose(intr->fx, intr->fy, intr->cx, intr->cy, *opt.tag_size_m);
    std::cerr << "Pose enabled (fx,fy,cx,cy)=(" << intr->fx << "," << intr->fy << ","
              << intr->cx << "," << intr->cy << "), tag=" << *opt.tag_size_m << "m\n";
  } else if (opt.tag_size_m && !have_intr) {
    std::cerr << "Tag size provided but intrinsics missing. Use --calib or --fx/--fy/--cx/--cy.\n";
  }

  cv::Mat frame, gray;
  using clock = std::chrono::steady_clock;
  auto last = clock::now();
  double fps = 0.0;
  bool warned_intrinsics_size = false;

  while (true) {
    if (!cap.read(frame) || frame.empty()) {
      // For files, this usually means EOF.
      if (opt.source == InputSourceType::VIDEO_FILE) break;
      cv::waitKey(1);
      continue;
    }

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    auto dets = detector.detect(gray);
    for (const auto& d : dets) {
      draw_detection(frame, d);
      if (have_intr && opt.tag_size_m) {
        draw_pose_axes(frame, d, *intr, *opt.tag_size_m);
      }
    }

    if (!warned_intrinsics_size && intr && intr->width > 0 && intr->height > 0 &&
        (intr->width != frame.cols || intr->height != frame.rows)) {
      std::cerr << "Warning: calibration size " << intr->width << "x" << intr->height
                << " does not match frame size " << frame.cols << "x" << frame.rows << "\n";
      warned_intrinsics_size = true;
    }

    if (opt.show_fps) {
      auto now = clock::now();
      double dt = std::chrono::duration<double>(now - last).count();
      last = now;
      double inst = dt > 0 ? 1.0 / dt : 0.0;
      fps = 0.9 * fps + 0.1 * inst;
      cv::putText(frame, ("FPS: " + std::to_string(fps).substr(0,5)),
                  cv::Point(20,40), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                  cv::Scalar(255,255,255), 2);
    }

    cv::imshow("AprilTag (Pose)", frame);
    int k = cv::waitKey(1);
    if (k == 27 || k == 'q') break;
  }

  return 0;
}
