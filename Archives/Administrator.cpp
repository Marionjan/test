#ifndef ADMINISTRATOR_CPP
#define ADMINISTRATOR_CPP

#include <map>
#include <string>
#include <memory>
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

void Administrator::searchObject(const std::string& name){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        std::cout << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(std::cout);        
    }
}

void Administrator::searchGroup(const std::string& name){
    auto grp = gTable.find(name); // recherche
    if (grp == gTable.end()) {
        std::cout << "Le groupe n'a pas été trouvé" << std::endl;
    } else {
        grp->second->displayGroup(std::cout);        
    }
}

void Administrator::display(const std::string& name){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        std::cout << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(std::cout);        
    }
}

void Administrator::play(const std::string& name){
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        std::cout << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->play();        
    }
}


#endif // ADMINISTRATOR_CPP