#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

#include "header.h"

int main()
{

    const int hauteur = 15;
    const int largeur = 35;
    char touche;

    // Initialisation de la grille avec des espaces
    std::vector<std::vector<char>>grille(hauteur, std::vector<char>(largeur, ' '));

    // Declaration de la liste d'objets de type entites
    std::vector<entites> objets;
     
    // Creation de la liste des objets qui vont constituer le murs sur la map 
    ajout_des_objets(objets);

    // Creation du perso Pac man
    struct entites Pac_man = {'P', 1, 1};

    // Transformation des elements de la liste objets en elements des murs de la map
    ajout_des_murs(grille, objets, Pac_man);

    // Configuration du terminal pour pouvoir recuperer une touche sans tapee sur entrer
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    // Boucle principale
    while(true)
    {
        // Affichage de la grille
        afficher_grille(grille, Pac_man);
 
        // Deplacement de pacman a l'aide de la fonction move_pacman()
        Pac_man = move_pacman(Pac_man, objets, grille);

        // Redefinition generale de la grille
        ajout_des_murs(grille, objets, Pac_man);

        // Attendre 0.4 secondes avant d'effacer la console
        usleep(400000);
        system("clear");
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return 0;
}