#include "playmusic_view.hpp"

using namespace std;

string PlayMusicView::getFolderPath() {
    string folderPath;
    cin >> folderPath;
    return folderPath;
}

void PlayMusicView::generatePlayMusicView() {
    //system("clear");
    cout << "=======PLAY MUSIC VIEW=======" << endl;
    cout << "Enter the folder path containing music files (or 'b' to go back, 'e' to exit): ";
}