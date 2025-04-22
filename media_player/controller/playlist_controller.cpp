#include "playlist_controller.hpp"
using namespace std;

void PlaylistController::createPlaylist(Application& _app) {
    system("clear");
    Playlist newPlaylist;
    vector<Playlist> list_playlists_temp;
    list_playlists_temp = _app.getPlaylists();
    cout << "=======CREATE PLAYLIST=======" << endl;
    cout << "Enter the name of the playlist: ";
    string playlistName;
    cin >> playlistName;
    newPlaylist.setName(playlistName);
    list_playlists_temp.push_back(newPlaylist);
    _app.setPlaylists(list_playlists_temp);
}

void PlaylistController::addSongToPlaylist(Application& _app) {
    system("clear");
    cout << "=======ADD SONG TO PLAYLIST=======" << endl;
    vector<Playlist> _playlists      = _app.getPlaylists();
    vector<MediaFile> mediaFilesList;
    if (_playlists.empty()) {
        cout << "No playlist available. Please create a playlist first." << endl;
        sleep(1);
        return;
    }
    cout << "Choose folder path to add song: " << endl;
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
        return;
    }

    // Set the folder path in the application
    _app.setFolderPath(folderPath);
    _app.setMediaFilesList(mediaFilesList);
    mediaFilesList = _app.getMediaFilesList();
    cout << "Select a song to add to a playlist:" << endl;
    
    for (int i = 0; i < (int)mediaFilesList.size(); ++i) {
        cout << i + 1 << ". " << mediaFilesList[i].getMetadata().getTitle() << endl;
    }
    int songIndex;
    cin >> songIndex;
    while (songIndex < 1 || songIndex > (int)mediaFilesList.size()) {
        cout << "Invalid song index. Please try again." << endl;
        cin >> songIndex;
    }
    _app.setNewSongIndex(songIndex - 1);
    cout << "Select a playlist to add a song to:" << endl;
    for (int i = 0; i < (int)_playlists.size(); ++i) {
        cout << i + 1 << ". " << _playlists[i].getName() << endl;
    }
    int playlistIndex;
    cin >> playlistIndex;
    while (playlistIndex < 1 || playlistIndex > (int)_playlists.size()) {
        cout << "Invalid playlist index. Please try again." << endl;
        cin >> playlistIndex;
        return;
    }
    _playlists[playlistIndex - 1].addSong(mediaFilesList[songIndex - 1]);
    _app.setPlaylists(_playlists);
}

void PlaylistController::removeSongFromPlaylist(Application& _app) {
    system("clear");
    cout << "=======REMOVE SONG FROM PLAYLIST=======" << endl;
    vector<Playlist> _playlists = _app.getPlaylists();
    if (_playlists.empty()) {
        cout << "No playlist available. Please create a playlist first." << endl;
        sleep(1);
        return;
    }
    cout << "Select a playlist to remove a song from: (type 0 to back)" << endl;
    for (size_t i = 0; i < _playlists.size(); ++i) {
        cout << i + 1 << ". " << _playlists[i].getName() << endl;
    }
    int playlistIndex;
    cin >> playlistIndex;
    if (playlistIndex == 0){
        _app.setViewState(HOME_VIEW);
        _app.setControllerState(HOME_CONTROLLER);
        return;
    }
    while (playlistIndex < 1 || playlistIndex > (int)_playlists.size()) {
        cout << "Invalid playlist index. Please try again." << endl;
        cin >> playlistIndex;     
    }
    cout << "Playlist: " << _playlists[playlistIndex - 1].getName() << endl;
    PlaylistView::displayPlaylist(_app, playlistIndex - 1);

    cout << "Enter the index of the song to remove: ";
    int songIndex;
    cin >> songIndex;
    _playlists[playlistIndex - 1].removeSong(songIndex-1);
    _app.setPlaylists(_playlists);
}

void PlaylistController::deletePlaylist(Application& _app) {
    system("clear");
    cout << "=======DELETE PLAYLIST=======" << endl;
    vector<Playlist> _playlists = _app.getPlaylists();
    if (_playlists.empty()) {
        cout << "No playlist available. Please create a playlist first." << endl;
        sleep(1);
        return;
    }
    cout << "Select a playlist to delete: (type 0 to back)" << endl;
    for (int i = 0; i < (int)_playlists.size(); ++i) {
        cout << i + 1 << ". " << _playlists[i].getName() << endl;
    }
    int playlistIndex;
    cin >> playlistIndex;
    if (playlistIndex == 0){
        _app.setViewState(HOME_VIEW);
        _app.setControllerState(HOME_CONTROLLER);
        return;
    }
    while (playlistIndex < 1 || playlistIndex > (int)_playlists.size()) {
        cout << "Invalid playlist index. Please try again." << endl;
        cin >> playlistIndex;
    }
    _playlists.erase(_playlists.begin() + playlistIndex - 1);
    _app.setPlaylists(_playlists);
}

void PlaylistController::displayAllPlaylists(Application& _app) {
    PlaylistView::displayAllPlaylists(_app);
}

void PlaylistController::playPlaylist(Application& _app) {
    system("clear");
    cout << "=======PLAY PLAYLIST=======" << endl;
    PlayMusicController::playMusicinPlaylist(_app);
    _app.setViewState(MEDIA_PLAYER_VIEW);
    _app.setControllerState(MEDIA_PLAYER_CONTROLLER);
}