#include <iostream>
#include <cmath>
#include "collision_check.h"

//Fonction gérant les collisions
bool collision_check(sp p1,sp p2){
    if ((abs(p1.x - p2.x) == 1 && p1.y == p2.y) || (abs(p1.y - p2.y) == 1 && p1.x == p2.x)){
        return true;
    }
    return false;
}