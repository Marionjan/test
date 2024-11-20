#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include <iostream>
#include "MultimediaObject.h"

class Photo : public MultimediaObject {
private:
    // Variables d'instance spécifiques aux photos
    int width;
    int height; 

public: 
    // Constructeurs, destructeur, accesseurs, modifieurs
    Photo(){
        this->setName(" ");
        this->setPathname(" ");
        this->width = 0;
        this->height = 0;
    };
    
    Photo(std::string name, std::string pathname, int width, int height){
        this->setName(name);
        this->setPathname(pathname);
        this->width = width;
        this->height = height;
    };
    
    virtual ~Photo(){
        std::cerr<<"Adieu photo " + this->getName() + "\n"<<std::endl;
    };
    
    int getWidth() const{ 
        return width; 
    };
    
    int getHeight() const{ 
        return height; 
    };
    
    void setWidth(int width){
        this->width = width; 
    };
    
    void setHeight(int height){
        this->height = height; 
    };
    
    void display(std::ostream &stream) const override{
        MultimediaObject::display(stream);
        stream << "Width: " << this->getWidth() << std::endl;
        stream << "Height: " << this->getHeight() << std::endl;
    };
    void play() const override{
        std::cout << "Displaying photo " << this->getName() << " from " << this->getPathname() << std::endl;
        system(("imagej " + this->getPathname() + " &").c_str());
    };
};

#endif // PHOTO_H