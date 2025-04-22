#ifndef _PLAYLIST_HPP_
#define _PLAYLIST_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "mediafile.hpp"
using namespace std;
class Playlist {
    private:
        string name;
        vector<MediaFile> songs;

    public:
        Playlist();
        ~Playlist();

        void addSong(MediaFile song);
        void removeSong(int index);

        std::string getName();
        void setName(std::string _name);

        int  getSizeofPlaylist();
        MediaFile getSong(int index);
};

#endif // _PLAYLIST_HPP_