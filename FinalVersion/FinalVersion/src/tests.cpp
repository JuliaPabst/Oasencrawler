#include "Tests.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"
#include <cassert> // assert()
#include <cstdlib> // rand() and srand()
#include <ctime> // time
#include <iostream>

using namespace std;

Tests::Tests()
{
    //ctor
}


void Tests::testGame(World world, Player player, Enemy enemy) {
    world.initializeWorld();

    // Test: Initialization
    assert(player.getHealth() == 5);
    assert(player.getRelicsGathered() == 0);
    assert(world.getRelicsTotal() > 0);

    // Test: Movement within borders
    player.setCurrentMove('d');
    bool canMove = player.moveCharacter(world);
    assert(canMove == true);
    assert(player.getX() == 0);

    // Test: Movement out of borders
    player.setX(0);
    player.setY(0);
    player.setCurrentMove('w');
    canMove = player.moveCharacter(world);
    assert(canMove == false);

    // Test: gather relict
    world.setWorld1(relic);
     player.setX(1);
    player.setY(1);
    int relicsBefore = world.getRelicsTotal();
    world.handleField(player);
    assert(player.getRelicsGathered() == 1);
    assert(relicsBefore == world.getRelicsTotal() + 1);

    cout << "All tests successful." << endl;
}

int Tests::testPlayThrough(World world, Player player, Enemy enemy){
     // seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    char moves[4] = {'w', 'a', 's', 'd'};
    int moveCount = 0;

    // Main game loop.
    while(player.getLastGameWon()){
        world.initializeWorld();
        enemy.setX(rand() % world.getWidth());
        enemy.setY(rand() % world.getHeight());
        player.setRelicsGathered(0);

        cout << "Level " << player.getLevel() << endl;

        while (player.getHealth() > 0 && world.getRelicsTotal() > 0) {
            world.printWorld(player, enemy);
            player.setCurrentMove(moves[rand() % 4]);
            if (player.moveCharacter(world)) {
                world.handleField(player);
                player.printStatus(world);
                enemy.moveEnemy(world);
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
            cout << "Damn it, you lost! You don't have any more health points!" << endl;
            return 0;
        } else if (player.getX() == enemy.getX() && player.getY() == enemy.getY()) {
            world.printWorld(player, enemy);
            player.setLastGameWon(false);
            cout << "Damn it, you lost! The enemy caught you!" << endl;
            return 0;
        }

            moveCount++;

            // Security measure to prevent an endless loop.
            if (moveCount > 1000) {
                cout << "Stop game after 1000 moves." << endl;
                break;
            }
        }
    }
    return 1;
}
