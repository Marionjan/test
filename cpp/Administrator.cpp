#ifndef ADMINISTRATOR_CPP
#define ADMINISTRATOR_CPP

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "MultimediaObject.h"
#include "Group.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Administrator.h"

Administrator::Administrator() {
    std::cerr << "Empty Administrator created" << std::endl;
    MultimediaTable mTable;
    GroupTable gTable;
}

Administrator::Administrator(MultimediaTable multimediaTable, GroupTable groupTable){
    std::cerr << "New Administrator created" << std::endl;
    mTable = multimediaTable;
    gTable = groupTable;
}

void Administrator::writeToFile(const std::string& name, std::ofstream& out) const {
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        out << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->writeToFile(out);        
    }
}
void Administrator::readFromFile(const std::string& name, std::ifstream& in){
    std::string type;
    in >> type;
    if (type == "Photo") {
        std::string name, pathname;
        int width, height;
        in >> name >> pathname >> width >> height;
        createPhoto(name, pathname, width, height);
    } else if (type == "Video") {
        std::string name, pathname;
        int duration;
        in >> name >> pathname >> duration;
        createVideo(name, pathname, duration);
    } else if (type == "Film") {
        std::string name, pathname;
        int duration, nbChapters;
        in >> name >> pathname >> duration >> nbChapters;
        int* chapters = new int[nbChapters];
        for (int i = 0; i < nbChapters; i++) {
            in >> chapters[i];
        }
        createFilm(name, pathname, duration, chapters, nbChapters);
    }
}

void Administrator::createPhoto(    const std::string& name, 
                                    const std::string& pathname, 
                                    int width, 
                                    int height)     {

    mTable[name] = std::make_shared<Photo>(name, pathname, width, height);
}

void Administrator::createVideo(    const std::string& name, 
                                    const std::string& pathname, 
                                    int duration)     {

    mTable[name] = std::make_shared<Video>(name, pathname, duration);
}

void Administrator::createFilm(    const std::string& name, 
                                    const std::string& pathname, 
                                    int duration,
                                    int *chapters, 
                                    int nbChapters)     {

    mTable[name] = std::make_shared<Film>(name, pathname, duration, chapters, nbChapters);
}

void Administrator::createGroup(const std::string& name){
    gTable[name] = std::make_shared<Group>(name);
}

void Administrator::searchObject(const std::string& name, std::ostream &stream){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(stream);        
    }
}

void Administrator::searchGroup(const std::string& name, std::ostream &stream){
    auto grp = gTable.find(name); // recherche
    if (grp == gTable.end()) {
        stream << "Le groupe n'a pas été trouvé" << std::endl;
    } else {
        grp->second->displayGroup(stream);        
    }
}

void Administrator::display(const std::string& name, std::ostream &stream){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(stream);        
    }
}

void Administrator::play(const std::string& name, std::ostream &stream){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->play();
        stream << "Regardez votre set-top box" << std::endl;        
    }
}


#endif // ADMINISTRATOR_CPP