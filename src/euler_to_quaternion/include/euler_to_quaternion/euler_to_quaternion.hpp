#pragma once
#include"rclcpp/rclcpp.hpp"
#include"euler_to_quaternion_interface/msg/my_euler.hpp"
#include"euler_to_quaternion_interface/msg/my_quaternion.hpp"
#include<cmath>
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/msg/quaternion.hpp"
#include"geometry_msgs/msg/transform_stamped.hpp"
#include<string>
class EulerToQuaternion: public rclcpp::Node
{
    private:
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf2_broadcaster;
    rclcpp::Subscription<euler_to_quaternion_interface::msg::MyEuler>::SharedPtr Subscriber;
    rclcpp::Publisher<euler_to_quaternion_interface::msg::MyQuaternion>::SharedPtr Publisher;
    void callback_euler(const euler_to_quaternion_interface::msg::MyEuler::SharedPtr msg);
    void callback_quaternion(const euler_to_quaternion_interface::msg::MyEuler::SharedPtr msg);
    void print_tf(geometry_msgs::msg::Quaternion quat);
    void print_tf2(geometry_msgs::msg::Quaternion quat);
    public:
    EulerToQuaternion(std::string name);
};