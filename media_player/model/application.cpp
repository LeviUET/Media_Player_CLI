#include "application.hpp"

Application::Application() {
    // Constructor implementation
}

Application::~Application() {
    // Destructor implementation
}

void Application::setFolderPath(std::string _folderPath) {
    this->folderPath = _folderPath;
}

void Application::setMediaFilesList(vector<MediaFile> _mediaFilesList) {
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            // Create a MediaFile object and add it to the list
            MediaFile media(entry.path().string());
            _mediaFilesList.push_back(media);
        }
    }
    this->mediaFilesList = _mediaFilesList;
}

vector<MediaFile> Application::getMediaFilesList() {
    return this->mediaFilesList;
}

int Application::getCurrentSongIndex() {
    return this->currentSongIndex;
}

void Application::setCurrentSongIndex(int _currentSongIndex) {
    this->currentSongIndex = _currentSongIndex;
}

CONTROLLER_STATE Application::getControllerState() {
    return this->controllerState;
}

void Application::setControllerState(CONTROLLER_STATE _state) {
    this->controllerState = _state;
}

VIEW_STATE Application::getViewState() {
    return this->viewState;
}

void Application::setViewState(VIEW_STATE _state) {
    this->viewState = _state;
}

int Application::getSizeofListPlaylists() {
    return playlists.size();
}

MediaFile Application::getMediaFileinPlaylist(int index) {
    if (index >= 0 && index < (int)playlists.size()) {
        return playlists[index].getSong(index);
    }
    return MediaFile("");
}

void Application::setPlaylists(vector<Playlist> _playlists) {
    this->playlists = _playlists;
}

vector<Playlist> Application::getPlaylists() {
    return this->playlists;
}

int Application::getNewSongIndex() {
    return this->newSongIndex;
}

void Application::setNewSongIndex(int _newSongIndex) {
    this->newSongIndex = _newSongIndex;
}

void Application::setFilePath(std::string _filePath) {
    this->filePath = _filePath;
}

std::string Application::getFilePath() {
    return this->filePath;
}

Playlist Application::getOnePlaylist(int indexPlaylist) {
    return playlists[indexPlaylist];
}

bool Application::getUsingPlaylist() {
    return usingPlaylist;
}

void Application::setUsingPlaylist(bool _usingPlaylist) {
    this->usingPlaylist = _usingPlaylist;
}

void Application::setMediaFilesListbyPlaylist(vector<MediaFile> _mediaFilesList) {
    this->mediaFilesList = _mediaFilesList;
}

void Application::setVolume(int _volume) {
    if (_volume < 0) {
        _volume = 0;
    }
    if (_volume > 128){
        _volume = 128;
    }
    Mix_VolumeMusic(_volume);
    this->volume = _volume;
}

int Application::getVolume() {
    return this->volume;
}

int Application::getCurrentTime() {
    return this->currentTime;
}
void Application::setCurrentTime(int _currentTime) {
    this->currentTime = _currentTime;
}

int Application::getDuration() {
    return this->duration;
}   

void Application::setDuration(int currentSongIndex) {
    TagLib::FileRef file(mediaFilesList[currentSongIndex].getDirectory().c_str());
    if (!file.isNull() && file.audioProperties()) {
        // Retrieve audio properties
        TagLib::AudioProperties* properties = file.audioProperties();
        // Return the duration in seconds
        this->duration = properties->length();  // Length in seconds
    }
}

void Application::setFd(int _fd) {
    this->fd = _fd;
}

int Application::getFd() {
    return this->fd;
}
