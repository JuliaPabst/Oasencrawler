#ifndef TESTS_H
#define TESTS_H
#include "Player.h"
#include "Enemy.h"
#include "World.h"

class Player;
class Enemy;
class World;

class Tests
{
    public:
        Tests();
        void testGame(World world, Player player, Enemy enemy);
        int testPlayThrough(World world, Player player, Enemy enemy);

    protected:

    private:
};

#endif // TESTS_H
