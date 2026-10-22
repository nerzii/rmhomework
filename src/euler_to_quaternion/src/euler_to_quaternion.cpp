#include"rclcpp/rclcpp.hpp"
#include"euler_to_quaternion/euler_to_quaternion.hpp"
#include"euler_to_quaternion_interface/msg/my_euler.hpp"
#include"euler_to_quaternion_interface/msg/my_quaternion.hpp"
#include<cmath>
#include"tf2_ros/transform_broadcaster.h"
#include"geometry_msgs/msg/quaternion.hpp"
#include"geometry_msgs/msg/transform_stamped.hpp"
#include<string>
void EulerToQuaternion::callback_quaternion( const euler_to_quaternion_interface::msg::MyEuler::SharedPtr msg )
{  
    euler_to_quaternion_interface::msg::MyQuaternion quater; 
    geometry_msgs::msg::Quaternion quat;
    quater.x =sin(msg->roll/2)*cos(msg->pitch/2)*cos(msg->yaw/2)-cos(msg->roll/2)*sin(msg->pitch/2)*sin(msg->yaw/2);
    quater.y =cos(msg->roll/2)*sin(msg->pitch/2)*cos(msg->yaw/2)+sin(msg->roll/2)*cos(msg->pitch/2)*sin(msg->yaw/2);
    quater.z =cos(msg->roll/2)*cos(msg->pitch/2)*sin(msg->yaw/2)-sin(msg->roll/2)*sin(msg->pitch/2)*cos(msg->yaw/2);
    quater.w =cos(msg->roll/2)*cos(msg->pitch/2)*cos(msg->yaw/2)-sin(msg->roll/2)*sin(msg->pitch/2)*sin(msg->yaw/2);
    Publisher->publish(quater);
    quat.x = quater.x;
    quat.y = quater.y;
    quat.z = quater.z;
    quat.w = quater.w;
    this->print_tf(quat);
    this->print_tf2(quat);
}
void EulerToQuaternion::callback_euler(const euler_to_quaternion_interface::msg::MyEuler::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(),"我已经收到欧拉角消息");
    callback_quaternion(msg);
}
void EulerToQuaternion::print_tf(geometry_msgs::msg::Quaternion quat)
{
        geometry_msgs::msg::TransformStamped transform;
        transform.header.frame_id = "map";
        transform.child_frame_id = "A";
        transform.header.stamp = rclcpp::Clock().now();
        transform.transform.translation.x = 0.0;
        transform.transform.translation.y = 0.0;
        transform.transform.translation.z = 0.0;
        transform.transform.rotation = quat;
        tf2_broadcaster->sendTransform(transform);
}
void EulerToQuaternion::print_tf2(geometry_msgs::msg::Quaternion quat)
{
        geometry_msgs::msg::TransformStamped transform;
        transform.header.frame_id = "map";
        transform.child_frame_id = "B";
        transform.header.stamp = rclcpp::Clock().now();
        transform.transform.translation.x = 1.0;
        transform.transform.translation.y = 1.0;
        transform.transform.translation.z = 2.0;
        transform.transform.rotation = quat;
        tf2_broadcaster->sendTransform(transform);
}
EulerToQuaternion::EulerToQuaternion(std::string name) : Node(name)
{
    Subscriber = this->create_subscription<euler_to_quaternion_interface::msg::MyEuler>
    (
        "euler",
        10,
        [this](const euler_to_quaternion_interface::msg::MyEuler::SharedPtr msg)
        {
            this->callback_euler(msg);
        }
    );
    Publisher = this->create_publisher<euler_to_quaternion_interface::msg::MyQuaternion>
    (
        "quaternion",
        10
    );  
    tf2_broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(this);
};
int main(int argc, char** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<EulerToQuaternion>("euler_to_quaternion_node"));
    rclcpp::shutdown();
}


