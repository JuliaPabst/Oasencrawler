#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime> // time
#include <cassert> // assert()

#define WIDTH 5
#define HEIGHT 5

using namespace std;

typedef enum {
    none, danger, well, relic, alreadyVisited
} fields;

typedef struct {
    int x = 0;
    int y = 0;
} PlayerCoordinates;


typedef struct {
    int width = WIDTH;
    int height = HEIGHT;
    fields world[WIDTH][HEIGHT];
    int relicsTotal = 0;
    PlayerCoordinates playerCoordinates;
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
            // cout << game.world[i][j] << " ";
        }
        // cout << " " << endl;
    }

    if (!relicPlaced){
        game.world[rand() % game.width][rand() % game.height] = relic;
        game.relicsTotal++;
    }
}

bool moveCharacter(Game& game, char currentMove) {
    int newX = game.playerCoordinates.x;
    int newY = game.playerCoordinates.y;
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
        cout << "Ungültige Bewegung. Bitte erneut versuchen: " << endl;
        return false;
    }

    if (newX >= 0 && newX < game.width && newY >= 0 && newY < game.height) {
        game.playerCoordinates.x = newX;
        game.playerCoordinates.y = newY;
        return true;
    } else {
        cout << "Bewegung außerhalb der Grenzen. Bitte erneut versuchen: " << endl;
        return false;
    }
}

void handleField(Game& game) {
    fields currentField = game.world[game.playerCoordinates.x][game.playerCoordinates.y];
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
    case alreadyVisited:
        break;
    default:
        break;
    }

    game.world[game.playerCoordinates.x][game.playerCoordinates.y] = alreadyVisited;
}

void printStatus(Game game) {
    cout << "Gesundheit: " << game.health << ", Gesammelte Relikte: " << game.relicsGathered << endl;
    cout << "Verbleibende Relikte: " << game.relicsTotal << endl;
}

void printWorld(Game game){
    for(int i = 0; i < game.width; i++){
        for(int j = 0; j < game.height; j++){
            if (i == game.playerCoordinates.x && j == game.playerCoordinates.y){
                cout << "X" << " ";
            }
            else if(game.world[i][j] != alreadyVisited){
                cout << "?" << " ";
            } else {
                cout << "-" << " ";
            }

        }
        cout << " " << endl;
    }
}

void testGame() {
    Game testGame;
    initializeWorld(testGame);

    // Test: Initialization
    assert(testGame.health == 5);
    assert(testGame.relicsGathered == 0);
    assert(testGame.relicsTotal > 0);

    // Test: Movement within borders
    bool canMove = moveCharacter(testGame, 'd');
    assert(canMove == true);
    assert(testGame.playerCoordinates.y == 1);

    // Test: Movement out of borders
    testGame.playerCoordinates.x = 0; testGame.playerCoordinates.y = 0;
    canMove = moveCharacter(testGame, 'w');
    assert(canMove == false);

    // Test: gather relict
    testGame.world[1][1] = relic;
    testGame.playerCoordinates.x = 1; testGame.playerCoordinates.y = 1;
    int relicsBefore = testGame.relicsTotal;
    handleField(testGame);
    assert(testGame.relicsGathered == 1);
    assert(relicsBefore == testGame.relicsTotal + 1);

    cout << "Alle Tests erfolgreich abgeschlossen." << endl;
}

void testPlayThrough(Game& game){
    char moves[4] = {'w', 'a', 's', 'd'};
    int moveCount = 0;

    while (game.health > 0 && game.relicsTotal != 0) {
        char currentMove = moves[rand() % 4];

        if (moveCharacter(game, currentMove)) {
            handleField(game);
        }

        moveCount++;

        // security measure to prevent endless loop
        if (moveCount > 1000) {
            cout << "Sicherheitsabbruch nach 1000 Bewegungen." << endl;
            break;
        }
    }
}


int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    Game game;

    initializeWorld(game);
    handleField(game);
    printStatus(game);

    // testGame();
    // testPlayThrough(game);

    char currentMove;
    while (game.health > 0 && game.relicsGathered < game.relicsTotal) {
        cout << " " << endl;
        printWorld(game);
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
