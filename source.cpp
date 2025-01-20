#include "header.h"

#include <iostream>
#include <vector>
#include <unistd.h>

void ajout_des_objets(std::vector<entites>& objets)
{
    //ici on definit une liste d'objets qui vont constituer les murs de la map
    // Il est necessaire d'en faire des objets pour car la fonction collision n'est utilisee que sur deux objets
    // la liste <objets> est une liste d'elements de type struct entites{}
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            if(i == 0 || i == 14 || j == 0 || j == 34)
            {
                objets.push_back({'#', i, j});
            }
        }
    }

    int j = 2;
    for (int i = 2; i < 7; i++)
    {
        objets.push_back({'#', i, j});
    }
    for (int i = 8; i < 13; i++)
    {
        objets.push_back({'#', i, j});
    }

    int line = 2;
    for (int col = 2; col < 7; col++)
    {
        objets.push_back({'#', line, col});
    }
    for (int col = 2; col < 7; col++)
    {
        objets.push_back({'#', 12, col});
    }
    int col = 8;
    for (line = 0; line < 3; line++)
    {
        objets.push_back({'#', line, col});
    }
    for (line = 12; line < 15; line++)
    {
        objets.push_back({'#', line, col});
    }
    line = 2;
    for (int i = 10; i < 24; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 10; i < 24; i++)
    {
        objets.push_back({'#', 12, i});
    }
    col = 25;
    for (line = 0; line < 3; line++)
    {
        objets.push_back({'#', line, col});
    }
    for (line = 12; line < 15; line++)
    {
        objets.push_back({'#', line, col});
    }
    j = 32;
    for (int i = 2; i < 7; i++)
    {
        objets.push_back({'#', i, j});
    }
    for (int i = 8; i < 13; i++)
    {
        objets.push_back({'#', i, j});
    }
    line = 2;
    for (int col = 27; col < 32; col++)
    {
        objets.push_back({'#', line, col});
    }
    for (int col = 27; col < 32; col++)
    {
        objets.push_back({'#', 12, col});
    }
    line = 10;
    for (int i = 10; i < 24; i++)
    {
        objets.push_back({'#', line, i});
    }
    line = 4;
    for (int i = 10; i < 15; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 19; i < 24; i++)
    {
        objets.push_back({'#', line, i});
    }
    col = 10;
    for (int i = 5; i < 10; i++)
    {
        objets.push_back({'#', i, col});
    }
    for (int i = 5; i < 10; i++)
    {
        objets.push_back({'#', i, 23});
    }
    line = 6;
    for (int i = 7; i < 9; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 25; i < 28; i++)
    {
        objets.push_back({'#', line, i});
    }
    line = 8;
    for (int i = 7; i < 9; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 25; i < 28; i++)
    {
        objets.push_back({'#', line, i});
    }
    col = 4;
    for (int i = 4; i < 11; i++)
    {
        objets.push_back({'#', i, col});
    }
    col = 30;
    for (int i = 4; i < 11; i++)
    {
        objets.push_back({'#', i, col});
    }
    col = 5;
    for (int i = 4; i < 11; i++)
    {
        objets.push_back({'#', i, col});
    }
    col = 29;
    for (int i = 4; i < 11; i++)
    {
        objets.push_back({'#', i, col});
    }
    line = 4;
    for (int i = 7; i < 9; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 25; i < 28; i++)
    {
        objets.push_back({'#', line, i});
    }
    line = 10;
    for (int i = 7; i < 9; i++)
    {
        objets.push_back({'#', line, i});
    }
    for (int i = 25; i < 28; i++)
    {
        objets.push_back({'#', line, i});
    }
}

void ajout_des_murs(std::vector<std::vector<char>>& grille, std::vector<entites>& objets, struct entites& Pac_man)
{
    // ici on transforme les elements de la liste objet en elements de la grille
    for(auto& entite : objets)
    {
        grille[entite.xPos][entite.yPos] = entite.symbole;
    }

    // en meme temps, on creait une image de l'entite Pac man dans la grille
    grille[Pac_man.xPos][Pac_man.yPos] = Pac_man.symbole;
}

void afficher_grille(const std::vector<std::vector<char>>& grille, struct entites& Pac_man)
{
    // cette fonction affiche les elements de la grille dans la console
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            if(i == Pac_man.xPos && j == Pac_man.yPos)
            {
                // on affiche pacman en jaune
                std::cout << "\033[33m" << grille[Pac_man.xPos][Pac_man.yPos] << "\033[0m";
            }
            else
            {
                std::cout << grille[i][j];
            }
        }
        std::cout << std::endl; 
    }
}

char touche_lue()
{
    // on reccupere la touche tapee par l'utiliateur avec read
    char touche;
    read(STDIN_FILENO, &touche, 1);
    return touche;
}

struct entites move_pacman(struct entites& Pac_man, std::vector<entites>& objets, std::vector<std::vector<char>>& grille)
{

    // ici,  on effectue les deplacements de Pac_man tout en gerant la collision

    // on va ici a chaque fois verifier la collision entre Pac_man et les objets de la liste objets donc les murs
    // si il ya collision, le mouvement n'est pas effectuer, sinon le mouvement est effectuer
    char touche;
    int detect;
    struct entites intermediares;

    // creation d'une entite intermediare pour tester la collision avant d'effectuer le mouvement de Pac_man
    intermediares.xPos = Pac_man.xPos;
    intermediares.yPos = Pac_man.yPos;
    intermediares.symbole = 'I';

    touche = touche_lue();

    if(touche == 'w')// Faire monter pac_man
    {
        intermediares.xPos--;
        for(auto& entite : objets)
        {
            // verification de la collision entre pac_man et les murs
            detect = collision(intermediares, entite);
            if(detect == true)
            {
                // si la collision est detectee, on reste sur la position innitiale de Pac_man
                grille[intermediares.xPos][intermediares.yPos] = '#';// et aussi on remet le murs en place
                return Pac_man;
            }
        }
        
        // si  la collision n'est pas detectee pour tout les entites du mur, on effectu le mouvement
        grille[Pac_man.xPos][Pac_man.yPos] = ' ';// tout en effacant l'ancienne occurence de Pac_man sur la grille
        Pac_man.xPos = intermediares.xPos;
        grille[intermediares.xPos][intermediares.yPos] = '#';// et aussi on remet le murs en place

        // ces operations sont les meme pour les autres deplacements
    }
    else if(touche == 's')// Faire descendre Pac_man
    {
        intermediares.xPos++;
        for(auto& entite : objets)
        {
            detect = collision(intermediares, entite);
            if(detect == true)
            {
                grille[intermediares.xPos][intermediares.yPos] = '#';
                return Pac_man;
            }
        }
        
        grille[Pac_man.xPos][Pac_man.yPos] = ' ';
        Pac_man.xPos++;
        grille[intermediares.xPos][intermediares.yPos] = '#';
    }
    else if(touche == 'a')// Aller a gauche
    {
        intermediares.yPos--;
        for(auto& entite : objets)
        {
            detect = collision(intermediares, entite);
            if(detect == true)
            {
                grille[intermediares.xPos][intermediares.yPos] = '#';
                return Pac_man;
            }
        }

        grille[Pac_man.xPos][Pac_man.yPos] = ' ';
        Pac_man.yPos--;
        grille[intermediares.xPos][intermediares.yPos] = '#';
    }
    else if(touche == 'd')// Aller a droite
    {
        intermediares.yPos++;
        for(auto& entite : objets)
        {
            detect = collision(intermediares, entite);
            if(detect == true)
            {
                grille[intermediares.xPos][intermediares.yPos] = '#';
                return Pac_man;
            }
        }

        grille[Pac_man.xPos][Pac_man.yPos] = ' ';
        Pac_man.yPos++;
        grille[intermediares.xPos][intermediares.yPos] = '#';
    }
    
    return Pac_man;
}
