#include "Player.h"
#include "World.h"
#include <iostream>

using namespace std;

Player::Player()
{
    //ctor
}

int Player::getX(){
    return x_;
}

int Player::getY(){
    return y_;
}

char Player::getCurrentMove(){
    return currentMove_;
}

int Player::getHealth(){
    return health_;
}

int Player::getStrength(){
    return strength_;
}

int Player::getSpeed(){
    return speed_;
}

int Player::getIntelligence(){
    return intelligence_;
}

int Player::getSpinach(){
    return spinach_;
}

int Player::getRedBull(){
    return redBull_;
}

int Player::getWalnut(){
    return walnut_;
}

int Player::getRelicsGathered(){
    return relicsGathered_;
}

int Player::getLevel(){
    return level_;
}


bool Player::getLastGameWon(){
    return lastGameWon_;
}

void Player::setHealth(int newHealth){
    health_ = newHealth;
}

void Player::setCurrentMove(char newMove){
    currentMove_ = newMove;
}

void Player::setSpinach(int newSpinach){
    spinach_ = newSpinach;
}

void Player::setRedBull(int newRedBull){
    redBull_ = newRedBull;
}

void Player::setWalnut(int newWalnut){
    walnut_ = newWalnut;
}

void Player::setRelicsGathered(int newRelics){
    relicsGathered_ = newRelics;
}

void Player::setLevel(int newLevel){
    level_ = newLevel;
}

void Player::setLastGameWon(bool newStatus){
    lastGameWon_ = newStatus;
}

void Player::printStatus(World world){
    cout << "Health: " << health_ << ", Gathered relics: " << relicsGathered_ << endl;
    cout << "Relics to be found: " << world.getRelicsTotal() << endl;
}

bool Player::moveCharacter(World world) {
    int newX = x_;
    int newY = y_;
    switch (currentMove_) {
    case 'w':
        newX--;
        break;
    case 'a':
        newY--;
        break;
    case 's':
        newX++;
        break;
    case 'd':
        newY++;
        break;
    default:
        cout << "Invalid move. Try again: " << endl;
        return false;
    }

    if (newX >= 0 && newX < world.getWidth() && newY >= 0 && newY < world.getHeight()) {
        x_ = newX;
        y_ = newY;
        return true;
    } else {
        cout << "Movement out of borders - try again: " << endl;
        return false;
    }
}
