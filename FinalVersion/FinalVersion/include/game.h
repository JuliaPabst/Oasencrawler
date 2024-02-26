#ifndef GAME_H
#define GAME_H

// different classes for gamefield and player
class game
{
    public:
        void setAge(int newAge);
        int getAge() const;
        game();
        ~game();

    private:
        int age_ = 5;
};

#endif // GAME_H
