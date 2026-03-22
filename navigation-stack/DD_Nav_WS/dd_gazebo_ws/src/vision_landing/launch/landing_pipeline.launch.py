from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='vision_landing',
            executable='apriltag_detector',
            name='apriltag_detector',
            output='screen'
        ),
        Node(
            package='vision_landing',
            executable='pose_estimator',
            name='pose_estimator',
            output='screen'
        ),
        Node(
            package='vision_landing',
            executable='landing_controller',
            name='landing_controller',
            output='screen'
        ),
	Node(
	    package='vision_landing',
	    executable='mission_controller',
	    name='landing_controler',
	    output='screen'
	)
    ])
