#include "media_player_controller.hpp"

void MediaPlayerController::pauseMusic() {
    if (Mix_PausedMusic()){
        Mix_ResumeMusic();
    }else if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
    else{
        cout << "No music is playing." << endl;
        sleep(1);
    }
}

void MediaPlayerController::skipMusic(Application& _app) {
    vector<MediaFile> mediaFilesList;
    mediaFilesList = _app.getMediaFilesList();
    if (mediaFilesList.size() == 0){
        return;
    }
    int currentSongIndex = _app.getCurrentSongIndex();
    if (currentSongIndex < (int)mediaFilesList.size() - 1) {
        _app.setCurrentSongIndex(currentSongIndex + 1);
    } else {
        currentSongIndex = 0;
        _app.setCurrentSongIndex(currentSongIndex);
    }
    string filePath = mediaFilesList[_app.getCurrentSongIndex()].getDirectory();
    _app.setFilePath(filePath);
    Mix_HaltMusic();
    Mix_Music* music = Mix_LoadMUS(_app.getFilePath().c_str());
    if (music == nullptr) {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }
    Mix_PlayMusic(music, -1);
}

void MediaPlayerController::rewindMusic(Application& _app) {
    vector<MediaFile> mediaFilesList;
    mediaFilesList = _app.getMediaFilesList();
    if (mediaFilesList.size() == 0){
        return;
    }
    int currentSongIndex = _app.getCurrentSongIndex();
    if (currentSongIndex > 0) {
        _app.setCurrentSongIndex(currentSongIndex - 1);    
    } else {
        currentSongIndex = mediaFilesList.size() - 1;
        _app.setCurrentSongIndex(currentSongIndex);
    }
    string filePath = mediaFilesList[_app.getCurrentSongIndex()].getDirectory();
    _app.setFilePath(filePath);
    Mix_HaltMusic();
    Mix_Music* music = Mix_LoadMUS(_app.getFilePath().c_str());
    if (music == nullptr) {
        cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }
    Mix_PlayMusic(music, -1);
}

void MediaPlayerController::stopMusic(Application& _app) {
    Mix_HaltMusic();
    Mix_FreeMusic(Mix_LoadMUS("")); // Free the music
    _app.setCurrentSongIndex(-1);
    _app.setFilePath("");
    _app.setCurrentTime(0);
    _app.setDuration(0);
    _app.setUsingPlaylist(false);
    _app.setControllerState(HOME_CONTROLLER);
    _app.setViewState(HOME_VIEW);
    _app.setMediaFilesList(vector<MediaFile>());
    _app.setPlaylists(vector<Playlist>());
    cout << "Music stopped." << endl;
    sleep(1);
    // Mix_CloseAudio();
    // SDL_Quit();
}

void MediaPlayerController::changeVolume(Application& _app) {
    int volume;
    cout << "Enter volume level (0-128): ";
    cin >> volume;
    if (volume < 0 || volume > 128) {
        cout << "Invalid volume level. Please enter a value between 0 and 128." << endl;
        return;
    }
    _app.setVolume(volume);
    Mix_VolumeMusic(_app.getVolume()); 
    cout << "Volume set to " << volume << "." << endl;
    sleep(1);
}