#ifndef ENEMY_H
#define ENEMY_H
#include "World.h"

class World;

class Enemy
{
    public:
        Enemy();
        int getX();
        int getY();
        void setX(int newX);
        void setY(int newY);
        void moveEnemy(World world);

    private:
        int x_ = 0;
        int y_ = 0;
};

#endif // ENEMY_H
