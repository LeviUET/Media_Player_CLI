#ifndef _MEDIA_PLAYER_HPP_
#define _MEDIA_PLAYER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../model/application.hpp"

class MediaPlayerController {
    public:
        static void pauseMusic();
        static void skipMusic(Application& app);
        static void rewindMusic(Application& app);
        static void stopMusic(Application& app);
        static void changeVolume(Application& app);
};
#endif // _MEDIA_PLAYER_HPP_