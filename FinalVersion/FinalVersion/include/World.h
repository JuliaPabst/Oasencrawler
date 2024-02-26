#ifndef WORLD_H
#define WORLD_H
#define WIDTH 5
#define HEIGHT 5
#include "Player.h"
#include "Enemy.h"

class Player;
class Enemy;

enum Fields {
    none, danger, well, relic, alreadyVisited
};

class World
{
    public:
        World();
        void initializeWorld();
        void handleField(Player& player);
        void printWorld(Player player, Enemy enemy);
        int getRelicsTotal();
        int getWidth();
        int getHeight();

    private:
        int width_ = WIDTH;
        int height_ = HEIGHT;
        Fields world_[WIDTH][HEIGHT];
        int relicsTotal_ = 0;
};

#endif // WORLD_H
