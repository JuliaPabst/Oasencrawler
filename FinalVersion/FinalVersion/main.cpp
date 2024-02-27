#include <iostream>
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "tests.h"

using namespace std;

int main()
{
    Player player;
    World world;
    Enemy enemy;
    Tests test;

    //test.testGame(world, player, enemy);

    test.testPlayThrough(world, player, enemy);


   while (player.getLastGameWon() && player.getCurrentMove() != 'n' && player.getCurrentMove() != 'x') {

        world.initializeWorld();

        enemy.setX(rand() % world.getWidth());
        enemy.setY(rand() % world.getHeight());

        player.setRelicsGathered(0);

        cout << "Level " << player.getLevel() << endl;

        while (player.getHealth() > 0 && world.getRelicsTotal() > 0 && (player.getX() != enemy.getX() || player.getY() != enemy.getY())) {
            cout << " " << endl;
            world.printWorld(player, enemy);
            cout << "Type in your next move (w = up, a = left, s = down, d = right, x = end game): ";
            char newMove;
            cin >> newMove;
            player.setCurrentMove(newMove);

            if (player.getCurrentMove() == 'x') {
                cout << "Game ended." << endl;
                return 0;
            }
            if (player.moveCharacter(world)) {
                world.handleField(player);
                player.printStatus(world);
                enemy.moveEnemy(world);
            }
        }

        if (world.getRelicsTotal() == 0 && (player.getX() != enemy.getX() || player.getY() != enemy.getY())) {
            cout << "Congratulations - you won!" << endl;
            cout << "Do you want to rise to the next level? (y / n): ";
            char newMove;
            cin >> newMove;
            player.setCurrentMove(newMove);
            if(player.getCurrentMove() == 'n') {
                return 0;
            }
            player.incrementLevel();
        } else if (player.getHealth() <= 0) {
            world.printWorld(player, enemy);
            player.setLastGameWon(false);
            cout << "Damn it, you lost! The enemy caught you!" << endl;
            return 0;
        } else if (player.getX() == enemy.getX() && player.getY() == enemy.getY()) {
            world.printWorld(player, enemy);
            player.setLastGameWon(false);
            cout << "Damn it, you lost! You don't have any more health points!" << endl;
            return 0;
        }
    }
}
