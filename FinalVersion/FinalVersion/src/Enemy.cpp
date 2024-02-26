#include "Enemy.h"
#include <cstdlib> // rand() and srand()
#include <ctime> // time

Enemy::Enemy(){
}

int Enemy::getX(){
    return x_;
}

int Enemy::getY(){
    return y_;
}

void Enemy::setX(int newX){
    x_ = newX;
}

void Enemy::setY(int newY){
    y_ = newY;
}

void Enemy::moveEnemy(World world) {
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    int direction = rand() % 4;

    switch (direction) {
    case 0:
        if (x_ > 0) {
            x_--;
        }
        break;
    case 1:
        if (x_ < world.getWidth() - 1) {
            x_++;
        }
        break;
    case 2:
        if (y_ > 0) {
            y_--;
        }
        break;
    case 3:
        if (y_ < world.getHeight() - 1) {
            y_++;
        }
        break;
    }
}
