#include <iostream>
#include <string>
#include <vector>
#include "metadata.hpp"

using namespace std;

Metadata::Metadata(string _title, string _artist, uint _year, string _genre){
    this->_title  = _title;
    this->_artist = _artist;
    this->_year   = _year;
    this->_genre  = _genre;
};

Metadata::~Metadata(){};

string Metadata::getTitle(){
    return _title;
}

string Metadata::getArtist(){
    return _artist;
}

uint Metadata::getYear(){
    return _year;
}

string Metadata::getGenre(){
    return _genre;
}

void Metadata::setTitle(string _title){
    this->_title = _title;
}

void Metadata::setArtist(string _artist){
    this->_artist = _artist;
}

void Metadata::setYear(uint _year){
    this->_year = _year;
}

void Metadata::setGenre(string _genre){
    this->_genre = _genre;
}