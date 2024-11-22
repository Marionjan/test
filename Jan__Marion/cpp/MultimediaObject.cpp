#ifndef MULTIMEDIAOBJECT_CPP
#define MULTIMEDIAOBJECT_CPP

#include "MultimediaObject.h"
#include <string>
#include <iostream>
#include <fstream>

MultimediaObject:: MultimediaObject() {
    name = " ";
    pathname = " ";
}
MultimediaObject::MultimediaObject(std::string name, std::string pathname) : name(name), pathname(pathname) {};



MultimediaObject::~MultimediaObject(){
    std::cerr<<"Adieu undefined object " + this->getName() + "\n"<<std::endl;
};

void MultimediaObject::writeToFile(std::ofstream& out) const {
    out << "Name: " << this->getName() << std::endl;
    out << "Pathname: " << this->getPathname() << std::endl;
}

std::string MultimediaObject::getName() const{
    return name; 
}

std::string MultimediaObject::getPathname() const{ 
    return pathname; 
}

void MultimediaObject::setName(std::string name){
    this->name = name; 
};

void MultimediaObject::setPathname(std::string pathname){
    this->pathname = pathname; 
};

// méthode d'affichage 
void MultimediaObject::display(std::ostream &stream) const{
    stream << "Name: " << this->getName() << std::endl;
    stream << "Pathname: " << this->getPathname() << std::endl;
};

#endif // MULTIMEDIAOBJECT_CPP