#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "mediafile.hpp"
#include "metadata.hpp"
#include "playlist.hpp"

enum CONTROLLER_STATE {
    HOME_CONTROLLER,
    PLAYMUSIC_CONTROLLER,
    PLAYLIST_CONTROLLER,
    EDIT_METADATA_CONTROLLER,

    MEDIA_PLAYER_CONTROLLER,
    EDIT_METADATA_MENU_CONTROLLER,

    EXIT_CONTROLLER,
};

enum VIEW_STATE {
    HOME_VIEW,
    PLAYMUSIC_VIEW,
    PLAYLIST_VIEW,
    EDIT_METADATA_VIEW,

    MEDIA_PLAYER_VIEW,
    EDIT_METADATA_MENU_VIEW,

    EXIT_VIEW,
};

class Application {
    private:
        vector<MediaFile> mediaFilesList;
        vector<Playlist>  playlists;
        std::string       folderPath;
        int               currentSongIndex = -1;
        int               newSongIndex     = -1;
        CONTROLLER_STATE  controllerState;
        VIEW_STATE        viewState;
        std::string       filePath;
        bool              usingPlaylist = false;
        int               volume;
        int               currentTime = 0;
        int               duration = 0;
        int               fd;
    public:
        Application();
        ~Application();
        void              setMediaFilesList(vector<MediaFile> _mediaFilesList);
        vector<MediaFile> getMediaFilesList();
        void              setMediaFilesListbyPlaylist(vector<MediaFile> _mediaFilesList);

        int               getSizeofListPlaylists();
        MediaFile         getMediaFileinPlaylist(int index);
        void              setPlaylists(vector<Playlist> _playlists);
        vector<Playlist>  getPlaylists();
        Playlist          getOnePlaylist(int indexPlaylist);

        void              setFolderPath(std::string _folderPath);

        std::string       getFilePath();
        void              setFilePath(std::string _filePath);

        int               getCurrentSongIndex();
        void              setCurrentSongIndex(int _currentSongIndex);
        
        CONTROLLER_STATE  getControllerState();
        void              setControllerState(CONTROLLER_STATE _state);

        VIEW_STATE        getViewState();
        void              setViewState(VIEW_STATE _state);

        int               getNewSongIndex();
        void              setNewSongIndex(int _newSongIndex);

        bool              getUsingPlaylist();
        void              setUsingPlaylist(bool _usingPlaylist);

        void              setVolume(int _volume);
        int               getVolume();

        int               getCurrentTime();
        void              setCurrentTime(int _currentTime);

        int               getDuration();
        void              setDuration(int currentSongIndex);

        int               getFd();
        void              setFd(int _fd);
};

#endif // _APPLICATION_HPP_