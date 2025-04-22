#ifndef _GENERAL_VIEW_HPP_
#define _GENERAL_VIEW_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"
#include "../view/home_view.hpp"
#include "../view/playmusic_view.hpp"
#include "../view/display_song_view.hpp"
#include "../view/media_player_view.hpp"
#include "../view/playlist_view.hpp"
#include "../view/edit_metadata_view.hpp"
#include "../view/edit_metadata_menu_view.hpp"
#include "../view/hardware_view.hpp"

class GeneralView {
    public:
        static void generateView(Application& _app);
        static char getChoice();
};

#endif // _GENERAL_VIEW_HPP_