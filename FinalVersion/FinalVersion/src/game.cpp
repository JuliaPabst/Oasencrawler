#include "game.h"

game::game()
{
    //ctor
}

game::~game()
{
    //dtor
}

void game::setAge(int newAge){
    age_ = newAge;
}

int game::getAge() const{
    return age_;
}
