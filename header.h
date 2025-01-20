#ifndef __header_H_INCLUDED__
#define __header_H_INCLUDED__

#include <iostream>
#include <vector>

// Cette structure enitites est le type de donnee qui sera assigne a tout les enites de la map
// D'ou le symbole ASCII et sa position dans la grille
struct entites
{
    char symbole;
    int xPos;
    int yPos;
};

// Affichage de la grille
void afficher_grille(const std::vector<std::vector<char>>& grille, struct entites& Pac_man);

//definition des objets ou entites constitutifs de la grille
void ajout_des_objets(std::vector<entites>& objets);

// transformation des objets ou entites en elements de la grille 2D
void ajout_des_murs(std::vector<std::vector<char>>& grille, std::vector<entites>& objets, struct entites& Pac_man);

// Cette fonction collision() retourne vrai si deux objets entrent en contact et faux sinon
bool collision(struct entites obj_1, struct entites obj_2);

// la fonction touche lue reccupere la touche tapee par l'utilisateur
char touche_lue();

// move_pacman() permet d'effectuer le deplacement de Pacman en fonction de la touche tapee(wsad)
struct entites move_pacman(struct entites& Pac_man, std::vector<entites>& objets, std::vector<std::vector<char>>& grille);

#endif 