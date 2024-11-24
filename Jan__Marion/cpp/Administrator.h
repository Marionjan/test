#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

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

/**
 * @file Administrator.h
 * @brief Déclaration de la classe Administrator.
 * 
 * Cette classe gère des objets multimédias (Photo, Vidéo, Film) et des groupes d'objets. 
 * Elle permet de créer, rechercher, afficher et manipuler ces entités.
 */

/** Alias pour une table contenant des objets multimédias. */
using MultimediaTable = std::map<std::string, std::shared_ptr<MultimediaObject>>;

/** Alias pour une table contenant des groupes d'objets multimédias. */
using GroupTable = std::map<std::string, std::shared_ptr<Group>>;

/**
 * @class Administrator
 * @brief Classe permettant de gérer les objets multimédias et les groupes.
 * 
 * La classe Administrator fournit des méthodes pour créer, lire, écrire, 
 * rechercher, afficher et jouer des objets multimédias, ainsi que pour gérer des groupes.
 */
class Administrator {
private:
    MultimediaTable mTable; /**< Table des objets multimédias. */
    GroupTable gTable;      /**< Table des groupes d'objets. */

public:
    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise les tables d'objets et de groupes comme étant vides.
     */
    Administrator();

    /**
     * @brief Constructeur avec paramètres.
     * 
     * Permet d'initialiser un administrateur avec des tables prédéfinies.
     * 
     * @param multimediaTable Table des objets multimédias.
     * @param groupTable Table des groupes.
     */
    Administrator(MultimediaTable multimediaTable, GroupTable groupTable);

    /**
     * @brief Écrit un objet multimédia dans un fichier.
     * 
     * @param name Nom de l'objet multimédia.
     * @param out Flux de sortie pour l'écriture.
     */
    void writeToFile(const std::string& name, std::ofstream& out) const;

    /**
     * @brief Lit un objet multimédia depuis un fichier.
     * 
     * @param name Nom de l'objet multimédia.
     * @param in Flux d'entrée pour la lecture.
     */
    void readFromFile(const std::string& name, std::ifstream& in);

    /**
     * @brief Crée une photo.
     * 
     * @param name Nom de la photo.
     * @param pathname Chemin vers le fichier de la photo.
     * @param width Largeur de la photo.
     * @param height Hauteur de la photo.
     */
    void createPhoto(const std::string& name, const std::string& pathname, int width, int height);

    /**
     * @brief Crée une vidéo.
     * 
     * @param name Nom de la vidéo.
     * @param pathname Chemin vers le fichier de la vidéo.
     * @param duration Durée de la vidéo en secondes.
     */
    void createVideo(const std::string& name, const std::string& pathname, int duration);

    /**
     * @brief Crée un film.
     * 
     * @param name Nom du film.
     * @param pathname Chemin vers le fichier du film.
     * @param duration Durée du film en secondes.
     * @param chapters Tableau contenant les durées des chapitres.
     * @param nbChapters Nombre de chapitres dans le film.
     */
    void createFilm(const std::string& name, const std::string& pathname, int duration, int* chapters, int nbChapters);

    /**
     * @brief Crée un groupe vide.
     * 
     * @param name Nom du groupe.
     */
    void createGroup(const std::string& name);

    /**
     * @brief Recherche un objet multimédia par nom et affiche ses informations.
     * 
     * @param name Nom de l'objet multimédial.
     * @param stream Flux de sortie où écrire les informations.
     */
    void searchObject(const std::string& name, std::ostream& stream);

    /**
     * @brief Recherche un groupe par nom et affiche ses informations.
     * 
     * @param name Nom du groupe.
     * @param stream Flux de sortie où écrire les informations.
     */
    void searchGroup(const std::string& name, std::ostream& stream);

    /**
     * @brief Affiche un objet multimédia par nom.
     * 
     * @param name Nom de l'objet multimédia.
     * @param stream Flux de sortie où écrire les informations.
     */
    void display(const std::string& name, std::ostream& stream);

    /**
     * @brief Joue un objet multimédia par nom.
     * 
     * @param name Nom de l'objet multimédia.
     * @param stream Flux de sortie où écrire les messages.
     */
    void play(const std::string& name, std::ostream& stream);
};

#endif // ADMINISTRATOR_H
