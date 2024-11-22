#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
#include <fstream>
#include "MultimediaObject.h"

class Video : public MultimediaObject {
private:
    // Variables d'instance spécifiques aux vidéos
    int duration;
public:
    // Constructeurs, destructeur, accesseurs, modifieurs
    Video(){
        this->setName(" ");
        this->setPathname(" ");
        this->duration = 0;
    };
    
    Video(std::string name, std::string pathname, int duration){
        this->setName(name);
        this->setPathname(pathname);
        this->duration = duration;
    };
    
    virtual ~Video(){
        std::cerr<<"Adieu video " + this->getName() + "\n"<<std::endl;
    };
    
    void writeToFile(std::ofstream& out) const override{
        MultimediaObject::writeToFile(out);
        out << "Duration: " << this->getDuration() << std::endl;
    };

    Video readFromFile(std::ifstream& in) {
        std::string name, pathname;
        int duration;
        in >> name >> pathname >> duration;
        return Video(name, pathname, duration);
    };

    int getDuration() const{ 
        return duration; 
    };
    
    void setDuration(int duration){
        this->duration = duration; 
    };
    
    void display(std::ostream &stream) const override{
        MultimediaObject::display(stream);
        stream << "Duration: " << this->getDuration() << std::endl;
    };
    void play() const override{
        std::cout << "Playing video " << this->getName() << " from " << this->getPathname() << std::endl;
        system(("mpv " + this->getPathname() + " &").c_str());
    };
};

#endif // VIDEO_H