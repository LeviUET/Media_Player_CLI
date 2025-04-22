#include "playlist.hpp"
using namespace std;

Playlist::Playlist(){};
Playlist::~Playlist(){};

void Playlist::addSong(MediaFile song) {
    songs.push_back(song);
}

void Playlist::removeSong(int index) {
    if (index >= 0 && index < (int)songs.size()) {
        songs.erase(songs.begin() + index);
    } else {
        cout << "Invalid index. Cannot remove song." << endl;
    }
}

MediaFile Playlist::getSong(int index) {
    return songs[index];
}

int Playlist::getSizeofPlaylist() {
    return songs.size();
}
void Playlist::setName(std::string _name) {
    name = _name;
}
std::string Playlist::getName() {
    return name;
}