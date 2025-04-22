#include "general_controller.hpp"
#include "edit_metadata_menu_controller.hpp"

using namespace std;

void GeneralController::executeState(Application& _app) {
    switch (_app.getControllerState()) {
        case HOME_CONTROLLER:
            char choice;
            GeneralView::generateView(_app);
            choice = GeneralView::getChoice();
            if (choice == '1'){
                _app.setUsingPlaylist(false);
                _app.setViewState(PLAYMUSIC_VIEW);
                _app.setControllerState(PLAYMUSIC_CONTROLLER);
            } else if (choice == '2'){
                _app.setUsingPlaylist(true);
                _app.setViewState(PLAYLIST_VIEW);
                _app.setControllerState(PLAYLIST_CONTROLLER);
            } else if (choice == '3'){
                _app.setViewState(EDIT_METADATA_VIEW);
                _app.setControllerState(EDIT_METADATA_CONTROLLER);
            } else if (choice == '4'){
                _app.setViewState(EXIT_VIEW);
                _app.setControllerState(EXIT_CONTROLLER);
            } else {
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
                _app.setViewState(HOME_VIEW);
                _app.setControllerState(HOME_CONTROLLER);
            }
            break;
        case PLAYMUSIC_CONTROLLER:
            GeneralView::generateView(_app);
            PlayMusicController::playMusicinFolder(_app);
            break;
        case PLAYLIST_CONTROLLER:
            char playlistChoice; 
            GeneralView::generateView(_app);
            playlistChoice = GeneralView::getChoice();
            if (playlistChoice == '1'){
                PlaylistController::createPlaylist(_app);
            } else if (playlistChoice == '2'){
                PlaylistController::addSongToPlaylist(_app);
            } else if (playlistChoice == '3'){
                PlaylistController::removeSongFromPlaylist(_app);
            } else if (playlistChoice == '4'){
                PlaylistController::deletePlaylist(_app);
            } else if (playlistChoice == '5'){
                PlaylistView::displayAllPlaylists(_app);
            } else if (playlistChoice == '6'){
                PlaylistController::playPlaylist(_app);
            } else if (playlistChoice == '7'){
                _app.setViewState(HOME_VIEW);
                _app.setControllerState(HOME_CONTROLLER);
            } else if (playlistChoice == '8'){
                _app.setViewState(EXIT_VIEW);
                _app.setControllerState(EXIT_CONTROLLER);
            } else {
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
                _app.setViewState(PLAYLIST_VIEW);
                _app.setControllerState(PLAYLIST_CONTROLLER);
            }
            break;
        case EDIT_METADATA_CONTROLLER:
            GeneralView::generateView(_app);
            EditMetadataController::chooseMusicFile(_app);
            if (_app.getViewState() == EDIT_METADATA_MENU_VIEW){
                _app.setControllerState(EDIT_METADATA_MENU_CONTROLLER);
            } else if (_app.getViewState() == HOME_VIEW){
                _app.setControllerState(HOME_CONTROLLER);
            } else if (_app.getViewState() == EXIT_VIEW){
                _app.setControllerState(EXIT_CONTROLLER);
            }
            break;
        case EXIT_CONTROLLER:
            exit(0);
            break;
        
        case MEDIA_PLAYER_CONTROLLER:
            char mediaChoice;
            GeneralView::generateView(_app);
            mediaChoice = GeneralView::getChoice();
            if (mediaChoice == '1'){
                MediaPlayerController::pauseMusic();
            } else if (mediaChoice == '2'){
                MediaPlayerController::skipMusic(_app);
            } else if (mediaChoice == '3'){
                MediaPlayerController::rewindMusic(_app);
            } else if (mediaChoice == '4'){
                MediaPlayerController::stopMusic(_app);
                _app.setViewState(PLAYMUSIC_VIEW);
                _app.setControllerState(PLAYMUSIC_CONTROLLER);
            } else if (mediaChoice == '5'){
                MediaPlayerController::changeVolume(_app);
            } else if (mediaChoice == '6'){
                _app.setViewState(PLAYMUSIC_VIEW);
                _app.setControllerState(PLAYMUSIC_CONTROLLER);
            } else if (mediaChoice == '7'){
                _app.setViewState(EXIT_VIEW);
                _app.setControllerState(EXIT_CONTROLLER);
            } else {
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
                _app.setControllerState(MEDIA_PLAYER_CONTROLLER);               
            }
            break;
        case EDIT_METADATA_MENU_CONTROLLER:
            char editMenuChoice;
            GeneralView::generateView(_app);
            editMenuChoice = GeneralView::getChoice();
            if (editMenuChoice == '1'){
                EditMetadataMenuController::editTitle(_app);
            } else if (editMenuChoice == '2'){
                EditMetadataMenuController::editArtist(_app);
            } else if (editMenuChoice == '3'){
                EditMetadataMenuController::editYear(_app);
            } else if (editMenuChoice == '4'){
                EditMetadataMenuController::editGenre(_app);
            } else if (editMenuChoice == '5'){
                _app.setViewState(HOME_VIEW);
                _app.setControllerState(HOME_CONTROLLER);
            } else if (editMenuChoice == '6'){
                _app.setViewState(EXIT_VIEW);
                _app.setControllerState(EXIT_CONTROLLER);
            } else {
                cout << "Invalid choice. Please try again." << endl;
                sleep(1);
                _app.setViewState(EDIT_METADATA_MENU_VIEW);
                _app.setControllerState(EDIT_METADATA_MENU_CONTROLLER);
            }
            break;
    }
}

