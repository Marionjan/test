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

/**
 * @file Administrator.cpp
 * @brief Implémente la classe Administrator pour gérer les objets multimédias et les groupes.
 * 
 * La classe Administrator permet de créer, rechercher, afficher et gérer des objets multimédias
 * (Photo, Vidéo, Film) et des groupes d'objets. Elle gère également la lecture et l'écriture dans des fichiers.
 */

/**
 * @brief Constructeur par défaut.
 * 
 * Crée un administrateur vide avec des tables d'objets et de groupes initialisées.
 */
Administrator::Administrator() {
    std::cerr << "Empty Administrator created" << std::endl;
    MultimediaTable mTable;
    GroupTable gTable;
}

/**
 * @brief Constructeur avec tables d'objets et de groupes.
 * 
 * @param multimediaTable La table des objets multimédias.
 * @param groupTable La table des groupes.
 */
Administrator::Administrator(MultimediaTable multimediaTable, GroupTable groupTable) {
    std::cerr << "New Administrator created" << std::endl;
    mTable = multimediaTable;
    gTable = groupTable;
}

/**
 * @brief Écrit un objet multimédia dans un fichier.
 * 
 * @param name Le nom de l'objet multimédia.
 * @param out Flux de sortie pour écrire les données.
 */
void Administrator::writeToFile(const std::string& name, std::ofstream& out) const {
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        out << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->writeToFile(out);        
    }
}

/**
 * @brief Lit un objet multimédia depuis un fichier.
 * 
 * @param name Le nom de l'objet multimédia.
 * @param in Flux d'entrée pour lire les données.
 */
void Administrator::readFromFile(const std::string& name, std::ifstream& in) {
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

/**
 * @brief Crée une photo.
 * 
 * @param name Nom de la photo.
 * @param pathname Chemin du fichier.
 * @param width Largeur de la photo.
 * @param height Hauteur de la photo.
 */
void Administrator::createPhoto(const std::string& name, const std::string& pathname, int width, int height) {
    mTable[name] = std::make_shared<Photo>(name, pathname, width, height);
}

/**
 * @brief Crée une vidéo.
 * 
 * @param name Nom de la vidéo.
 * @param pathname Chemin du fichier.
 * @param duration Durée de la vidéo.
 */
void Administrator::createVideo(const std::string& name, const std::string& pathname, int duration) {
    mTable[name] = std::make_shared<Video>(name, pathname, duration);
}

/**
 * @brief Crée un film.
 * 
 * @param name Nom du film.
 * @param pathname Chemin du fichier.
 * @param duration Durée du film.
 * @param chapters Tableau des durées des chapitres.
 * @param nbChapters Nombre de chapitres.
 */
void Administrator::createFilm(const std::string& name, const std::string& pathname, int duration, int* chapters, int nbChapters) {
    mTable[name] = std::make_shared<Film>(name, pathname, duration, chapters, nbChapters);
}

/**
 * @brief Crée un groupe vide.
 * 
 * @param name Nom du groupe.
 */
void Administrator::createGroup(const std::string& name) {
    gTable[name] = std::make_shared<Group>(name);
}

/**
 * @brief Recherche un objet multimédia par nom et l'affiche.
 * 
 * @param name Nom de l'objet multimédia.
 * @param stream Flux de sortie où écrire les informations.
 */
void Administrator::searchObject(const std::string& name, std::ostream& stream) {
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(stream);        
    }
}

/**
 * @brief Recherche un groupe par nom et l'affiche.
 * 
 * @param name Nom du groupe.
 * @param stream Flux de sortie où écrire les informations.
 */
void Administrator::searchGroup(const std::string& name, std::ostream& stream) {
    auto grp = gTable.find(name); // recherche
    if (grp == gTable.end()) {
        stream << "Le groupe n'a pas été trouvé" << std::endl;
    } else {
        grp->second->displayGroup(stream);        
    }
}

/**
 * @brief Affiche un objet multimédia par nom.
 * 
 * @param name Nom de l'objet multimédia.
 * @param stream Flux de sortie où écrire les informations.
 */
void Administrator::display(const std::string& name, std::ostream& stream) {
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->display(stream);        
    }
}

/**
 * @brief Joue un objet multimédia par nom.
 * 
 * @param name Nom de l'objet multimédia.
 * @param stream Flux de sortie où écrire les informations.
 */
void Administrator::play(const std::string& name, std::ostream& stream) {
    auto obj = mTable.find(name); // recherche
    if (obj == mTable.end()) {
        stream << "L'objet n'a pas été trouvé" << std::endl;
    } else {
        obj->second->play();
        stream << "Regardez votre set-top box" << std::endl;        
    }
}

#endif // ADMINISTRATOR_CPP
