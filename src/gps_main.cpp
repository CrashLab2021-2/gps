#include <iostream>
#include "gps.cpp"
#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

using namespace std;

int main(int argc,char **argv){
	ros::init(argc,argv,"GPS_LORA");
	ros::NodeHandle nh;
	ros::Publisher gps_pub = nh.advertise<sensor_msgs::NavSatFix>("/gps", 1);
	sensor_msgs::NavSatFix gps_msg;

	Serial gps("/dev/ttyUSB0",9600);
	if(!gps.good){
		ROS_INFO("GPS ERROR");
		return 0;
	}
	
	ROS_INFO("START NODE");
	int count = 0;
	vector<float> gps_data;
    while(ros::ok()){
				if(gps.good){
					ROS_INFO("[%d count]",count++);
					gps_data = get_gps(gps);
					if(gps_data.size()){
						gps_msg.latitude = gps_data[1];
						gps_msg.longitude = gps_data[2];
						gps_msg.altitude = gps_data[3];
						gps_msg.header.stamp = ros::Time::now();
						gps_pub.publish(gps_msg);
					}
				}
	}
    return 0; // success
}
