from concurrent.futures import Executor
from http.server import executable
from launch import LaunchDescription
from launch_ros.actions import Node
# from launch_ros.actions import ExecuteProcess
import launch
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression




def generate_launch_description():
    record = LaunchConfiguration('record')
    ld = LaunchDescription()

    node1 = Node(
        package="nodes_pkg",
        executable="node1"
 
    )


    bag_ex =launch.actions.ExecuteProcess(
        condition=IfCondition(
            PythonExpression([
                record])
        ),
            cmd=['ros2', 'bag', 'record', '/joint_val_topic'],
            output='screen'
        )
    
    bag_ex_launch_arg = launch.actions.DeclareLaunchArgument(
        'record',
        default_value='False'
    )

    ld.add_action(node1)
    ld.add_action(bag_ex_launch_arg)
    ld.add_action(bag_ex)

    return ld



# def generate_launch_description():
#     return launch.LaunchDescription([
#         launch.actions.ExecuteProcess(
#             cmd=['ros2', 'bag', 'record', '-a'],
#             output='screen'
#         ),
#         launch_ros.actions.Node(
#             package='nodes_pkg',
#             executable='node1'
#         )   
#     ])