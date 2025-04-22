#include <iostream>
#include <string>
#include <vector>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include "mediafile.hpp"
#include "metadata.hpp"
using namespace std;

MediaFile::MediaFile(const string& _directory){
    this->directory = _directory;
    TagLib::FileRef file(_directory.c_str());
    if (!file.isNull() && file.tag ()) {
        TagLib::Tag*    tag = file.tag();
        this->metadata.setTitle(tag->title().toCString());
        this->metadata.setArtist(tag->artist().toCString());
        this->metadata.setYear(tag->year());
        this->metadata.setGenre(tag->genre().toCString());
    }
};
MediaFile::~MediaFile(){};

Metadata MediaFile::getMetadata(){
    return this->metadata;
}

string MediaFile::getDirectory(){
    return this->directory;
}

void MediaFile::setMetadata(Metadata _metadata){
    this->metadata = _metadata;
}