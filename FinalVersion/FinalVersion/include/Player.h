#ifndef PLAYER_H
#define PLAYER_H
#include "World.h"

class World;

class Player
{
    public:
        Player();
        int getX();
        int getY();
        char getCurrentMove();
        int getHealth();
        int getStrength();
        int getSpeed();
        int getIntelligence();
        int getSpinach();
        int getRedBull();
        int getWalnut();
        int getRelicsGathered();
        int getLevel();
        bool getLastGameWon();
        void setHealth(int newHealth);
        void setCurrentMove(char newMove);
        void setSpinach(int newSpinach);
        void setRedBull(int newRedBull);
        void setWalnut(int newWalnut);
        void setRelicsGathered(int newRelics);
        void setLevel(int newLevel);
        void setLastGameWon(bool newStatus);
        void printStatus(World world);
        bool moveCharacter(World world);

    protected:

    private:
        int x_ = 0;
        int y_ = 0;
        int health_ = 5;
        int relicsGathered_ = 0;
        char currentMove_ = 'd';
        int spinach_ = 0;
        int redBull_ = 0;
        int walnut_ = 0;
        int strength_ = 5;
        int speed_ = 5;
        int intelligence_ = 5;
        int level_ = 1;
        bool lastGameWon_ = true;
};

#endif // PLAYER_H
