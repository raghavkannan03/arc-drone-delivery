cmake_minimum_required(VERSION 3.16)

project(zed_apriltag_streaming
  VERSION 0.2.0
  DESCRIPTION "ZED UDP/RTP (H264) stream ingest with OpenCV + AprilTag detection + pose (C++)"
  LANGUAGES C CXX
)

option(ZAS_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Pose is enabled by default in this repo; it activates at runtime when intrinsics+tag-size are provided.
add_compile_definitions(ZAS_ENABLE_POSE=1)

# other build setup (find_package, FetchContent) happens before we declare the
# target so that dependencies are available when linking later.

find_package(OpenCV REQUIRED)

include(FetchContent)

set(APRILTAG_SOURCE_DIR "" CACHE PATH "Path to a local apriltag checkout (optional)")
if (APRILTAG_SOURCE_DIR AND EXISTS "${APRILTAG_SOURCE_DIR}/CMakeLists.txt")
  message(STATUS "Using local apriltag from: ${APRILTAG_SOURCE_DIR}")
  add_subdirectory("${APRILTAG_SOURCE_DIR}" apriltag_build)
else()
  FetchContent_Declare(
    apriltag
    GIT_REPOSITORY https://github.com/AprilRobotics/apriltag.git
    GIT_TAG        master
  )
  FetchContent_MakeAvailable(apriltag)
endif()


add_executable(zed_apriltag
  src/main.cpp
  src/zed_gst_pipeline.cpp
  src/zed_gst_pipeline.hpp
  src/apriltag_detector.cpp
  src/apriltag_detector.hpp
  src/cli.cpp
  src/cli.hpp
  src/calibration.cpp
  src/calibration.hpp
)

target_include_directories(zed_apriltag PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(zed_apriltag PRIVATE apriltag ${OpenCV_LIBS})

# enable warnings once the target exists
include(cmake/CompilerWarnings.cmake)
zas_enable_warnings(zed_apriltag ${ZAS_WARNINGS_AS_ERRORS})

message(STATUS "OpenCV version: ${OpenCV_VERSION}")
 