#include "edit_metadata_controller.hpp"
using namespace std;

void EditMetadataController::chooseMusicFile(Application& _app) {
    string folderPath;
    cin >> folderPath;
    if (folderPath == "b") {
        _app.setViewState(HOME_VIEW);
        _app.setControllerState(HOME_CONTROLLER);
        return;
    } else if (folderPath == "e") {
        _app.setViewState(EXIT_VIEW);
        _app.setControllerState(EXIT_CONTROLLER);
        return;
    }
    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        cout << "Invalid folder path. Please try again." << endl;
        sleep(1);
        return;
    }
    _app.setFolderPath(folderPath);
    vector<MediaFile> mediaFilesList;
    _app.setMediaFilesList(mediaFilesList);
    mediaFilesList = _app.getMediaFilesList();
    cout << endl;
    cout << "Select a media file to edit metadata:" << endl;
    for (int i = 0; i < (int)mediaFilesList.size(); ++i) {
        cout << i + 1 << ". " << mediaFilesList[i].getDirectory() << endl;
    }
    cout << "\nEnter the index of the media file: ";
    int index;
    cin >> index;
    while (index < 1 || index > (int)mediaFilesList.size()) {
        cout << "Invalid index. Please try again." << endl;
        cin >> index;
    }
    string filePath = mediaFilesList[index - 1].getDirectory();
    cout << "Selected file: " << filePath << endl;
    _app.setFilePath(filePath);
    _app.setViewState(EDIT_METADATA_MENU_VIEW);
    _app.setControllerState(EDIT_METADATA_MENU_CONTROLLER);
}