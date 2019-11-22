#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SpinProblem{
  private:
    std::shared_ptr< rclcpp::Publisher <std_msgs::msg::String> > chatter;
    void listen_thread(rclcpp::Node::SharedPtr node){

	  auto subscription = node->create_subscription<std_msgs::msg::String>(
		"listener",
		10,
		[&](const std_msgs::msg::String::SharedPtr msg) ->void {
		  RCLCPP_INFO(node->get_logger(), "I heard: '%s'", msg->data.c_str());
		}
	  );
	
	  rclcpp::spin(node);

    }
  public:
    SpinProblem(){
      auto node = rclcpp::Node::make_shared("test");
      std::thread(&SpinProblem::listen_thread, this,node).detach();
      chatter = node->create_publisher<std_msgs::msg::String>("spin_problem", rclcpp::QoS(10));
    }

    void send_something(){
      std_msgs::msg::String msg;
  
      msg.data = "send something";
  
      chatter->publish(msg);
    }
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  std::unique_ptr<SpinProblem> spinProblem = std::make_unique<SpinProblem>();

  spinProblem->send_something();

  rclcpp::Rate sleepRate(1s);
  int counter=0;

  while(counter==0){
    sleepRate.sleep();
    std::cout<<"doing something simulator"<<std::endl;
    counter++;
  }
  spinProblem->send_something();
  

  std::cout<<"end code"<<std::endl;
}
