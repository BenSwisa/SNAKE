#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    { // servo_cmd_topic
      publisher_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("joint_cmd_topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
      
    }

  private:
    void timer_callback()
    {
      if(arr[0]>450) arr[0]=100;
      arr[0]= arr[0]+30;
      auto message = std_msgs::msg::Float32MultiArray();
      message.data = {0,0,0,0,0,0,0,0,0,0,0,0};
    //   message.data[0]=arr[0];
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data[0]);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_;
    size_t count_;
    int arr[12]={0,50,0,0,0,0,0,0,0,0,0,0};
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}