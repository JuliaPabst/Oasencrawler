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
    int width = WIDTH;
    int height = HEIGHT;
    fields world[WIDTH][HEIGHT];
    int relicsTotal;
    int x = 0;
    int y = 0;
    int health = 5;
    int relicsGathered = 0;
} Game;

int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    bool relicPlaced = false;
    char currentMove = 'a';

    Game game;

    // fill playing field
    for(int i = 0; i < game.width; i++){
        for(int j = 0; j < game.height; j++){
            int randomValue = rand() % 10;

            if(randomValue < 4){
                game.world[i][j] = none;
            } else if(randomValue < 8){
                game.world[i][j] = danger;
            } else if (randomValue < 9){
                game.world[i][j] = well;
            } else if (randomValue == 9){
                game.world[i][j] = relic;
                game.relicsTotal++;
                relicPlaced = true;
            }
            cout << game.world[i][j] << " ";
        }
        cout << " " << endl;
    }

    if (!relicPlaced){
        game.world[rand() % 5][rand() % 5] = relic;
    }

    while(currentMove != 'x' && game.health > 0 && game.relicsGathered < game.relicsTotal){
        cout << "Enter your next move (w = up, a = left, s = right, d = down): " << endl;
        cin >> currentMove;
        switch (currentMove) {
        case 'w':
            game.y++;
            break;
        case 'a':
            game.x--;
            break;
        case 's':
            game.y--;
            break;
        case 'd':
            game.x++;
            break;
        }

    }




    return 0;
}
