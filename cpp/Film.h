#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>
#include "Video.h"

class Film : public Video {
private:
    // Variables d'instance spécifiques aux films
    int* chapters;
    int nbChapters;
public:
    Film();
    Film(std::string name, std::string pathname, int duration, int *chapters, int nbChapters);

    virtual ~Film();
    void writeToFile(std::ofstream& out) const override;
    Film readFromFile(std::ifstream& in) ;

    void setChapters(int* chapters, int nbChapters);

    int *getChapters() const;
    
    int getNbChapters() const;
    
    void display(std::ostream &stream) const override;

    void play() const override;

};
#endif // FILM_H