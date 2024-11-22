#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H

#include <string>
#include <iostream>

/// @brief Classe de base pour les objets multimédia
class MultimediaObject {
private:
    // Variables d'instance communes à tous les objets multimédia
    std::string name;
    std::string pathname;
    friend class Administrator;

protected:
    //constructeurs, le destructeur, accesseurs, modifieurs
    MultimediaObject();
    
    MultimediaObject(std::string name, std::string pathname);

    virtual void writeToFile(std::ofstream& out) const ;

    virtual ~MultimediaObject();

public:
    std::string getName() const;
    
    std::string getPathname() const;
    
    void setName(std::string name);
    
    void setPathname(std::string pathname);

    virtual void display(std::ostream &stream) const ;
    virtual void play() const = 0;
};

#endif // MULTIMEDIAOBJECT_H