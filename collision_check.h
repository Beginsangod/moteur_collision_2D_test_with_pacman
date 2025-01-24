#include <cmath>
#define COLLISION_CHECK_INCLUDED
#ifdef COLLISION_CHECK_INCLUDED

//classe pour definir les sprites
class sprite
{
    public:
        int x;
        int y;
        char symbol;

        sprite(int x, int y, char symbol = 1) : x(x) , y(y) , symbol(symbol) {}

        static bool collision_check(sprite& p1,sprite& p2){
        if ((abs(p1.x - p2.x) == 1 && p1.y == p2.y) || (abs(p1.y - p2.y) == 1 && p1.x == p2.x)){
            return true;
        }
        return false;
        }
};

#endif