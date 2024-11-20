#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <iostream>
#include <list>
#include "MultimediaObject.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"


class Group : public std::list<std::shared_ptr<MultimediaObject>> {

private:
    std::string name;
    std::list<std::shared_ptr<MultimediaObject>> objects;

public:
    Group(const std::string& name);

    Group(  const std::string& name, 
            std::list<std::shared_ptr<MultimediaObject>> objects);


    ~Group();

    std::string getName() const;

    void displayGroup(std::ostream &stream) const;
    void playGroup() const;

    void push_back(std::shared_ptr<MultimediaObject> obj);
};

#endif // GROUP_H 