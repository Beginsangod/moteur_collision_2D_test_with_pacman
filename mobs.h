#include <iostream>
#include "collision_check.h"
#include "player.h"

#define MOBS_INCLUDED
#ifdef MOBS_INCLUDED

//classe pour les monstres
class mob : public sprite{
    public:
        
        mob(int x, int y, char symbol = 1) : sprite(x, y, symbol){};

    void move(player& p)
    {
        
    }
    //Methode pour la gestion des tamponnement avec les joueurs
    void kill(player& p){
        if (sprite::collision_check(*this,p))
        {
            p.life -= 1;
        }
    }
};

class Mobsgroup : public sprite{
    public:
    mob** mobs;
    int size;
    int capacity;
    bool deadmode = false;

    Mobsgroup(int init_capacity = 4) : sprite(0, 0, ' '), size(1), capacity(init_capacity){
        mobs = new mob*[capacity];
    };

    ~Mobsgroup() {
        for (int i = 0; i < size; ++i) {
            delete mobs[i];  // Libérer la mémoire de chaque sprite
        }
        delete[] mobs;  // Libérer le tableau de pointeurs
    }

    void addMob(mob* newMob) {
        if (size >= capacity) {
            capacity *= 2;
            mob** newMobs = new mob*[capacity];
            for (int i = 0; i < size; ++i) {
                newMobs[i] = mobs[i];
            }
            delete[] mobs;
            mobs = newMobs;
        }
        mobs[size++] = newMob;
    }

    void removeMob(mob* targetMob) {
        for (int i = 0; i < size; ++i) {
            if (mobs[i] == targetMob) {
                delete mobs[i];
                for (int j = i; j < size - 1; ++j) {
                    mobs[j] = mobs[j + 1];
                }
                --size;
                break;
            }
        }
    }

    //periode du joker kill du monstre toucher
    void deadcontact(player& p, int score) {
        if (deadmode) {
            for (int i = 0; i < size; ++i) {
                mobs[i]->symbol = 2;
            }
            for (int i = 0; i < size; ++i) {
                if (sprite::collision_check(*mobs[i], p)) {
                    removeMob(mobs[i]);
                    score += 200;
                    break;
                }
            }
        }
    }
};

#endif