#ifndef _DISPLAY_SONG_VIEW_HPP_
#define _DISPLAY_SONG_VIEW_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <thread>
#include "../model/application.hpp"

string formatTime(int seconds);
void   displayProgressBar(int currentTime, int totalDuration);
class DisplaySongView {
    public:
        static void displaySongDetails(Application& _app);
};

#endif // _DISPLAY_SONG_VIEW_HPP_