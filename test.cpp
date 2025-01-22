#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include "collision_check.h"

using namespace std;

// Fonction pour afficher le repère
void afficherRepere(sp m, sp m1, int largeur, int hauteur) {
    m.symbol = 1;
    m1.symbol = 1;
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (i == m.y && j == m.x) {
                cout << "\033[34m"<<m.symbol<<"\033[37m"; // Marqueur de position
            }else if (i == m1.y && j == m1.x) {
                cout << "\033[32m"<<m1.symbol<<"\033[37m"; // Marqueur de position
            } else {
                cout << "."; // Repère
            }
        }
        cout << endl;
    }
}

int main() {
    sp m, m1;
    m.x = 0; //Position initiale x m
    m.y = 0; //Position initiale y m
    m.symbol = 1;
    m1.x = 10; //Position initiale x m1
    m1.y = 0; //Position initiale y m1
    m1.symbol = 1;
    int largeur = 10; // Largeur du repère
    int hauteur = 10; // Hauteur du repère
    int deplacementX = 1; // Déplacement en x
    int deplacementY = 0; // Déplacement en y

    while (true) {
        system("CLS"); // Effacer la console..
        afficherRepere(m, m1, largeur, hauteur);
        this_thread::sleep_for(chrono::milliseconds(1000)); // Attendre 100 ms

        if (!collision_check(m,m1))
        {
            m1.x -= deplacementX;
            m1.y -= deplacementY;
        }

        if (!collision_check(m,m1))
        {
            // Déplacer le marqueur
            m.x += deplacementX;
            m.y += deplacementY;
        }
        // Rebondir sur les bords
        if (m.x < 0 || m.x >= largeur) {
            deplacementX = -deplacementX;
        }
        if (m.y < 0 || m.y >= hauteur) {
            deplacementY = -deplacementY;
        }

        if (m1.x < 0 || m1.x >= largeur) {
            deplacementX = -deplacementX;
        }
        if (m1.y < 0 || m1.y >= hauteur) {
            deplacementY = -deplacementY;
        }

    }

    return 0;
}