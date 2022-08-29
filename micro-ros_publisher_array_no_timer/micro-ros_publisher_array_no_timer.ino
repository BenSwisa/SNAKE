#include <micro_ros_arduino.h>


#include <stdio.h>
#include <stdlib.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>


#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32_multi_array.h>

#include <std_msgs/msg/multi_array_dimension.h>
#include <std_msgs/msg/multi_array_layout.h>

//---
#include <micro_ros_utilities/type_utilities.h>
std_msgs__msg__Float32MultiArray msg_sensors;
//static micro_ros_utilities_memory_conf_t conf = {0};
//---

rcl_publisher_t publisher;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

#define LED_PIN 13

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}


void error_loop(){
  while(1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

//-------------- TIMER FUNCTION -------------
void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
      
    //create msg memory

   static float memory[3]; 
   msg_sensors.data.capacity = 3;
//   msg_sensors.data.data = (float*) malloc(msg_sensors.data.capacity * sizeof(float));
  msg_sensors.data.data = memory;
   msg_sensors.data.size = 2;

   msg_sensors.data.data[0]=1;  
   msg_sensors.data.data[1]=54;  
  
    //-----enter the data and publish -------

    //    msg_sensors.data.data[1]=4;
    RCSOFTCHECK(rcl_publish(&publisher, &msg_sensors, NULL));

//   //free memory
//     free(msg_sensors.data.data);
  }
}

void setup() {
  set_microros_transports();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  
  
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
   ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
    "micro_ros_arduino_node_publisher"));

  // create timer,
//  const unsigned int timer_timeout = 1000;
//  RCCHECK(rclc_timer_init_default(
//    &timer,
//    &support,
//    RCL_MS_TO_NS(timer_timeout),
//    timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  


  
}

void loop() {
  delay(100);
   //create msg memory

   static float memory[3]; 
   msg_sensors.data.capacity = 3;
//   msg_sensors.data.data = (float*) malloc(msg_sensors.data.capacity * sizeof(float));
  msg_sensors.data.data = memory;
   msg_sensors.data.size = 2;

   msg_sensors.data.data[0]=1;  
   msg_sensors.data.data[1]=54;  
  
    //-----enter the data and publish -------

    //    msg_sensors.data.data[1]=4;
    RCSOFTCHECK(rcl_publish(&publisher, &msg_sensors, NULL));
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
