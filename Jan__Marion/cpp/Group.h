#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <list>
#include <memory>
#include "MultimediaObject.h"

/**
 * @file Group.h
 * @brief Déclaration de la classe Group.
 * 
 * Cette classe représente un groupe d'objets multimédias.
 * Elle fournit des méthodes pour afficher, jouer, et manipuler les objets du groupe.
 */

/**
 * @class Group
 * @brief Classe représentant un groupe d'objets multimédias.
 */
class Group : public std::list<std::shared_ptr<MultimediaObject>> {
private:
    std::string name; /**< Nom du groupe. */
    std::list<std::shared_ptr<MultimediaObject>> objects; /**< Liste des objets multimédias appartenant au groupe. */

public:
    /**
     * @brief Constructeur avec le nom du groupe.
     * 
     * @param name Nom du groupe.
     */
    Group(const std::string& name);

    /**
     * @brief Constructeur avec nom et liste d'objets.
     * 
     * @param name Nom du groupe.
     * @param objects Liste des objets multimédias.
     */
    Group(const std::string& name, std::list<std::shared_ptr<MultimediaObject>> objects);

    /**
     * @brief Destructeur.
     * Vide la liste des objets lors de la destruction du groupe.
     */
    ~Group();

    /**
     * @brief Récupère le nom du groupe.
     * 
     * @return Le nom du groupe.
     */
    std::string getName() const;

    /**
     * @brief Affiche les informations des objets du groupe.
     * 
     * @param stream Flux dans lequel les informations seront affichées.
     */
    void displayGroup(std::ostream& stream) const;

    /**
     * @brief Joue tous les objets du groupe.
     */
    void playGroup() const;

    /**
     * @brief Ajoute un objet multimédia au groupe.
     * 
     * @param obj Un objet multimédia à ajouter au groupe.
     */
    void push_back(std::shared_ptr<MultimediaObject> obj);
};

#endif // GROUP_H
