#ifndef _HOME_CONTROLLER_HPP_
#define _HOME_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h> 
#include "../model/application.hpp"
#include "../view/general_view.hpp"
#include "../controller/playmusic_controller.hpp"
#include "../controller/media_player_controller.hpp"
#include "../controller/playlist_controller.hpp"
#include "../controller/edit_metadata_controller.hpp"
#include "../controller/edit_metadata_menu_controller.hpp"
#include "../controller/hardware_controller.hpp"

class GeneralController {
    public:
        static void   executeState(Application& _app);
};

#endif // _HOME_CONTROLLER_HPP_