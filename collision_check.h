#define COLLISION_CHECK_INCLUDED
#ifdef COLLISION_CHECK_INCLUDED

//type pour definir les sprites
typedef struct sprite{
    int x;
    int y;
    char symbol;
} sp;

bool collision_check(sp p1,sp p2);

#endif