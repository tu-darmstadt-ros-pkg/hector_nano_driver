/*
 * NOTE: Type of imu has to be defined in inv_mpu.h
 */

#include "freeram.h"

#include "mpu.h"
#include "I2Cdev.h"

#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

void blinkCb(const std_msgs::Bool& msg);

ros::NodeHandle nh;

//geometry_msgs::Quaternion quat_msg;
//ros::Publisher quat_pub("quaternion", &quat_msg);
std_msgs::Float32 gas_msg;
ros::Publisher gas_pub("co2", &gas_msg);

ros::Subscriber<std_msgs::Bool> blink_sub("blink", &blinkCb);

int ret;
void setup() {
  //  Fastwire::setup(400,0);
  //  ret = mympu_open(200);

  nh.initNode();

  nh.subscribe(blink_sub);

  nh.advertise(gas_pub);

}

unsigned int c = 0; //cumulative number of successful MPU/DMP reads
unsigned int np = 0; //cumulative number of MPU/DMP reads that brought no packet back
unsigned int err_c = 0; //cumulative number of MPU/DMP reads that brought corrupted packet
unsigned int err_o = 0; //cumulative number of MPU/DMP reads that had overflow bit set

void loop() {

    nh.spinOnce();
/*
    ret = mympu_update();

    switch (ret) {
    case 0: c++; break;
    case 1: np++; return;
    case 2: err_o++; return;
    case 3: err_c++; return;
    default:
        return;
    }

    quat_msg.w = mympu.quat.w;
    quat_msg.x = mympu.quat.x;
    quat_msg.y = mympu.quat.y;
    quat_msg.z = mympu.quat.z;

    quat_pub.publish(&quat_msg);
*/
    gas_msg.data = 1.0 * analogRead(0);

    gas_pub.publish(&gas_msg);
}

void blinkCb(const std_msgs::Bool& msg){
    digitalWrite(13, msg.data);   // blink the led
}
