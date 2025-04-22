#ifndef _PLAYMUSIC_VIEW_HPP_
#define _PLAYMUSIC_VIEW_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "general_view.hpp"

class PlayMusicView {
    public:
        static void   generatePlayMusicView();
        static string getFolderPath();
};

#endif // _PLAYMUSIC_VIEW_HPP_