#ifndef FILM_CPP
#define FILM_CPP

#include <string>
#include <iostream>
#include <fstream>
#include "Film.h"


Film::Film(){
    this->setName(" ");
    this->setPathname(" ");
    this->setDuration(0);
    this->nbChapters = 0;
    this->chapters = nullptr;
};
Film::Film(std::string name, std::string pathname, int duration, int *chapters, int nbChapters){
    this->setName(name);
    this->setPathname(pathname);
    this->setDuration(duration);
    this->nbChapters = nbChapters;
    this->chapters = new int[nbChapters];
    for(int i = 0; i < nbChapters; i++){
        this->chapters[i] = chapters[i];
    }
};
Film::~Film(){
    std::cerr<<"Adieu film " + this->getName() + "\n"<<std::endl;
};

void Film::writeToFile(std::ofstream& out) const{
    Video::writeToFile(out);
    out << "Number of chapters: " << this->getNbChapters() << std::endl;
    out << "Chapters: ";
    for(int i = 0; i < this->getNbChapters(); i++){
        out << this->getChapters()[i] << " ";
    }
    out << std::endl;
};

Film Film::readFromFile(std::ifstream& in){
    std::string name, pathname;
    int duration, nbChapters;
    in >> name >> pathname >> duration >> nbChapters;
    int* chapters = new int[nbChapters];
    for (int i = 0; i < nbChapters; i++){
        in >> chapters[i];
    }
    return Film(name, pathname, duration, chapters, nbChapters);
};

void Film::setChapters(int* chapters, int nbChapters){
    this->nbChapters = nbChapters;
    if(this->chapters != nullptr){
        delete[] this->chapters;
    }
    if(nbChapters == 0){
        this->chapters = nullptr;
        return;
    }
    this->chapters = new int[nbChapters];
    for(int i = 0; i < nbChapters; i++){
        this->chapters[i] = chapters[i];
    }
};

int* Film::getChapters() const{
    return chapters;
};

int Film::getNbChapters() const{
    return nbChapters;
};

void Film::display(std::ostream &stream) const{
    Video::display(stream);
    stream << "Number of chapters: " << this->getNbChapters() << std::endl;
    stream << "Chapters: ";
    for(int i = 0; i < this->getNbChapters(); i++){
        stream << this->getChapters()[i] << " ";
    }
    stream << std::endl;
};

void Film::play() const{
    std::cout << "Playing film " << this->getName() << " from " << this->getPathname() << std::endl;
    std::string command = 
        "mpv " + this->getPathname() 
        + " --start=" + std::to_string(this->getChapters()[0]) 
        + " --end=" + std::to_string(this->getChapters()[this->getNbChapters() - 1]) + " &";
    system(command.c_str());
};

#endif // FILM_CPP