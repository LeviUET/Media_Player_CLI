#ifndef _HARDWARE_CONTROLLER_HPP_
#define _HARDWARE_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "../model/application.hpp"
#include "media_player_controller.hpp"
#include "../view/general_view.hpp"
#include "../controller/general_controller.hpp"

class HardwareController {
    public:
        static int   uart_init(const char* port);
        static void  uart_receive_thread(Application& _app, int fd);  
};

#endif // _HARDWARE_CONTROLLER_HPP_