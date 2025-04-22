#ifndef _PLAYMUSIC_CONTROLLER_HPP_
#define _PLAYMUSIC_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"
#include "../view/playmusic_view.hpp"

class PlayMusicController {
    public:
        static void playMusicinFolder(Application& _app);
        static void playMusicinPlaylist(Application& _app);
};

#endif // _PLAYMUSIC_CONTROLLER_HPP_