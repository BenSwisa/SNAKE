#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"



using std::placeholders::_1;
// using std::placeholders::_2;
// using std::placeholders::_3;

 
class Node1 : public rclcpp::Node // MODIFY NAME
{
public:
    Node1() : Node("node1") // MODIFY NAME
    {
     RCLCPP_INFO(this->get_logger(), "Node1 has been started.");
     joint_val_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "joint_val_topic", 10, std::bind(&Node1::joint_val_callback, this, _1));
    tension_val_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "tension_val_topic", 10, std::bind(&Node1::tension_val_callback, this, _1));
    joint_cmd_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "joint_cmd_topic", 10, std::bind(&Node1::joint_cmd_callback, this, _1));
     motor_cmd_publisher_ = this->create_publisher<std_msgs::msg::Int16MultiArray>("motor_cmd_topic",10);
     timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(1000)),
                                         std::bind(&Node1::publish_motor_pwm ,this)); //publish motor cmd every second  
     
    }

 
private:
    void publish_motor_pwm(){
        auto message = std_msgs::msg::Int16MultiArray();
        message.data={1,0,0};
        motor_cmd_publisher_->publish(message);

    }

    void joint_val_callback(const std_msgs::msg::Float32MultiArray msg){
     RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }

    void joint_cmd_callback(const std_msgs::msg::Float32MultiArray msg){
     RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }
    
    void tension_val_callback(const std_msgs::msg::Float32MultiArray msg){
     RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }
    
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_val_subscriber_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr tension_val_subscriber_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_cmd_subscriber_;
    rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr motor_cmd_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Node1>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}