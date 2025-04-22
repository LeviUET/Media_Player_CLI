#include "playlist_view.hpp"
using namespace std;

void PlaylistView::generatePlaylistView() {
    //system("clear");
    cout << "=======PLAYLIST VIEW=======" << endl;
    cout << "1. Create playlist" << endl;
    cout << "2. Add song to plalist" << endl;
    cout << "3. Remove song from playlist" << endl;
    cout << "4. Delete playlist" << endl;
    cout << "5. Display all playlist" << endl;
    cout << "6. Play playlist" << endl;
    cout << "7. Back" << endl;
    cout << "8. Exit" << endl;
}

void PlaylistView::displayPlaylist(Application& _app, int index) {
    vector<Playlist> _playlists = _app.getPlaylists();
    //cout << "Playlist: " << _playlists[index].getName() << endl;
    if (_playlists[index].getSizeofPlaylist() == 0) {
        cout << "Empty ... " << endl;
        sleep(1);
        return;
    }
    for (int i = 0; i < _playlists[index].getSizeofPlaylist(); ++i) {
        cout << "   " << i + 1 << ". " << _playlists[index].getSong(i).getMetadata().getTitle() << endl;
    }
}

void PlaylistView::displayAllPlaylists(Application& _app) {
    system("clear");
    vector<Playlist> _playlists = _app.getPlaylists();
    cout << "All playlist: " << endl;
    if (_app.getSizeofListPlaylists() == 0) {
        cout << "Empty ... " << endl;
        sleep(1);
        return;
    }
    for (int i = 0; i < _app.getSizeofListPlaylists(); ++i) {
        cout << i + 1 << ". " << _playlists[i].getName() << endl;
        PlaylistView::displayPlaylist(_app, i);
    }
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    //getchar(); // Chờ người dùng nhấn Enter
}

