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

void initMobs(Mobsgroup& mbs);
void initBonus(Bonusgroup& bg);
void afficherRepere(sprite& obj, int largeur, int score, int hauteur, char grille[15][35], Mobsgroup& mbs,Bonusgroup& bg, player& pacman);

//initialiser les fantomes
void initMobs(Mobsgroup& mbs) {
    mbs.addMob(new mob(6, 15, 1));
    mbs.addMob(new mob(6, 16, 2));
    mbs.addMob(new mob(6, 17, 0));
    mbs.addMob(new mob(6, 18, 3));
}

// Ajoutez quelques bonus aléatoires et regulier
void initBonus(Bonusgroup& bg) {
    srand(time(NULL));
    for (int i = 0; i < 4; i++)
    {
        bg.addbonus(new super_pellet(rand() % 14, rand() % 34));
        bg.addbonus(new joker(rand() %14, rand() % 34));
    }
    
    for (int i = 1; i < 14; i++)
    {
        for (int j = 1; j < 34; j++)
        {
            bg.addbonus(new pellet(i,j));
        }
    }
};

// Fonction pour afficher le repère
void afficherRepere(sprite& obj, int largeur, int score,int hauteur, char grille[15][35], Mobsgroup& mbs,Bonusgroup& bg, player& pacman) {
    char mur = 219;
    grille[obj.x][obj.y] = obj.symbol;

    for (int i = 0; i < largeur; i++)
    {
        for (int j = 0; j < hauteur; j++)
        {
            if(i == pacman.x && j == pacman.y)
            {
                // on affiche pacman en jaune
                std::cout << "\033[33m" << pacman.symbol << "\033[0m";
                // Vérifier les collisions avec les bonus
                bonus* b = bg.getBonusAt(i, j);
                if (b != nullptr) {
                    b->addscore(score, pacman);
                    bg.removeBonus(i, j);
                }   
            }
            // Tout ce qui suit dans cette fonction c'est la modelisation de la carte donc le placemant des murs
            else if(i == 0 || i == 14 || j == 0 || j == 34)
            {
                grille[i][j] = 35;
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
            else
            {
                // Afficher les mobs et les bonus
                mob* m = mbs.getMobsAt(i, j);
                if (m != nullptr) {
                    switch (m->id) {
                        case 0:
                            std::cout << "\033[31m" << m->symbol << "\033[0m"; // Rouge
                            break;
                        case 1:
                            std::cout << "\033[32m" << m->symbol << "\033[0m"; // Vert
                            break;
                        case 2:
                            std::cout << "\033[34m" << m->symbol << "\033[0m"; // Bleu
                            break;
                        case 3:
                            std::cout << "\033[35m" << m->symbol << "\033[0m"; // Violet
                            break;
                    }
                } else {
                    // Afficher les bonus
                    bonus* b = bg.getBonusAt(i, j);
                    if (b != nullptr) {
                        std::cout << b->symbol;
                    } else {
                        std::cout << " ";
                    }
                }
            }
        }
        std::cout << std::endl; 
    }
}

int main() {
    sprite obj(0, 0, 219); // Initialize with appropriate parameters
    player pacman(1, 1, 1);
    Bonusgroup bg;
    Mobsgroup mbs;
    int score = 0;

    int largeur = 15; // Largeur du repère
    int hauteur = 35; // Hauteur du repère
    char grille[15][35]; // Grille 2D pour le repere
    bool running = true; //pour la boucle du jeu

    initMobs(mbs);
    initBonus(bg);

    while (running) {
        #ifdef _WIN32
        system("CLS"); // Effacer la console sur windows
        #elif defined(__linux__) 
        system("clear"); // Effacer la console sur linux
        #endif
        afficherRepere(obj, largeur, score, hauteur, grille, mbs, bg, pacman);
        this_thread::sleep_for(chrono::milliseconds(10)); // Attendre 10 ms
        
        // Deplacer pacman
        pacman.deplacement(grille, running);
        
        for (int i = 0; i < 4; i++)
        {
            mbs.mobs[i]->move(pacman, grille);
            mbs.mobs[i]->kill(pacman);
        }
        mbs.deadcontact(pacman, score);
        if (pacman.life == 0)
        {
            running = false;
        }
    }
    std::cout<< "game over";
    return 0;
}
