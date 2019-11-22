#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

int main(int argc, char** argv){
	rclcpp::init(argc, argv);
	
	auto node = rclcpp::Node::make_shared("listen_test");

	auto subscription = node->create_subscription<std_msgs::msg::String>(
		"spin_problem",
		10,
		[&](const std_msgs::msg::String::SharedPtr msg) ->void {
		  RCLCPP_INFO(node->get_logger(), "I heard: '%s'", msg->data.c_str());
		}
	);
	
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}
