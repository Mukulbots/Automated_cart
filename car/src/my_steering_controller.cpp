#include <ros/ros.h>
#include <pluginlib/class_loader.h>
#include <controller_manager/controller_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <sensor_msgs/JointState.h>

namespace my_robot_controllers
{
  class MySteeringController : public controller_manager::ControllerInterface
  {
  public:
    MySteeringController() : gain_(0.1) {} // Adjust gain as needed

    bool init(controller_manager::ControllerManager* cm) override
    {
      // Get joint handles
      joint_steering_ = cm->getJointHandle("steeringJoint");
      if (!joint_steering_)
      {
        ROS_ERROR("Failed to get handle for steering_joint");
        return false;
      }

      // Subscribe to joint states (optional)
      joint_state_sub_ = cm->nh().subscribe("/joint_states", 10, &MySteeringController::jointStateCallback, this);

      return true;
    }

    void update(ros::Time now, ros::Duration period) override
    {
      // Get desired steering command from a source (e.g., subscriber, parameter)
      double desired_steering_command = 0.0; // Replace with your control logic

      // Calculate control output
      double control_output = gain_ * desired_steering_command;

      // Set joint command
      joint_steering_->setCommand(control_output);
    }

  private:
    void jointStateCallback(const sensor_msgs::JointStateConstPtr& msg)
    {
      // Use joint state information if needed
    }

    hardware_interface::JointHandle* joint_steering_;
    ros::Subscriber joint_state_sub_;
    double gain_;
  };
}

PLUGINLIB_EXPORT_CLASS(my_robot_controllers::MySteeringController, controller_manager::ControllerInterface)
