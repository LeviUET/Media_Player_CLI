#ifndef _PLAYLIST_CONTROLLER_HPP_
#define _PLAYLIST_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"
#include "../view/playlist_view.hpp"
#include "../view/playmusic_view.hpp"
#include "../controller/playmusic_controller.hpp"


class PlaylistController {
    public:
        static void createPlaylist(Application& _app);
        static void addSongToPlaylist(Application& _app);
        static void removeSongFromPlaylist(Application& _app);
        static void deletePlaylist(Application& _app);
        static void displayAllPlaylists(Application& _app);
        static void playPlaylist(Application& _app);
};

#endif // _PLAYLIST_CONTROLLER_HPP_