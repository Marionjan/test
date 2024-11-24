#ifndef GROUP_CPP
#define GROUP_CPP

#include <iostream>
#include <list>
#include "Group.h"
#include "MultimediaObject.h"
#include <memory>

/**
 * @file Group.cpp
 * @brief Définition des méthodes de la classe Group.
 */

Group::Group(const std::string& name) : name(name) {}

/**
 * @brief Constructeur avec une liste d'objets multimédias.
 * 
 * Initialise le groupe avec un nom et une liste d'objets.
 * 
 * @param name Nom du groupe.
 * @param objects Liste des objets multimédias.
 */
Group::Group(   const std::string& name, 
                std::list<std::shared_ptr<MultimediaObject>> objects) 
                : name(name), objects(objects) {}

Group::~Group() {
    objects.clear();
    std::cerr << "Adieu groupe " << this->getName() << std::endl;
}

std::string Group::getName() const {
    return name;
}

/**
 * @brief Affiche les informations des objets multimédias dans le groupe.
 * 
 * Si aucun objet n'est présent, un message approprié est affiché.
 * 
 * @param stream Flux de sortie pour afficher les informations.
 */
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

/**
 * @brief Joue tous les objets du groupe.
 * 
 * Cette méthode appelle la fonction `play` pour chaque objet du groupe.
 */
void Group::playGroup() const {
    for (const auto& obj : *this) {
        obj->play();
    }
}

/**
 * @brief Ajoute un objet multimédia au groupe.
 * 
 * @param obj Un objet multimédia à ajouter.
 */
void Group::push_back(std::shared_ptr<MultimediaObject> obj) {
    objects.push_back(obj);
}

#endif // GROUP_CPP
