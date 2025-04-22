#include "edit_metadata_menu_controller.hpp"
using namespace std;
void EditMetadataMenuController::editTitle(Application& _app) {
    system("clear");
    TagLib::FileRef file(_app.getFilePath().c_str());

    cout << "=======EDIT TITLE=======" << endl;
    string newTitle;
    cout << "Enter the new title: ";
    getline(cin, newTitle);
    cin.ignore();
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();
        // Update metadata fields
        tag->setTitle(TagLib::String(newTitle.c_str()));      // Set new title
    }
    file.save();
}

void EditMetadataMenuController::editArtist(Application& _app) {
    system("clear");
    TagLib::FileRef file(_app.getFilePath().c_str());
    
    cout << "=======EDIT ARTIST=======" << endl;
    string newArtist;
    cout << "Enter the new artist: ";
    getline(cin, newArtist);
    cin.ignore();
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();
        // Update metadata fields
        tag->setArtist(TagLib::String(newArtist.c_str()));      // Set new artist
    }
    file.save();
}

void EditMetadataMenuController::editYear(Application& _app) {
    system("clear");
    TagLib::FileRef file(_app.getFilePath().c_str());

    cout << "=======EDIT YEAR=======" << endl;
    uint newYear;
    cout << "Enter the new year: ";
    cin >> newYear;
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();
        // Update metadata fields
        tag->setYear(newYear);      // Set new year
    }
    file.save();
}

void EditMetadataMenuController::editGenre(Application& _app) {
    system("clear");
    TagLib::FileRef file(_app.getFilePath().c_str());

    cout << "=======EDIT GENRE=======" << endl;
    string newGenre;
    cout << "Enter the new genre: ";
    getline(cin, newGenre);
    cin.ignore();
    if (!file.isNull() && file.tag()) {
        TagLib::Tag* tag = file.tag();
        // Update metadata fields
        tag->setGenre(TagLib::String(newGenre.c_str()));      // Set new genre
    }
    file.save();
}