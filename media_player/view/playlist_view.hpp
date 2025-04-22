#ifndef _PLAYLIST_VIEW_HPP_
#define _PLAYLIST_VIEW_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"

class PlaylistView {
    public:
        static void generatePlaylistView();
        static void displayAllPlaylists(Application& _app);
        static void displayPlaylist(Application& _app, int index);
};

#endif // _PLAYLIST_VIEW_HPP_