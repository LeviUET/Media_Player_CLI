#include "playmusic_controller.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

void PlayMusicController::playMusicinFolder(Application& _app){
    int index;
    vector<MediaFile> mediaFilesList;
    string folderPath = PlayMusicView::getFolderPath();
    if (folderPath == "b") {
        _app.setViewState(HOME_VIEW);
        _app.setControllerState(HOME_CONTROLLER);
        return;
    } else if (folderPath == "e") {
        _app.setViewState(EXIT_VIEW);
        _app.setControllerState(EXIT_CONTROLLER);
        return;
    }
    // Check if the folder exists
    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        cout << "Invalid folder path. Please try again." << endl;
        sleep(1);
        return;
    }

    // Set the folder path in the application
    _app.setFolderPath(folderPath);

    // Get the list of media files in the folder
    
    _app.setMediaFilesList(mediaFilesList);
    mediaFilesList = _app.getMediaFilesList();
    if (mediaFilesList.empty()) {
        cout << "No music files found in the selected folder." << endl;
        return;
    }else{
        for (int i = 0; i < (int)mediaFilesList.size(); ++i) {
            cout << i + 1 << ". " << mediaFilesList[i].getMetadata().getTitle() << endl;
        }
        cout << "\nEnter the index of the music file to play (press 0 to skip to next step): ";
        cin >> index;
        
        while (index < 1 || index > (int)mediaFilesList.size()) {
            if (index == 0){
                _app.setViewState(MEDIA_PLAYER_VIEW);
                _app.setControllerState(MEDIA_PLAYER_CONTROLLER);
                return;
            }
            cout << "Invalid index. Please try again: ";
            cin >> index;
        }
        _app.setCurrentSongIndex(index-1);
    }
    // Play the selected music file
    string filePath = mediaFilesList[index-1].getDirectory();
    _app.setFilePath(filePath);
    Mix_Music* music = Mix_LoadMUS(_app.getFilePath().c_str());
    if (music == nullptr) {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }

    Mix_PlayMusic(music, -1);
    _app.setViewState(MEDIA_PLAYER_VIEW);
    _app.setControllerState(MEDIA_PLAYER_CONTROLLER);
}

void PlayMusicController::playMusicinPlaylist(Application& _app){
    int index;
    vector<MediaFile> mediaFilesList;
    vector<Playlist> _playlists = _app.getPlaylists();
    if (_playlists.empty()) {
        cout << "No playlist available. Please create a playlist first." << endl;
        sleep(1);
        return;
    }
    for (int i = 0; i < (int)_playlists.size(); ++i) {
        cout << i + 1 << ". " << _playlists[i].getName() << endl;
    }
    cout << "\nSelect a playlist to play: (type 0 to back)" << endl;
    cin >> index;
    
    while (index < 1 || index > (int)_playlists.size()) {
        if (index == 0){
            _app.setViewState(HOME_VIEW);
            _app.setControllerState(HOME_CONTROLLER);
            return;
        }
        cout << "Invalid playlist index. Please try again." << endl;
        cin >> index;
    }


    for (int i = 0; i < _playlists[index - 1].getSizeofPlaylist(); ++i) {
        mediaFilesList.push_back(_playlists[index - 1].getSong(i));
    }
    _app.setMediaFilesListbyPlaylist(mediaFilesList);
    if (mediaFilesList.empty()) {
        cout << "No songs in the selected playlist." << endl;
        sleep(1);
        return;
    }else{
        for (int i = 0; i < (int)mediaFilesList.size(); ++i) {
            cout << i + 1 << ". " << mediaFilesList[i].getMetadata().getTitle() << endl;
        }
        cout << "\nEnter the index of the music file to play: ";
        cin >> index;
        while (index < 1 || index > (int)mediaFilesList.size()) {
            cout << "Invalid index. Please try again." << endl;
            cin >> index;
        }
        _app.setCurrentSongIndex(index-1);
    }
    
    // Play the selected music file
    string filePath = mediaFilesList[index-1].getDirectory();
    _app.setFilePath(filePath);
    Mix_Music* music = Mix_LoadMUS(_app.getFilePath().c_str());
    if (music == nullptr) {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }
    Mix_PlayMusic(music, -1);     
}