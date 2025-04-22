#ifndef _MEDIAFILE_H_
#define _MEDIAFILE_H_

#include <iostream>
#include <string>
#include <vector>
#include <taglib/tag.h>
#include "metadata.hpp"
using namespace std;

class MediaFile{
    protected:
    std::string   directory;
    Metadata      metadata;

    public:
    MediaFile(const string& _directory);
    ~MediaFile();

    Metadata    getMetadata();
    std::string getDirectory();
    void        setMetadata(Metadata _metadata);
};

#endif // _MEDIAFILE_H_