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
    int relicsTotal = 0;
    int x = 0;
    int y = 0;
    int health = 5;
    int relicsGathered = 0;
} Game;

void initializeWorld(Game& game){
    bool relicPlaced = false;
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
        game.world[rand() % game.width][rand() % game.height] = relic;
        game.relicsTotal++;
    }
}

bool moveCharacter(Game& game, char currentMove) {
    int newX = game.x;
    int newY = game.y;
    switch (currentMove) {
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
        cout << "Ungültige Bewegung. Bitte erneut versuchen: ";
        return false;
    }

    if (newX >= 0 && newX < game.width && newY >= 0 && newY < game.height) {
        game.x = newX;
        game.y = newY;
        cout << "X: " << newX << endl;
        cout << "Y: " << newY <<endl;

        return true;
    } else {
        cout << "Bewegung außerhalb der Grenzen. Bitte erneut versuchen: ";
        return false;
    }
}

void handleField(Game& game) {
    fields currentField = game.world[game.x][game.y];
    switch (currentField) {
    case none:
        break;
    case danger:
        if (rand() % 6 == 0) {
            game.health--;
            cout << "Gefahr! Du hast ein Lebenspunkt verloren." << endl;
        }
        break;
    case well:
        game.health++;
        cout << "Du hast einen Brunnen gefunden und einen Lebenspunkt gewonnen." << endl;
        break;
    case relic:
        game.relicsGathered++;
        game.relicsTotal--;
        cout << "Du hast ein Relikt gefunden!" << endl;
        break;
    }
    game.world[game.x][game.y] = none;
}

void printStatus(Game game) {
    cout << "Gesundheit: " << game.health << ", Gesammelte Relikte: " << game.relicsGathered << endl;
    cout << "Verbleibende Relikte: " << game.relicsTotal << endl;
}


int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    Game game;

    initializeWorld(game);

    char currentMove;
    while (game.health > 0 && game.relicsGathered < game.relicsTotal) {
        cout << "Gib deinen nächsten Zug ein (w = hoch, a = links, s = unten, d = rechts, x = Spiel beenden): ";
        cin >> currentMove;
        if (currentMove == 'x') {
            cout << "Spiel beendet." << endl;
            break;
        }
        if (moveCharacter(game, currentMove)) {
            handleField(game);
            printStatus(game);
        }
    }

    if (game.relicsTotal == 0) {
        cout << "Herzlichen Glückwunsch! Du hast alle Relikte gesammelt." << endl;
    } else if (game.health <= 0) {
        cout << "Leider verloren. Versuche es erneut!" << endl;
    }

    return 0;
}
