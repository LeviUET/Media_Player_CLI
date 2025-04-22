#ifndef _METADATA_H_
#define _METADATA_H_


using namespace std;

class Metadata{
    private:
        std::string _title;
        std::string _artist;
        std::string _album;
        uint        _year;
        std::string _genre;
        uint        _track;
    public:
        Metadata(string _title = "Unknown", string _artist = "Unknown", uint _year = 0, string _genre = "Unknown");
        ~Metadata();
        
        std::string getTitle();
        std::string getArtist();
        uint        getYear();
        std::string getGenre();

        void setTitle(std::string _title);
        void setArtist(std::string _artist);
        void setYear(uint _year);
        void setGenre(std::string _genre);

};

#endif // _METADATA_H_