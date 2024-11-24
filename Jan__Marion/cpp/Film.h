#ifndef FILM_H
#define FILM_H

#include <string>
#include "Video.h"

/**
 * @file Film.h
 * @brief Déclaration de la classe Film.
 * 
 * La classe Film hérite de Video et représente un film découpé en chapitres.
 * Elle permet de manipuler les chapitres et de jouer le film en spécifiant les limites des chapitres.
 */
class Film : public Video {
private:
    int* chapters; /**< Tableau contenant les durées des chapitres en secondes. */
    int nbChapters; /**< Nombre total de chapitres dans le film. */

public:
    /**
     * @brief Constructeur par défaut.
     */
    Film();

    /**
     * @brief Constructeur avec paramètres.
     * 
     * @param name Nom du film.
     * @param pathname Chemin vers le fichier du film.
     * @param duration Durée totale du film en secondes.
     * @param chapters Tableau contenant les durées des chapitres.
     * @param nbChapters Nombre total de chapitres.
     */
    Film(std::string name, std::string pathname, int duration, int* chapters, int nbChapters);

    /**
     * @brief Destructeur.
     * Libère la mémoire allouée pour le tableau des chapitres.
     */
    ~Film();

    /**
     * @brief Définit les chapitres du film.
     * 
     * @param chapters Tableau contenant les durées des chapitres.
     * @param nbChapters Nombre total de chapitres.
     */
    void setChapters(int* chapters, int nbChapters);

    /**
     * @brief Retourne le tableau des chapitres.
     * 
     * @return Un pointeur vers le tableau des chapitres.
     */
    int* getChapters() const;

    /**
     * @brief Retourne le nombre total de chapitres.
     * 
     * @return Nombre de chapitres.
     */
    int getNbChapters() const;

    /**
     * @brief Affiche les informations du film, y compris les chapitres.
     * 
     * @param stream Flux dans lequel afficher les informations.
     */
    void display(std::ostream& stream) const override;

    /**
     * @brief Joue le film à l'aide du lecteur vidéo.
     * 
     * Cette méthode utilise un appel système pour jouer le fichier avec `mpv`.
     */
    void play() const override;

    /**
     * @brief Écrit les informations du film dans un fichier.
     * 
     * @param out Flux de sortie.
     */
    void writeToFile(std::ofstream& out) const;

    /**
     * @brief Lit les informations d'un film depuis un fichier.
     * 
     * @param in Flux d'entrée.
     * @return Un objet Film créé à partir des données lues.
     */
    static Film readFromFile(std::ifstream& in);
};

#endif // FILM_H
