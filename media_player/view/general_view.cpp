#include "general_view.hpp"
using namespace std;

char GeneralView::getChoice() {
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return choice;
}

void GeneralView::generateView(Application& _app) {
    system("clear");
    switch (_app.getViewState()) {
        case HOME_VIEW:
            HomeView::generateHomeView();
            cout << endl;
            DisplaySongView::displaySongDetails(_app);
            cout << endl;
            cout << "Enter your choice: ";
            cout << endl;
            break;
        case PLAYMUSIC_VIEW:
            PlayMusicView::generatePlayMusicView();
            break;
        case PLAYLIST_VIEW:
            PlaylistView::generatePlaylistView();
            cout << endl;
            cout << "Enter your choice: ";
            cout << endl;
            break;
        case EDIT_METADATA_VIEW:
            EditMetadataView::generateEditMetadataView();
            break;
        case EXIT_VIEW:
            cout << "Exiting..." << endl;
            break;       
        case MEDIA_PLAYER_VIEW:
            MediaPlayerView::generateMediaPlayerView();
            cout << endl;
            DisplaySongView::displaySongDetails(_app);
            cout << endl;
            cout << "Enter your choice: ";
            cout << endl;
            break;
        case EDIT_METADATA_MENU_VIEW:
            EditMetadataMenuView::generateEditMetadataMenuView();
            cout << endl;
            cout << "Enter your choice: ";
            cout << endl;
            break;
    }
}

