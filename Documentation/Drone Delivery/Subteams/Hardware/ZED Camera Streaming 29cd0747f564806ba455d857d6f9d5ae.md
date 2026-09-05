# ZED Camera Streaming

Filepath for reciever/sender example on the Jetson: `computer/usr/local/zed/samples/camera streaming`

[https://www.stereolabs.com/docs/gstreamer/20_zed-camera-source#h264-streaming-over-udp-on-local-network](https://www.stereolabs.com/docs/gstreamer/20_zed-camera-source#h264-streaming-over-udp-on-local-network)

remove the resolution arguments to get video streaming from both left and right cameras

on receiving computer:

install gstreamer 

sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

install gstreamer post processing `sudo apt-get install gstreamer1.0-vaapi`

command on jetson (replace ip address with that of the receiving computer)

```bash
gst-launch-1.0 zedsrc ! timeoverlay ! tee name=split has-chain=true ! \
 queue ! autovideoconvert ! fpsdisplaysink \
 split. ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! autovideoconvert ! \
 x264enc byte-stream=true tune=zerolatency speed-preset=ultrafast bitrate=3000 ! \
 h264parse ! rtph264pay config-interval=-1 pt=96 ! queue ! \
 udpsink clients=192.168.1.169:5000 max-bitrate=3000000 sync=false async=false
```

command on receiving computer:

```bash
gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,clock-rate=90000,payload=96 !  queue ! rtph264depay ! h264parse ! avdec_h264 !  queue ! autovideoconvert ! fpsdisplaysink
```

Jetson Orin has hardware limitations— we cannot use the streaming example, but will use Gstreamer