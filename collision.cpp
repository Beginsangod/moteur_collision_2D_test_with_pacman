#include <iostream>
#include "header.h"

bool collision(struct entites obj_1, struct entites obj_2)
{
    // verification de la collision entre deux objets a partir de leurs coordonnees dans la grille 2D
    if(obj_1.xPos == obj_2.xPos && obj_1.yPos == obj_2.yPos)
    {
        return true;
    }
    return false;
}