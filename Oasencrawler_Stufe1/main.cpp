#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime> // time
#include <cassert> // assert()

#define WIDTH 5
#define HEIGHT 5

using namespace std;

typedef enum {
    none, danger, well, relic, alreadyVisited
} Fields;

typedef struct {
    int x = 0;
    int y = 0;
} PlayerCoordinates;

typedef struct {
    int width = WIDTH;
    int height = HEIGHT;
    Fields world[WIDTH][HEIGHT];
    int relicsTotal = 0;
} PlayingField;

typedef struct {
    PlayerCoordinates playerCoordinates;
    int health = 5;
    int relicsGathered = 0;
    char currentMove = ' ';
} Player;


typedef struct {
    PlayingField playingField;
    Player player;
} Game;

void initializeWorld(Game& game){
    bool relicPlaced = false;
    for(int i = 0; i < game.playingField.width; i++){
        for(int j = 0; j < game.playingField.height; j++){
            int randomValue = rand() % 10;

            if(randomValue < 4){
                game.playingField.world[i][j] = none;
            } else if(randomValue >= 4 && randomValue < 8){
                game.playingField.world[i][j] = danger;
            } else if (randomValue == 8){
                game.playingField.world[i][j] = well;
            } else if (randomValue == 9){
                game.playingField.world[i][j] = relic;
                game.playingField.relicsTotal++;
                relicPlaced = true;
            }
        }
    }

    if (!relicPlaced){
        game.playingField.world[rand() % game.playingField.width][rand() % game.playingField.height] = relic;
        game.playingField.relicsTotal++;
    }
}

bool moveCharacter(Game& game) {
    int newX = game.player.playerCoordinates.x;
    int newY = game.player.playerCoordinates.y;
    switch (game.player.currentMove) {
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
        cout << "Invalid move. Try again!: " << endl;
        return false;
    }

    if (newX >= 0 && newX < game.playingField.width && newY >= 0 && newY < game.playingField.height) {
        game.player.playerCoordinates.x = newX;
        game.player.playerCoordinates.y = newY;
        return true;
    } else {
        cout << "Movement out of borders. Try again!: " << endl;
        return false;
    }
}

void handleField(Game& game) {
    Fields currentField = game.playingField.world[game.player.playerCoordinates.x][game.player.playerCoordinates.y];
    switch (currentField) {
    case none:
        break;
    case danger:
        if (rand() % 6 == 0) {
            game.player.health--;
            cout << "Danger! You lost a health point." << endl;
        } else {
            cout << "Danger! Lucky you: You escaped." << endl;
        }
        break;
    case well:
        game.player.health++;
        cout << "You have found a well and get a health point." << endl;
        break;
    case relic:
        game.player.relicsGathered++;
        game.playingField.relicsTotal--;
        cout << "You found a relic!" << endl;
        break;
    case alreadyVisited:
        break;
    default:
        break;
    }

    game.playingField.world[game.player.playerCoordinates.x][game.player.playerCoordinates.y] = alreadyVisited;
}

void printStatus(Game game) {
    cout << "Health: " << game.player.health << "; Gathered relics: " << game.player.relicsGathered << endl;
    cout << "Remaining relics: " << game.playingField.relicsTotal << endl;
    cout << " " << endl;
}

void printWorld(Game game){
    for(int i = 0; i < game.playingField.width; i++){
        for(int j = 0; j < game.playingField.height; j++){
            if (i == game.player.playerCoordinates.x && j == game.player.playerCoordinates.y){
                cout << "X" << " ";
            }
            else if(game.playingField.world[i][j] != alreadyVisited){
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
    assert(testGame.player.health == 5);
    assert(testGame.player.relicsGathered == 0);
    assert(testGame.playingField.relicsTotal > 0);

    // Test: Movement within borders
    bool canMove = moveCharacter(testGame);
    assert(canMove == true);
    assert(testGame.player.playerCoordinates.y == 1);

    // Test: Movement out of borders
    testGame.player.playerCoordinates.x = 0; testGame.player.playerCoordinates.y = 0;
    canMove = moveCharacter(testGame);
    assert(canMove == false);

    // Test: gather relict
    testGame.playingField.world[1][1] = relic;
    testGame.player.playerCoordinates.x = 1; testGame.player.playerCoordinates.y = 1;
    int relicsBefore = testGame.playingField.relicsTotal;
    handleField(testGame);
    assert(testGame.player.relicsGathered == 1);
    assert(relicsBefore == testGame.playingField.relicsTotal + 1);

    cout << "All tests successful." << endl;
}

void testPlayThrough(Game& game){
    char moves[4] = {'w', 'a', 's', 'd'};
    int moveCount = 0;

    while (game.player.health > 0 && game.playingField.relicsTotal != 0) {
        printWorld(game);
        game.player.currentMove = moves[rand() % 4];

        if (moveCharacter(game)) {
            handleField(game);
        }

        moveCount++;

        if (moveCount > 1000) {
            cout << "Stopped game to prevent endless loop after more then 1000 moves." << endl;
            break;
        }
        printStatus(game);
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
    //testPlayThrough(game);

    while (game.player.health > 0 && game.playingField.relicsTotal != 0) {
        cout << " " << endl;
        printWorld(game);
        cout << "Enter your next move (w = up, a = left, s = down, d = right, x = end game): ";
        cin >> game.player.currentMove;
        if (game.player.currentMove == 'x') {
            cout << "Game ended." << endl;
            break;
        }
        if (moveCharacter(game)) {
            handleField(game);
            printStatus(game);
        }
    }

    if (game.playingField.relicsTotal == 0) {
        cout << "Congratulations! You found all relics and have won!" << endl;
    } else if (game.player.health <= 0) {
        cout << "You lost all your health points and lost!" << endl;
    }

    return 0;
}
