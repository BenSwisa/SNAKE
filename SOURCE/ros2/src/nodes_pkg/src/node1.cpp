#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"



using std::placeholders::_1;

 
class Node1 : public rclcpp::Node // MODIFY NAME
{
public:
    Node1() : Node("node1") // MODIFY NAME
    {
     RCLCPP_INFO(this->get_logger(), "Node1 has been started.");
     joint_val_subscriber_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "joint_val_topic", 10, std::bind(&Node1::joint_val_callback, this, _1));
     
    }

 
private:
    void joint_val_callback(const std_msgs::msg::Float32MultiArray msg){
     RCLCPP_INFO(this->get_logger(), " %f , %f \n",msg.data[0],msg.data[1]);
    }
    
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_val_subscriber_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Node1>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}