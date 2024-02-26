#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include <cstdlib> // rand() and srand()
#include <ctime> // time
#include <iostream>


using namespace std;


World::World()
{
    //ctor
}

void World::initializeWorld(){
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    bool relicPlaced = false;
    for(int i = 0; i < width_; i++){
        for(int j = 0; j < height_; j++){
            int randomValue = rand() % 10;

            if(randomValue < 4){
                world_[i][j] = none;
            } else if(randomValue < 8){
                world_[i][j] = danger;
            } else if (randomValue < 9){
                world_[i][j] = well;
            } else if (randomValue == 9){
                world_[i][j] = relic;
                relicsTotal_++;
                relicPlaced = true;
            }
            // cout << world_[i][j] << " ";
        }
        // cout << " " << endl;
    }

    if (!relicPlaced){
        world_[rand() % width_][rand() % height_] = relic;
        relicsTotal_++;
    }
}

void World::handleField(Player& player){
    Fields currentField = world_[player.getX()][player.getY()];
    int currentHealth = player.getHealth();
    switch (currentField) {
    case none:
        break;
    case danger:{
        int attribute = rand() % 3;
        int dice = 0;
        char throwDice = ' ';

        if(attribute == 0){
            cout << "Danger! There is a bear in front of you! You need to prove your strength! Currently you have a strength of " << player.getStrength() << endl;
            if(player.getSpinach() > 0){
                cout << "Additionally, you have " << player.getSpinach() << " can(s) of spinach. They each boost your strength by 1 point"  << endl;
            }
            cout << "To win against the bear you need to get at least " << 7+player.getLevel() << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + player.getSpinach() + player.getStrength()) >= 7 + player.getLevel()){
                cout << "Lucky you! You won!" << endl;
            } else {
                cout << "The bear beat you - you lose one health point!" << endl;
                player.setHealth(--currentHealth);
            }
        } else if (attribute == 1){
            cout << "Danger! A cheetah is chasing you! You need to prove your speed! Your current speed level is " << player.getSpeed() << endl;
            if(player.getRedBull() > 0){
                cout << "Additionally, you have " << player.getRedBull() << " can(s) of Red Bull. They each boost your speed by 1 point"  << endl;
            }
            cout << "To outrun the cheetah you need to get at least " << 7+player.getLevel() << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + player.getRedBull() + player.getSpeed()) >= 7 + player.getLevel()){
                cout << "Lucky you! You outran the cheetah!" << endl;
            } else {
                cout << "The cheetah beat you - you lose one health point!" << endl;
                player.setHealth(--currentHealth);
            }
        } else {
            cout << "Danger! A dolphin is asking you for a game of chess! You need to prove your intelligence! Your current intelligence level is " << player.getIntelligence() << endl;
            if(player.getWalnut() > 0){
                 cout << "Additionally, you have " << player.getWalnut() << " walnut(s). They each boost your speed by 1 point"  << endl;
            }
            cout << "To win against the dolphin you need to get at least " << 7 + player.getLevel() << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + player.getWalnut() + player.getIntelligence()) >= 7 + player.getLevel()){
                 cout << "Lucky you! You beat the dolphin!" << endl;
            } else {
                cout << "The dolphin beat you - you lose on health point!" << endl;
                player.setHealth(--currentHealth);
            }
        }
        break;
    }
    case well:{
        player.setHealth(++currentHealth);
        cout << "You found a well and get a health point!" << endl;

        int artefact = rand() % 3;
        if(artefact == 0){
            int currentSpinach = player.getSpinach();
            player.setSpinach(++currentSpinach);
            cout << "You found a can of spinach!" << endl;
        } else if (artefact == 1){
            int currentRedBull = player.getRedBull();
            player.setRedBull(++currentRedBull);
            cout << "You found a can of red bull!" << endl;
        } else {
            int currentWalnut = player.getWalnut();
            player.setWalnut(++currentWalnut);
            cout << "You found a walnut!" << endl;
        }

        break;
    }
    case relic:{
        int currentRelics = player.getRelicsGathered();
        player.setRelicsGathered(++currentRelics);
        relicsTotal_--;
        cout << "You found a relic!" << endl;

        int artefact = rand() % 3;
        if(artefact == 0){
            int currentSpinach = player.getSpinach();
            player.setSpinach(++currentSpinach);
            cout << "You found a can of spinach!" << endl;
        } else if (artefact == 1){
            int currentRedBull = player.getRedBull();
            player.setRedBull(++currentRedBull);
            cout << "You found a can of red bull!" << endl;
        } else {
            int currentWalnut = player.getWalnut();
            player.setWalnut(++currentWalnut);
            cout << "You found a walnut!" << endl;
        }

        break;
    }
    case alreadyVisited:
        break;
    default:
        break;
    }

    world_[player.getX()][player.getY()] = alreadyVisited;
}

void World::printWorld(Player player, Enemy enemy){
    for(int i = 0; i < width_; i++){
        for(int j = 0; j < height_; j++){
            if (i == enemy.getX() && j == enemy.getY()){
                cout << "E" << " ";
            } else if (i == player.getX() && j == player.getY()){
                cout << "X" << " ";
            } else if(world_[i][j] != alreadyVisited){
                cout << "?" << " ";
            } else {
                cout << "-" << " ";
            }
        }
        cout << " " << endl;
    }
}

int World::getRelicsTotal(){
    return relicsTotal_;
}

int World::getWidth(){
    return width_;
}

int World::getHeight(){
    return height_;
}
