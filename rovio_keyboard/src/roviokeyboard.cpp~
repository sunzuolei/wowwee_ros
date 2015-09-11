    #include <termios.h>  
    #include <signal.h>  
    #include <math.h>  
    #include <stdio.h>  
    #include <stdlib.h>  
    #include <sys/poll.h>  


#include "rovio_base/manDrv.h"
//#include "rovio_base/image.h"
//#include "rovio_base/report.h"
      
    #include <boost/thread/thread.hpp>  
    #include <ros/ros.h>  
    #include <geometry_msgs/Twist.h>  
      
    #define KEYCODE_W 0x77  
    #define KEYCODE_A 0x61  
    #define KEYCODE_S 0x73  
    #define KEYCODE_D 0x64  
      
    #define KEYCODE_A_CAP 0x41  
    #define KEYCODE_D_CAP 0x44  
    #define KEYCODE_S_CAP 0x53  
    #define KEYCODE_W_CAP 0x57  



    class roviokeyboardTeleopNode
    {  
        private:  
            double walk_vel_;  
            double run_vel_;  
            double yaw_rate_;  
            double yaw_rate_run_;  
              
            geometry_msgs::Twist cmdvel_;  
            ros::NodeHandle n_;  
            ros::Publisher pub_;  
      
        public:  
            roviokeyboardTeleopNode()
            {  
                pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 1);  
                  
                ros::NodeHandle n_private("~");  
                n_private.param("walk_vel", walk_vel_, 0.5);
                n_private.param("run_vel", run_vel_, 1.0);  
                n_private.param("yaw_rate", yaw_rate_, 1.0);  
                n_private.param("yaw_rate_run", yaw_rate_run_, 1.5);  
            }  
              
            ~roviokeyboardTeleopNode() { }
            void keyboardLoop();  
              
            void stopRobot()  
            {  
                cmdvel_.linear.x = 0.0;  
                cmdvel_.angular.z = 0.0;  
                pub_.publish(cmdvel_);  
            }  
    };  
      
    roviokeyboardTeleopNode* tbk;
    int kfd = 0;  
    struct termios cooked, raw;  
    bool done;  


   // ros::NodeHandle key;
   // ros::ServiceClient imageClient = key.serviceClient<rovio_base::image>("rovioImage");
   // ros::ServiceClient controlClient = key.serviceClient<rovio_base::manDrv>("rovioControl");
   // ros::ServiceClient reportClient = key.serviceClient<rovio_base::report>("rovioReport");
   // rovio_base::image imageSrv;
  //  rovio_base::manDrv controlSrv;
   // rovio_base::report reportSrv;

    int main(int argc, char** argv)  
    {  
       // ros::init(argc,argv,"roviokeyboard");
        ros::init(argc,argv,"tbk", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler);  

        roviokeyboardTeleopNode tbk;

        ros::NodeHandle key;
        ros::ServiceClient controlClient = key.serviceClient<rovio_base::manDrv>("rovioControl");
        rovio_base::manDrv controlSrv;

        boost::thread t = boost::thread(boost::bind(&roviokeyboardTeleopNode::keyboardLoop, &tbk));

        if (controlClient.call(controlSrv))
        {
          ROS_INFO("Control response code: %d", (int )controlSrv.response.code);
          ROS_INFO("%d",(int)controlSrv.request.drive);
          ROS_INFO("%d",(int)controlSrv.request.speed);
        }
        else
        {
          ROS_ERROR("Failed to call service rovioControl");
          return 1;
        }
          
        ros::spin();  
          
        t.interrupt();  
        t.join();  
        tbk.stopRobot();  
        tcsetattr(kfd, TCSANOW, &cooked);  
          
        return(0);  
    }  
      
    void roviokeyboardTeleopNode::keyboardLoop()
    {  
        char c;  
        double max_tv = walk_vel_;  
        double max_rv = yaw_rate_;  
        bool dirty = false;  
        int speed = 0;  
        int turn = 0;  


        ros::NodeHandle key;
        ros::ServiceClient controlClient = key.serviceClient<rovio_base::manDrv>("rovioControl");
        rovio_base::manDrv controlSrv;

          
        // get the console in raw mode  
        tcgetattr(kfd, &cooked);  
        memcpy(&raw, &cooked, sizeof(struct termios));  
        raw.c_lflag &=~ (ICANON | ECHO);  
        raw.c_cc[VEOL] = 1;  
        raw.c_cc[VEOF] = 2;  
        tcsetattr(kfd, TCSANOW, &raw);  
          
        puts("Reading from keyboard");  
        puts("Use WASD keys to control the robot");  
        puts("Press Shift to move faster");  
          
        struct pollfd ufd;  
        ufd.fd = kfd;  
        ufd.events = POLLIN;  
          
        for(;;)  
        {  
            boost::this_thread::interruption_point();  
              
            // get the next event from the keyboard  
            int num;  
              
            if ((num = poll(&ufd, 1, 250)) < 0)  
            {  
                perror("poll():");  
                return;  
            }  
            else if(num > 0)  
            {  
                if(read(kfd, &c, 1) < 0)  
                {  
                    perror("read():");  
                    return;  
                }  
            }  
            else  
            {  
                if (dirty == true)  
                {  
                    stopRobot();  
                    dirty = false;  
                }  
                  
                continue;  
            }  
              
            switch(c)  
            {  
                case KEYCODE_W:  
                    max_tv = walk_vel_;  
                    controlSrv.request.drive = 1;
                    controlSrv.request.speed = 9;
                  //  speed = 1;
                    turn = 0;  
                    dirty = true;  
                    break;  
                case KEYCODE_S:  
                    controlSrv.request.drive = 2;
                    controlSrv.request.speed = 9;
                    max_tv = walk_vel_;  
                    speed = -1;  
                    turn = 0;  
                    dirty = true;  
                    break;  
                case KEYCODE_A:
                   controlSrv.request.drive = 3;
                   controlSrv.request.speed = 9;
                    max_rv = yaw_rate_;  
                    speed = 0;  
                    turn = 1;  
                    dirty = true;  
                    break;  
                case KEYCODE_D:  
                  controlSrv.request.drive = 4;
                   controlSrv.request.speed = 9;
                    max_rv = yaw_rate_;  
                    speed = 0;  
                    turn = -1;  
                    dirty = true;  
                    break;  
                      
                case KEYCODE_W_CAP:  
                    max_tv = run_vel_;  
                    speed = 1;  
                    turn = 0;  
                    dirty = true;  
                    break;  
                case KEYCODE_S_CAP:  
                    max_tv = run_vel_;  
                    speed = -1;  
                    turn = 0;  
                    dirty = true;  
                    break;  
                case KEYCODE_A_CAP:  
                    max_rv = yaw_rate_run_;  
                    speed = 0;  
                    turn = 1;  
                    dirty = true;  
                    break;  
                case KEYCODE_D_CAP:  
                    max_rv = yaw_rate_run_;  
                    speed = 0;  
                    turn = -1;  
                    dirty = true;  
                    break;                
                default:  
                    max_tv = walk_vel_;  
                    max_rv = yaw_rate_;  
                    speed = 0;  
                    turn = 0;  
                    dirty = false;  
            }  
            cmdvel_.linear.x = speed * max_tv;  
            cmdvel_.angular.z = turn * max_rv;  
           // pub_.publish(cmdvel_);
            controlClient.call(controlSrv);
        }  
    }  
