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

        // Fonction pour la gestion des deplacements de pacman
        static sprite deplacement(sprite obj, char grille[15][35])
        {
            char touche;
            #ifdef _WIN32
            touche = getch();
            #elif defined(__linux__)
            read(0, &touche, 1);
            #endif

            if(touche == 'w') // Monter
            {  
                if(grille[obj.x - 1][obj.y] == 35) // verifier si la position cibler est un mur
                {
                    // ne pas deplacer le joueur si c'est un mur 
                    return obj;
                }
                else 
                {
                    // deplacer le jouer si ce n'est pas une mur
                    obj.x--;
                    return obj;
                }
            }
            else if(touche == 's') // Descendre
            {
                if(grille[obj.x + 1][obj.y] == 35)
                {
                    return obj;
                }
                else 
                {
                    obj.x++;
                    return obj;
                }
            }
            else if(touche == 'a') // Aller a gauche
            {
                if(grille[obj.x][obj.y - 1] == 35)
                {
                    return obj;
                }
                else
                {
                    obj.y--;
                    return obj;
                }
            }
            else if(touche == 'd') // Aller a doite
            {
               if(grille[obj.x][obj.y + 1] == 35)
                {
                    return obj;
                }
                else
                {
                    obj.y++;
                    return obj;
                } 
            }
            return obj;
        }
};

#endif