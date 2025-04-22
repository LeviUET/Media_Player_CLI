#ifndef _HARDWARE_VIEW_HPP_
#define _HARDWARE_VIEW_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "../model/application.hpp"

class HardwareView {
    public:
        static void generateHardwareView(Application& _app);
};  

#endif // _HARDWARE_VIEW_HPP_