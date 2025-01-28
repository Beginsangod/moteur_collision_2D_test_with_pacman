#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "mobs.h"
#include "gest_bonus.h"

using namespace std;

// Fonction pour afficher le repère
void afficherRepere(sprite obj, int largeur, int hauteur, char grille[15][35], Bonusgroup bg) {
    srand(time(NULL));
    char mur = 219;
    grille[obj.x][obj.y] = obj.symbol;

    for (int i = 0; i < largeur; i++)
    {
        for (int j = 0; j < hauteur; j++)
        {
            if(i == obj.x && j == obj.y)
            {
                // on affiche pacman en jaune
                std::cout << "\033[33m" << obj.symbol << "\033[0m";
            }
            // Tout ce qui suit dans cette fonction c'est la modelisation de la carte donc le placemant des murs
            else if(i == 0 || i == 14 || j == 0 || j == 34)
            {
                grille[i][j] = 35; // ajouter les blocks du mur aux elements d'un tableau
                cout << mur;
            }
            else if(j == 2 && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if(j == 32 && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((i == 2 || i == 12) && (j == 3 || j == 4 || j == 5 || j == 6 || j == 8 || j == 10 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 16 || j == 17 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 || j == 25 || j == 27 || j == 28 || j == 29 || j == 30 || j == 31))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((j == 4 || j == 5 || j == 29 || j == 30) && (i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((j == 7 || j == 8 || j == 25 || j == 26 || j == 27) && (i == 4 || i == 6 || i == 8 || i == 10))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((j == 10 || j == 23) && (i == 6 || i == 7 || i == 8))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((i == 4 || i == 10) && (j == 10 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 16 || j == 17 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((i == 6) && (j == 11 || j == 12 || j == 13 || j == 14 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((i == 8) && (j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 16 || j == 17 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else if((i == 1 || i == 13) && (j == 8 || j == 25))
            {
                grille[i][j] = 35;
                cout << mur;
            }
            else
            {
                 bonus* bonus = bg.getBonusAt(i, j);
                if (bonus) {
                    std::cout << "\033[32m" << bonus->symbol << "\033[0m"; // Afficher le bonus en vert
                } else {
                    // Ajouter un bonus aléatoire dans les espaces vides
                    int randBonus = rand() % 3;
                    if (randBonus == 0) {
                        bg.addbonus(new pellet(i, j));
                        std::cout << "\033[32m" << bg.bns[i]->symbol << "\033[0m"; // Afficher pellet
                    } else if (randBonus == 1) {
                        bg.addbonus(new super_pellet(i, j));
                        std::cout << "\033[32m" << bg.bns[i]->symbol << "\033[0m"; // Afficher powerPellet
                    } else {
                        bg.addbonus(new joker(i, j));
                        std::cout << "\033[32m" << bg.bns[i]->symbol << "\033[0m"; // Afficher speedBoost
                    }
                }
            }
        }
        std::cout << std::endl; 
    }
}

int main() {
    player pacman(1, 1, 1);
    Bonusgroup bg;

    int largeur = 15; // Largeur du repère
    int hauteur = 35; // Hauteur du repère
    char grille[15][35]; // Grille 2D pour le repere
    bool running = true; //pour la boucle du jeu

    bg.addbonus(new pellet(3, 3));
    bg.addbonus(new super_pellet(5, 5));
    bg.addbonus(new joker(7, 7));

    while (running) {
        #ifdef _WIN32
        system("CLS"); // Effacer la console sur windows
        #elif defined(__linux__) 
        system("clear"); // Effacer la console sur linux
        #endif
        afficherRepere(pacman, largeur, hauteur, grille, bg);
        this_thread::sleep_for(chrono::milliseconds(100)); // Attendre 100 ms
   
        // Deplacer pacman
        pacman.deplacement(grille, running);
    }

    return 0;
}