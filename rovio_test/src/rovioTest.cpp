#include "ros/ros.h"
#include "rovio_base/manDrv.h"
#include "rovio_base/image.h"
#include "rovio_base/report.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rovioTest");
  ros::NodeHandle n;
  ros::ServiceClient imageClient = n.serviceClient<rovio_base::image>("rovioImage");
  ros::ServiceClient controlClient = n.serviceClient<rovio_base::manDrv>("rovioControl");
  ros::ServiceClient reportClient = n.serviceClient<rovio_base::report>("rovioReport");
  rovio_base::image imageSrv;
  rovio_base::manDrv controlSrv;
  rovio_base::report reportSrv;

  // Head middle control
  controlSrv.request.drive = 13;
  controlSrv.request.speed = 9;
  if (controlClient.call(controlSrv))
  {
    ROS_INFO("Control response code: %d", (int )controlSrv.response.code);
  }
  else
  {
    ROS_ERROR("Failed to call service rovioControl");
    return 1;
  }

  // Get report info
  if (reportClient.call(reportSrv))
  {
    int length = reportSrv.response.length;
    int lDirection = reportSrv.response.lDirection;
    int lNum = reportSrv.response.lNum;
    int rDirection = reportSrv.response.rDirection;
    int rNum = reportSrv.response.rNum;
    int rearDirection = reportSrv.response.rearDirection;
    int rearNum = reportSrv.response.rearNum;
    int headPosition = reportSrv.response.headPosition;
    bool isLedOn = reportSrv.response.isLedOn;
    bool isIrOn = reportSrv.response.isIrOn;
    bool isDetectedBarrier = reportSrv.response.isDetectedBarrier;
    ROS_INFO("MCU Report:\nlength=%d", length);
    ROS_INFO("Left direction:num=%d:%d", lDirection, lNum);
    ROS_INFO("Right direction:num=%d:%d", rDirection, rNum);
    ROS_INFO("Rear direction:num=%d:%d", rearDirection, rearNum);
    ROS_INFO("headPosition=%d", headPosition);
    ROS_INFO("isLedOn=%d,isIrOn=%d,isDetectedBarrier=%d", isLedOn, isIrOn, isDetectedBarrier);
  }
  else
  {
    ROS_ERROR("Failed to call service rovioReport");
    return 1;
  }

  // Show images from camera
  for (int i = 0; i < 20; i++)
  {
    if (imageClient.call(imageSrv))
    {
      ROS_INFO("Image size: %dx%d", (int )imageSrv.response.img.width, (int )imageSrv.response.img.height);
      cv_bridge::CvImagePtr cvImgPtr;
      try
      {
        cvImgPtr = cv_bridge::toCvCopy(imageSrv.response.img, sensor_msgs::image_encodings::BGR8);
        cv::imshow("", cvImgPtr->image);
        cv::waitKey(100);
      }
      catch (cv_bridge::Exception& e)
      {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return 1;
      }
    }
    else
    {
      ROS_ERROR("Failed to call service rovioImage");
      return 1;
    }
  }

  // Head down control
  controlSrv.request.drive = 12;
  controlSrv.request.speed = 9;
  if (controlClient.call(controlSrv))
  {
    ROS_INFO("Control response code: %d", (int )controlSrv.response.code);
  }
  else
  {
    ROS_ERROR("Failed to call service rovioControl");
    return 1;
  }

  return 0;
}
