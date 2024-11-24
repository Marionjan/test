#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
#include <fstream>
#include "MultimediaObject.h"

/**
 * @file Video.h
 * @brief Déclaration et implémentation de la classe Video.
 * 
 * Cette classe hérite de MultimediaObject et représente une vidéo avec une durée spécifique.
 */

/**
 * @class Video
 * @brief Classe représentant une vidéo avec une durée spécifique.
 */ 

class Video : public MultimediaObject {
private:
    int duration; /**< Durée de la vidéo en secondes. */

public:
    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise une vidéo avec des valeurs par défaut.
     */
    Video() {
        this->setName(" ");
        this->setPathname(" ");
        this->duration = 0;
    }

    /**
     * @brief Constructeur avec paramètres.
     * 
     * @param name Nom de la vidéo.
     * @param pathname Chemin d'accès du fichier vidéo.
     * @param duration Durée de la vidéo en secondes.
     */
    Video(std::string name, std::string pathname, int duration) {
        this->setName(name);
        this->setPathname(pathname);
        this->duration = duration;
    }

    /**
     * @brief Destructeur.
     * 
     * Affiche un message indiquant la destruction de la vidéo.
     */
    virtual ~Video() {
        std::cerr << "Adieu video " + this->getName() + "\n" << std::endl;
    }

    /**
     * @brief Écrit les informations de la vidéo dans un fichier.
     * 
     * Cette méthode inclut la durée de la vidéo.
     * 
     * @param out Flux de sortie vers lequel écrire les informations.
     */
    void writeToFile(std::ofstream& out) const override {
        MultimediaObject::writeToFile(out);
        out << "Duration: " << this->getDuration() << std::endl;
    }

    /**
     * @brief Lit les informations d'une vidéo depuis un fichier.
     * 
     * @param in Flux d'entrée contenant les informations de la vidéo.
     * @return Un objet Video initialisé avec les données du fichier.
     */
    Video readFromFile(std::ifstream& in) {
        std::string name, pathname;
        int duration;
        in >> name >> pathname >> duration;
        return Video(name, pathname, duration);
    }

    /**
     * @brief Obtient la durée de la vidéo.
     * 
     * @return La durée en secondes.
     */
    int getDuration() const { 
        return duration; 
    }

    /**
     * @brief Définit la durée de la vidéo.
     * 
     * @param duration La nouvelle durée en secondes.
     */
    void setDuration(int duration) {
        this->duration = duration; 
    }

    /**
     * @brief Affiche les informations de la vidéo dans un flux.
     * 
     * Les informations incluent le nom, le chemin d'accès et la durée.
     * 
     * @param stream Flux dans lequel afficher les informations.
     */
    void display(std::ostream &stream) const override {
        MultimediaObject::display(stream);
        stream << "Duration: " << this->getDuration() << std::endl;
    }

    /**
     * @brief Joue la vidéo en utilisant un lecteur multimédia.
     * 
     * Cette méthode utilise la commande système `mpv` pour lire la vidéo.
     */
    void play() const override {
        std::cout << "Playing video " << this->getName() << " from " << this->getPathname() << std::endl;
        system(("mpv " + this->getPathname() + " &").c_str());
    }
};

#endif // VIDEO_H
