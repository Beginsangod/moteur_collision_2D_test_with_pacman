#include <iostream>

#define MOBS_INCLUDED
#ifdef MOBS_INCLUDED

//classe pour les monstres
class mob : public sprite{
    public:
        int id;
        mob(int x, int y, int id,char symbol = 1) : sprite(x, y, symbol), id(id){};

    void move(player& p, char grille[15][35]) {
        // Directions possibles
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        std::string directions[] = {"up", "down", "left", "right"};

        // Choix de la meilleure direction
        int bestDist = INT_MAX;
        int bestMove = -1;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Vérifier que le mouvement est valide
            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 35 && grille[nx][ny] != 35) {
                int dist = abs(nx - p.x) + abs(ny - p.y);
                if (dist < bestDist) {
                    bestDist = dist;
                    bestMove = i;
                }
            }
        }

        // Effectuer le mouvement
        if (bestMove != -1 && sprite::collision_check(*this,p) == false) {
            x += dx[bestMove];
            y += dy[bestMove];
        }
    }

    void fuir(player& p, char grille[15][35]) {
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        std::string directions[] = {"up", "down", "left", "right"};

        // Choix de la meilleure direction pour fuir
        int bestDist = -1;
        int bestMove = -1;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Vérifier que le mouvement est valide
            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 35 && grille[nx][ny] != 35) {
                int dist = abs(nx - p.x) + abs(ny - p.y);
                if (dist > bestDist) {
                    bestDist = dist;
                    bestMove = i;
                }
            }
        }

        // Effectuer le mouvement
        if (bestMove != -1) {
            x += dx[bestMove];
            y += dy[bestMove];
        }
    }

    //Methode pour la gestion des tamponnement avec les joueurs
    void kill(player& p){
        if (sprite::collision_check(*this,p))
        {
            p.life -= 1;
            p.x = 1;
            p.y = 1;
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
                    mobs[i]->x = 6;
                    mobs[i]->y = 15;
                    score += 200;
                    break;
                }
            }
        }
    }
    mob* getMobsAt(int x, int y) {
        for (int i = 0; i < size; ++i) {
            if (mobs[i]->x == x && mobs[i]->y == y) {
                return mobs[i];
            }
        }
        return nullptr;
    };
};

#endif