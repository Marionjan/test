#ifndef MULTIMEDIAOBJECT_H
#define MULTIMEDIAOBJECT_H

#include <string>
#include <iostream>
#include <fstream>

/**
 * @file MultimediaObject.h
 * @brief Déclaration de la classe MultimediaObject.
 * 
 * Cette classe représente un objet multimédia de base. 
 * Elle contient des informations comme le nom et le chemin d'accès de l'objet.
 */

/**
 * @class MultimediaObject
 * @brief Classe représentant un objet multimédia de base.
 */

class MultimediaObject {
private:
    std::string name;      /**< Nom de l'objet multimédia. */
    std::string pathname;  /**< Chemin d'accès du fichier multimédia. */

public:
    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise l'objet avec des valeurs par défaut.
     */
    MultimediaObject();

    /**
     * @brief Constructeur avec paramètres.
     * 
     * @param name Nom de l'objet multimédia.
     * @param pathname Chemin d'accès du fichier multimédia.
     */
    MultimediaObject(std::string name, std::string pathname);

    /**
     * @brief Destructeur.
     * 
     * Affiche un message indiquant la destruction de l'objet.
     */
    virtual ~MultimediaObject();

    /**
     * @brief Obtient le nom de l'objet multimédia.
     * 
     * @return Le nom de l'objet.
     */
    std::string getName() const;

    /**
     * @brief Obtient le chemin d'accès de l'objet multimédia.
     * 
     * @return Le chemin d'accès du fichier.
     */
    std::string getPathname() const;

    /**
     * @brief Définit le nom de l'objet multimédia.
     * 
     * @param name Le nouveau nom de l'objet.
     */
    void setName(std::string name);

    /**
     * @brief Définit le chemin d'accès de l'objet multimédia.
     * 
     * @param pathname Le nouveau chemin d'accès.
     */
    void setPathname(std::string pathname);

    /**
     * @brief Écrit les informations de l'objet dans un fichier.
     * 
     * @param out Flux de sortie vers lequel écrire les informations.
     */
    virtual void writeToFile(std::ofstream& out) const;

    /**
     * @brief Affiche les informations de l'objet dans un flux de sortie.
     * 
     * @param stream Flux dans lequel afficher les informations.
     */
    virtual void display(std::ostream &stream) const;

    /**
     * @brief Affiche l'objet sur le serveur.
     * 
     * @param stream Flux dans lequel s'affiche le statut de l'affichage de l'objet.
     */
    virtual void play(std::ostream &stream) const;
};

#endif // MULTIMEDIAOBJECT_H
