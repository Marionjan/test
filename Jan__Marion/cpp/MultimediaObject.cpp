#ifndef MULTIMEDIAOBJECT_CPP
#define MULTIMEDIAOBJECT_CPP

#include "MultimediaObject.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * @file MultimediaObject.cpp
 * @brief Implémentation des méthodes de la classe MultimediaObject.
 */

MultimediaObject::MultimediaObject() {
    name = " ";
    pathname = " ";
}

/**
 * @brief Constructeur avec paramètres.
 * 
 * Initialise l'objet avec un nom et un chemin d'accès donnés.
 * 
 * @param name Nom de l'objet.
 * @param pathname Chemin d'accès du fichier.
 */
MultimediaObject::MultimediaObject(std::string name, std::string pathname) 
    : name(name), pathname(pathname) {}

MultimediaObject::~MultimediaObject() {
    std::cerr << "Adieu undefined object " << this->getName() << std::endl;
}

/**
 * @brief Écrit les informations de l'objet dans un fichier.
 * 
 * Les informations écrites incluent le nom et le chemin d'accès de l'objet.
 * 
 * @param out Flux de sortie.
 */
void MultimediaObject::writeToFile(std::ofstream& out) const {
    out << "Name: " << this->getName() << std::endl;
    out << "Pathname: " << this->getPathname() << std::endl;
}

/**
 * @brief Obtient le nom de l'objet.
 * 
 * @return Le nom actuel de l'objet.
 */
std::string MultimediaObject::getName() const {
    return name; 
}

/**
 * @brief Obtient le chemin d'accès du fichier.
 * 
 * @return Le chemin d'accès actuel.
 */
std::string MultimediaObject::getPathname() const { 
    return pathname; 
}

/**
 * @brief Définit le nom de l'objet.
 * 
 * @param name Le nouveau nom de l'objet.
 */
void MultimediaObject::setName(std::string name) {
    this->name = name; 
}

/**
 * @brief Définit le chemin d'accès de l'objet.
 * 
 * @param pathname Le nouveau chemin d'accès.
 */
void MultimediaObject::setPathname(std::string pathname) {
    this->pathname = pathname; 
}

/**
 * @brief Affiche les informations de l'objet dans un flux.
 * 
 * Les informations affichées incluent le nom et le chemin d'accès.
 * 
 * @param stream Flux de sortie (e.g., `std::cout`).
 */
void MultimediaObject::display(std::ostream &stream) const {
    stream << "Name: " << this->getName() << std::endl;
    stream << "Pathname: " << this->getPathname() << std::endl;
}

#endif // MULTIMEDIAOBJECT_CPP
