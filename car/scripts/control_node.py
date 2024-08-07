#!/usr/bin/env python
#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64
from geometry_msgs.msg import Twist

def control_joint():
    rospy.init_node('control_joint_node', anonymous=False)
    joint1_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(10) # 10 Hz

    while not rospy.is_shutdown():
        position = 1.0  # Example position
        rospy.loginfo("Setting joint1 position to {position}")
        joint1_pub.publish(position)
        rate.sleep()

if __name__ == '__main__':
    try:
        control_joint()
    except rospy.ROSInterruptException:
        pass