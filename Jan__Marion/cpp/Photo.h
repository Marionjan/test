#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include <iostream>
#include <fstream>
#include "MultimediaObject.h"

/**
 * @file Photo.h
 * @brief Déclaration et implémentation de la classe Photo.
 * 
 * Cette classe hérite de MultimediaObject et représente une photo avec des dimensions spécifiques.
 */

/**
 * @class Photo
 * @brief Classe représentant une photo avec des dimensions spécifiques.
 */

class Photo : public MultimediaObject {
private:
    int width;   /**< Largeur de la photo en pixels. */
    int height;  /**< Hauteur de la photo en pixels. */

public: 
    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise une photo avec des valeurs par défaut.
     */
    Photo() {
        this->setName(" ");
        this->setPathname(" ");
        this->width = 0;
        this->height = 0;
    }
    
    /**
     * @brief Constructeur avec paramètres.
     * 
     * @param name Nom de la photo.
     * @param pathname Chemin d'accès du fichier photo.
     * @param width Largeur de la photo.
     * @param height Hauteur de la photo.
     */
    Photo(std::string name, std::string pathname, int width, int height) {
        this->setName(name);
        this->setPathname(pathname);
        this->width = width;
        this->height = height;
    }
    
    /**
     * @brief Destructeur.
     * 
     * Affiche un message indiquant la destruction de la photo.
     */
    virtual ~Photo() {
        std::cerr << "Adieu photo " + this->getName() + "\n" << std::endl;
    }
    
    /**
     * @brief Écrit les informations de la photo dans un fichier.
     * 
     * Cette méthode inclut les dimensions de la photo.
     * 
     * @param out Flux de sortie vers lequel écrire les informations.
     */
    void writeToFile(std::ofstream& out) const override {
        MultimediaObject::writeToFile(out);
        out << "Width: " << this->getWidth() << std::endl;
        out << "Height: " << this->getHeight() << std::endl;
    }

    /**
     * @brief Lit les informations d'une photo depuis un fichier.
     * 
     * @param in Flux d'entrée contenant les informations de la photo.
     * @return Un objet Photo initialisé avec les données du fichier.
     */
    Photo readFromFile(std::ifstream& in) {
        std::string name, pathname;
        int width, height;
        in >> name >> pathname >> width >> height;
        return Photo(name, pathname, width, height);
    }

    /**
     * @brief Obtient la largeur de la photo.
     * 
     * @return La largeur en pixels.
     */
    int getWidth() const { 
        return width; 
    }
    
    /**
     * @brief Obtient la hauteur de la photo.
     * 
     * @return La hauteur en pixels.
     */
    int getHeight() const { 
        return height; 
    }
    
    /**
     * @brief Définit la largeur de la photo.
     * 
     * @param width La nouvelle largeur en pixels.
     */
    void setWidth(int width) {
        this->width = width; 
    }
    
    /**
     * @brief Définit la hauteur de la photo.
     * 
     * @param height La nouvelle hauteur en pixels.
     */
    void setHeight(int height) {
        this->height = height; 
    }
    
    /**
     * @brief Affiche les informations de la photo dans un flux.
     * 
     * Les informations incluent le nom, le chemin d'accès, et les dimensions.
     * 
     * @param stream Flux dans lequel afficher les informations.
     */
    void display(std::ostream &stream) const override {
        MultimediaObject::display(stream);
        stream << "Width: " << this->getWidth() << std::endl;
        stream << "Height: " << this->getHeight() << std::endl;
    }
    
    /**
     * @brief Joue la photo en utilisant une visionneuse.
     * 
     * Cette méthode utilise la commande système `imagej` pour afficher la photo.
     */
    void play() const override {
        std::cout << "Displaying photo " << this->getName() << " from " << this->getPathname() << std::endl;
        system(("imagej " + this->getPathname() + " &").c_str());
    }
};

#endif // PHOTO_H
