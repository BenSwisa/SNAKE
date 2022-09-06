#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"



using std::placeholders::_1;
// using std::placeholders::_2;
// using std::placeholders::_3;

 
class Node1 : public rclcpp::Node 
{
public:
    Node1() : Node("node1") 
    {
     RCLCPP_INFO(this->get_logger(), "Node1 has been started.");
     joint_val_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "joint_val_topic", 10, std::bind(&Node1::joint_val_callback, this, _1));
    tension_val_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "tension_val_topic", 10, std::bind(&Node1::tension_val_callback, this, _1));
    joint_cmd_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "joint_cmd_topic", 10, std::bind(&Node1::joint_cmd_callback, this, _1));
     motor_cmd_publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("motor_cmd_topic",10);
    //  timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(1000)),
    //                                      std::bind(&Node1::publish_motor_pwm ,this)); //publish motor cmd every second  
     
    }

 
private:
    void publish_motor_pwm(int *arr){
        auto message = std_msgs::msg::Int32MultiArray();
        message.data={0,0,0,0,0,0,0,0,0,0,0,0};
        for(int i=0;i<12;i++){
        message.data[i]=arr[i];
        }
        motor_cmd_publisher_->publish(message);

    }

    void joint_val_callback(const std_msgs::msg::Float32MultiArray msg){
      RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }

    void joint_cmd_callback(const std_msgs::msg::Float32MultiArray msg){
      RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
      auto message = std_msgs::msg::Int32MultiArray();
        message.data={0,0,0,0,0,0,0,0,0,0,0,0};
        for(int i=0;i<12;i++){
        message.data[i]=(int32_t)msg.data[i];
        }
        motor_cmd_publisher_->publish(message);
    }
    
    void tension_val_callback(const std_msgs::msg::Float32MultiArray msg){
     RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }
    
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_val_subscriber_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr tension_val_subscriber_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_cmd_subscriber_;
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr motor_cmd_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Node1>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}