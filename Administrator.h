#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H


#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include "MultimediaObject.h"
#include "Group.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"

using MultimediaTable   = std::map<std::string, std::shared_ptr<MultimediaObject>>; 
using GroupTable        = std::map<std::string, std::shared_ptr<Group>>;

class Administrator {
private:
    MultimediaTable mTable;;
    GroupTable gTable;

public:
    Administrator();
    Administrator(MultimediaTable multimediaTable, GroupTable groupTable);

    void createPhoto(const std::string& name, const std::string& pathname, int width, int height);
    void createVideo(const std::string& name, const std::string& pathname, int duration);
    void createFilm(const std::string& name, const std::string& pathname, int duration, int *chapters, int nbChapters);

    void createGroup(const std::string& name);

    void searchObject(const std::string& name);
    void searchGroup(const std::string& name);

    void Administrator::display(const std::string& name, std::ostream &stream);

    void play(const std::string& name);
};

    


#endif // ADMINISTRATOR_H
