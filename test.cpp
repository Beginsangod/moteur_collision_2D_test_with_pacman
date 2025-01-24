#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>

#include "player.h"

using namespace std;

// Fonction pour afficher le repère
void afficherRepere(sprite obj, int largeur, int hauteur, char grille[15][35]) {

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
            else if(i == 0 || i == 14 || j == 0 || j == 34)
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(j == 2 && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(j == 32 && (i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(i == 2 && (j == 10 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 16 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 || j == 24 || j == 25))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(i == 12 && (j == 10 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 16 || j == 18 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 || j == 24 || j == 25))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if((i == 5 || i == 9) && (j == 10 || j == 11 || j == 12 || j == 13 || j == 14 || j == 15 || j == 19 || j == 20 || j == 21 || j == 22 || j == 23 || j == 24 || j == 25))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if((j == 9 || j == 26) && (i == 5 || i == 6 || i == 7 || i == 8 || i == 9))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(j == 6 && (i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 12))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else if(j == 29 && (i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || i == 12))
            {
                grille[i][j] = 35;
                cout << "#";
            }
            else
            {
                grille[i][j] = '.';
                cout << " ";
            }
        }
        std::cout << std::endl; 
    }
}

int main() {
    sprite pacman(1, 1, 112);

    int largeur = 15; // Largeur du repère
    int hauteur = 35; // Hauteur du repère
    char grille[15][35]; // Grille 2D pour le repere

    while (true) {
        system("clear"); // Effacer la console..
        afficherRepere(pacman, largeur, hauteur, grille);
        this_thread::sleep_for(chrono::milliseconds(100)); // Attendre 100 ms
   
        // Deplacer pacman
        pacman = player::deplacement(pacman, grille);

    }

    return 0;
}


