#include <iostream>
#include <chrono>
#include <thread>

#define GEST_BONUS_INCLUDED
#ifdef GEST_BONUS_INCLUDED

//classe parent pour les differents bonus du jeu 
class bonus : public sprite {
    public:
        bonus(int x, int y,char symbol) : sprite(x,y,symbol){};

    //gerer le contact entre les bonus et le joueur
    bool contact(player& p){
        if (sprite::collision_check(*this, p))
        {
            return true;
        }
        return false;
    }
};

//classe bonus basique pour les points
class pellet : public bonus{ 
    public:
        pellet(int x, int y, char symbol= '.'): bonus(x,y,symbol){};

    //ajoue de point
    void addscore(int score,player p){
        if (bonus::contact(p))
        {
            score += 10;
        }
    }
};

//classe bonus superieur plus de point
class super_pellet : public bonus{ 
    public:
        super_pellet(int x, int y, char symbol= 16): bonus(x,y,symbol){};

    //ajoue de point
    void addscore(int score, player p){
        if (bonus::contact(p))
        {
            score += 100;
        } 
    }
};

//classe bonus superieur+ et possibilite de bouffer le joueur
class joker : public bonus{ 
    public:
        joker(int x, int y, char symbol= 5): bonus(x,y,symbol){};

    //ajoue de point
    void addscore(int score, player p){
        if (bonus::contact(p))
        {
            score += 50;
        } 
    }
    //Methode transformant les mobs en mangeable pour 5 seconde
    void changeghost(player p, Mobsgroup ms){
        if (bonus::contact(p))
        {
            ms.deadmode = true;
            auto start = std::chrono::steady_clock::now();
            
            while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() < 10) {
                // Logique de mise à jour du jeu ici sans bloquer le fil
                std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Attendre ~16ms pour une mise à jour fluide (~60 FPS)
            }
            ms.deadmode = false;
        } 
    }
};

class Bonusgroup : public sprite {
    public:
        bonus** bns;
        int size;
        int capacity;

        Bonusgroup(int init_capacity = 10) : sprite(0, 0 , ' '), size(0), capacity(init_capacity){
            bns = new bonus*[capacity];
        };

        ~Bonusgroup() {
            for (int i = 0; i < size; ++i) {
                delete bns[i];  // Libérer la mémoire de chaque sprite
            }
            delete[] bns;  // Libérer le tableau de pointeurs
        }

        void addbonus(bonus* newbonus) {
            if (size >= capacity) {
                // Augmenter la capacité du tableau de pointeurs
                capacity *= 2;  // Doubler la capacité
                bonus** new_bns = new bonus*[capacity];
                // Copier les anciens bonus dans le nouveau tableau
                for (int i = 0; i < size; ++i) {
                    new_bns[i] = bns[i];
                }
                // Libérer l'ancien tableau de pointeurs
                delete[] bns;
                // Réaffecter le nouveau tableau au pointeur bns
                bns = new_bns;
            }

            // Ajouter le nouveau bonus
            bns[size++] = newbonus;
        };
        bonus* getBonusAt(int x, int y) {
            for (int i = 0; i < size; ++i) {
                if (bns[i]->x == x && bns[i]->y == y) {
                    return bns[i];
                }
            }
            return nullptr;
        };
};
#endif