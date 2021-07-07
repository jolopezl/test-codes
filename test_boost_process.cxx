#include <chrono>
#include <iostream>
#include <boost/process/child.hpp>
#include <boost/process/spawn.hpp>

int main()
{
    boost::process::spawn("/opt/X11/bin/glxgears");
    /*
    boost::process::child c("/opt/X11/bin/glxgears");
    if (c.running()) {
        std::cout << "process is running" << std::endl;
    }
    auto t = std::chrono::seconds(10);
    c.wait_for(t);
    c.detach();
    c.terminate();
    */
    return 1;
}
