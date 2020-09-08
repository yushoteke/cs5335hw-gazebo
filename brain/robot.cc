#include <iostream>
#include <string>
#include <vector>

#include "robot.hh"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace gazebo;
using namespace gazebo::transport;

Robot::Robot(int argc, char* argv[], void (*cb)(Robot*))
    : on_update(cb)
{
    client::setup(argc, argv);
    node = NodePtr(new Node());
    node->Init();

    turn_pub = node->Advertise<msgs::Any>("~/teapot0/turn_cmd");
    turn_pub->WaitForConnection();

    vel_pub = node->Advertise<msgs::Any>("~/teapot0/vel_cmd");
    vel_pub->WaitForConnection();

    scan_sub = node->Subscribe(
        string("~/teapot0/teapot/rplidar_a2/link/laser/scan"),
        &Robot::on_scan,
        this,
        false
    );

    pose_sub = node->Subscribe(
        string("~/teapot0/pose"),
        &Robot::on_pose,
        this,
        false
    );

    cout << "robot created" << endl;
}

Robot::~Robot()
{
    client::shutdown();
    cout << "robot destroyed" << endl;
}

void
Robot::wait()
{
    while (true) {
        node->ProcessIncoming();
        gazebo::common::Time::MSleep(10);
    }
}

void
Robot::set_vel(double vel)
{
    auto msg = msgs::ConvertAny(vel);
    vel_pub->Publish(msg);
}

void
Robot::set_turn(double turn)
{
    auto msg = msgs::ConvertAny(turn);
    turn_pub->Publish(msg);
}

void
Robot::on_scan(ConstLaserScanStampedPtr &msg)
{
    cout << "got on_scan" << endl;
    msgs::LaserScan scan = msg->scan();

    auto xs = scan.ranges();
    cout << "xs.size = " << xs.size() << endl;

    float min_val = 999.0;
    long  min_idx = 0;
    for (long ii = 0; ii < xs.size(); ++ii) {
        float xx = xs[ii];
        if (xx < min_val) {
            min_val = xs[ii];
            min_idx = ii;
        }
    }

    cout << "min val = " << min_val << " @ " << min_idx << endl;
}
