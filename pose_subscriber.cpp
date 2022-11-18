/***********************************************************************
Copyright 2020 GuYueHome (www.guyuehome.com).
***********************************************************************/

/**
 * 该例程将订阅/turtle1/pose话题，消息类型turtlesim::Pose
 */
 
#include <ros/ros.h>
#include "turtlesim/Pose.h"
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"

double spd=0;
geometry_msgs::Twist vel2_msg;
ros::Subscriber pose_sub;
ros::Publisher turtle_vel2_pub;


void pub(double spd);

// 接收到订阅的消息后，会进入消息回调函数
void Callback(const geometry_msgs::Twist& msg)
{
    // 将接收到的消息打印出来
    
    spd=msg.linear.x;
    ROS_INFO("Current velocity:[%0.2f m/s]",spd);
    ROS_INFO("Publish turtle velocity command[%0.2f m/s]", 
                spd);

}

void pub(double spd){
    vel2_msg.linear.x=spd;
    // turtle_vel2_pub.publish(vel2_msg);
    // printf("Publish turtle velocity command[%0.2f m/s]", 
    //             spd); 
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "velocity_subscriber");
    ros::NodeHandle n2;
    ros::Rate loop_rate(5);
    pose_sub = n2.subscribe("/turtle1/cmd_vel", 1000, Callback);
    turtle_vel2_pub = n2.advertise<geometry_msgs::Twist>("cmd_vel1", 1000);
    turtle_vel2_pub.publish(vel2_msg);
    

    ROS_INFO("Node handle created");
    while (ros::ok()){
        // 创建一个Subscriber，订阅名为/turtle1/pose的topic，注册回调函数poseCallback
        loop_rate.sleep();
        // 循环等待回调函数
        ros::spinOnce();
    }
    

    

    

    return 0;
}
