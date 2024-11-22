#ifndef GROUP_CPP
#define GROUP_CPP

#include <iostream>
#include <list>
#include "Group.h"
#include "MultimediaObject.h"
#include <memory>


Group::Group(const std::string& name) : name(name) {}

Group::Group(   const std::string& name, 
                std::list<std::shared_ptr<MultimediaObject>> objects) 
                : name(name), objects(objects) {}

Group::~Group() {
    objects.clear();
    std::cerr<<"Adieu groupe " + this->getName() + "\n"<<std::endl;
}

std::string Group::getName() const {
    return name;
}

void Group::displayGroup(std::ostream &stream) const {
    for (const auto& obj : objects) { 
        if (obj) { 
            obj->display(stream);  
        }
        else {
            stream << "No objects in this group" << std::endl;
        }
        stream << std::endl;
    }
}

void Group::playGroup() const {
    for (const auto& obj : *this) {
        obj->play();
    }
}

void Group::push_back(std::shared_ptr<MultimediaObject> obj) {
        objects.push_back(obj);
    }


#endif // GROUP_CPP