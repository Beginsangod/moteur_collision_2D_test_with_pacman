#include "collision_check.h"
#include <stdio.h>


#ifdef _WIN32
#include <conio.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#define PLAYER_INCLUDED
#ifdef PLAYER_INCLUDED

class player : public sprite
{
    public:
        int life = 3;
        player(int x, int y, char symbol = 1) : sprite(x, y, symbol), life(3){};

        // Fonction pour la gestion des deplacements de pacman
        void deplacement(char grille[15][35])
        {    
            #ifdef _WIN32   
            if (_kbhit()) 
            #elif defined(__linux__)
            if (select())
            #endif
            {    
                char touche;
                #ifdef _WIN32
                touche = getch();
                #elif defined(__linux__)
                read(0, &touche, 1);
                #endif

                if(touche == 'w') // Monter
                {  
                    if(grille[x - 1][y] != 35) // verifier si la position cibler est un mur
                    {
                        // deplacer le jouer si ce n'est pas un mur
                        x--;
                    }
                }
                else if(touche == 's') // Descendre
                {
                    if(grille[x + 1][y] != 35)
                    {
                        x++;
                    }
                }
                else if(touche == 'a') // Aller a gauche
                {
                    if(grille[x][y - 1] != 35)
                    {
                        y--;
                    }
                }
                else if(touche == 'd') // Aller a doite
                {
                    if(grille[x][y + 1] != 35)
                    {
                        y++;
                    } 
                }
            }
        }
};

#endif