#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime> // time()

#define WIDTH 5
#define HEIGHT 5

using namespace std;

typedef enum {
    none, danger, well, relic
} fields;

typedef struct {
    fields world[WIDTH][HEIGHT];
    int x = 0;
    int y = 0;
} Game;

int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    Game game;

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; i < LENGTH; j++){
            int randomValue = rand() % 10;
        }
    }



    return 0;
}
