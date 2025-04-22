#include "display_song_view.hpp"
using namespace std;

string formatTime(int seconds){
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    return to_string(minutes) + ":" + (remainingSeconds < 10 ? "0" : "") + to_string(remainingSeconds);
}

void displayProgressBar(int currentTime, int totalDuration) {
    int barLength = 30;
    int progress = (currentTime * barLength) / totalDuration;
    string progressBar = "[";
    for (int i = 0; i < barLength; ++i) {
        progressBar += (i < progress) ? "#" : "_";
    }
    progressBar += "]";
    cout << progressBar << formatTime(currentTime) << "/" << formatTime(totalDuration) << endl;
}


void DisplaySongView::displaySongDetails(Application& _app) {
    TagLib::FileRef file(_app.getFilePath().c_str());
    int duration = 0;
    if (!file.isNull() && file.audioProperties()) {
        // Retrieve audio properties
        TagLib::AudioProperties* properties = file.audioProperties();
        // Return the duration in seconds
        duration = properties->length();  // Length in seconds
    }
    if (Mix_PlayingMusic() && Mix_PausedMusic() == 0) {
        std::cout << "Now Playing: " << std::endl;
    }
    else{
        std::cout << "Now Paused: " << std::endl;
    }
    if (_app.getMediaFilesList().empty() || _app.getCurrentSongIndex() < 0 || _app.getCurrentSongIndex() >= (int)_app.getMediaFilesList().size()) { 
        std::cout << "📀 Title: " << "Unknown" << std::endl;
        std::cout << "🎤 Artist: " << "Unknown" << std::endl;
        std::cout << "📜 Year: " << "Unknown" << std::endl;
        std::cout << "🎵 Genre: " << "Unknown" << std::endl;
        std::cout << "⌛ Duration Time: " << "0:00" << std::endl;
        if (_app.getFd() < 0) {
            cout << "❌ Failed connecting to Board " << endl;
            // Exit if UART initialization fails
        } else {
            cout << "✅ Connected to Board " << endl;
        }
        return;
    }
    std::cout << "📀 Title: " << _app.getMediaFilesList()[_app.getCurrentSongIndex()].getMetadata().getTitle() << std::endl;
    std::cout << "🎤 Artist: " << _app.getMediaFilesList()[_app.getCurrentSongIndex()].getMetadata().getArtist() << std::endl;
    std::cout << "📜 Year: " << _app.getMediaFilesList()[_app.getCurrentSongIndex()].getMetadata().getYear() << std::endl;
    std::cout << "🎵 Genre: " << _app.getMediaFilesList()[_app.getCurrentSongIndex()].getMetadata().getGenre() << std::endl;
    std::cout << "⌛ Duration Time: " << formatTime(duration) << endl;
    if (_app.getFd() < 0) {
        cout << "❌ Failed connecting to Board " << endl;
        // Exit if UART initialization fails
    } else {
        cout << "✅ Connected to Board " << endl;
    }
    return;
}