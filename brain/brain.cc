
#include <iostream>

#include "robot.hh"

using std::cout;
using std::endl;

void
callback(Robot* robot)
{
    cout << "main callback" << endl;
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
