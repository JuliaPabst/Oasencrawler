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
    int strength = 5;
    int speed = 5;
    int intelligence = 5;
} Attributes;

typedef struct {
    int spinach = 0;
    int redBull = 0;
    int walnut = 0;
} Artefacts;

typedef struct {
    int x, y;
} EnemyCoordinates;

typedef struct {
    int x = 0;
    int y = 0;
} PlayerCoordinates;


typedef struct {
    int width = WIDTH;
    int height = HEIGHT;
    Fields world[WIDTH][HEIGHT];
    int relicsTotal = 0;
    PlayerCoordinates playerCoordinates;
    EnemyCoordinates enemyCoordinates;
    int health = 5;
    int relicsGathered = 0;
    bool gameWon = true;
    int level = 1;
    Attributes attributes;
    Artefacts artefacts;
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
        cout << "Invalid move. Try again: " << endl;
        return false;
    }

    if (newX >= 0 && newX < game.width && newY >= 0 && newY < game.height) {
        game.playerCoordinates.x = newX;
        game.playerCoordinates.y = newY;
        return true;
    } else {
        cout << "Movement out of borders - try again: " << endl;
        return false;
    }
}

void moveEnemy(Game& game) {
    int direction = rand() % 4;

        switch (direction) {
        case 0:
            if (game.enemyCoordinates.x > 0) {
                game.enemyCoordinates.x--;
            }
            break;
        case 1:
            if (game.enemyCoordinates.x < WIDTH - 1) {
                game.enemyCoordinates.x++;
            }
            break;
        case 2:
            if (game.enemyCoordinates.y > 0) {
                game.enemyCoordinates.y--;
            }
            break;
        case 3:
            if (game.enemyCoordinates.y < HEIGHT - 1) {
                game.enemyCoordinates.y++;
            }
            break;
        }
}


void handleField(Game& game) {
    Fields currentField = game.world[game.playerCoordinates.x][game.playerCoordinates.y];
    switch (currentField) {
    case none:
        break;
    case danger:{
        int attribute = rand() % 3;
        int dice = 0;
        char throwDice = ' ';

        if(attribute == 0){
            cout << "Danger! There is a bear in front of you! You need to prove your strength! Currently you have a strength of " << game.attributes.strength << endl;
            if(game.artefacts.spinach > 0){
                cout << "Additionally, you have " << game.artefacts.spinach << " can(s) of spinach. They each boost your strength by 1 point"  << endl;
            }
            cout << "To win against the bear you need to get at least" << 10+game.level << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + game.artefacts.spinach + game.attributes.strength) > 10 + game.level){
                cout << "Lucky you! You won!" << endl;
            } else {
                cout << "The bear beat you - you lose one health point!" << endl;
                game.health--;
            }
        } else if (attribute == 1){
            cout << "Danger! A cheetah is chasing you! You need to prove your speed! Your current speed level is " << game.attributes.speed << endl;
            if(game.artefacts.redBull > 0){
                cout << "Additionally, you have " << game.artefacts.redBull << " can(s) of Red Bull. They each boost your speed by 1 point"  << endl;
            }
            cout << "To outrun the cheetah you need to get at least " << 10+game.level << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + game.artefacts.redBull + game.attributes.speed) > 10 + game.level){
                cout << "Lucky you! You outran the cheetah!" << endl;
            } else {
                cout << "The cheetah beat you - you lose one health point!" << endl;
                game.health--;
            }
        } else {
            cout << "Danger! A dolphin is asking you for a game of chess! You need to prove your intelligence! Your current intelligence level is" << game.attributes.intelligence << endl;
            if(game.artefacts.walnut > 0){
                 cout << "Additionally, you have " << game.artefacts.walnut << " walnut(s). They each boost your speed by 1 point"  << endl;
            }
            cout << "To win against the dolphin you need to get at least " << 10+game.level << " points in total! Press 't' to throw the dice!" << endl;
            cin >> throwDice;
            dice = (rand() % 6) + 1;
            cout << "You threw a " << dice << endl;
            if((dice + game.artefacts.walnut + game.attributes.intelligence) > 10 + game.level){
                 cout << "Lucky you! You beat the dolphin!" << endl;
            } else {
                cout << "The dolphin beat you - you lose on health point!" << endl;
            }
        }
        break;
    }
    case well:{
        game.health++;
        cout << "You found a well and get a health point!" << endl;

        int artefact = rand() % 3;
        if(artefact == 0){
            game.artefacts.spinach++;
            cout << "You found a can of spinach!" << endl;
        } else if (artefact == 1){
            game.artefacts.redBull++;
            cout << "You found a can of red bull!" << endl;
        } else {
            game.artefacts.walnut++;
            cout << "You found a walnut!" << endl;
        }

        break;
    }
    case relic:{
        game.relicsGathered++;
        game.relicsTotal--;
        cout << "You found a relic!" << endl;

        int artefact = rand() % 3;
        if(artefact == 0){
            game.artefacts.spinach++;
            cout << "You found a can of spinach!" << endl;
        } else if (artefact == 1){
            game.artefacts.redBull++;
            cout << "You found a can of red bull!" << endl;
        } else {
            game.artefacts.walnut++;
            cout << "You found a walnut!" << endl;
        }

        break;
    }
    case alreadyVisited:
        break;
    default:
        break;
    }

    game.world[game.playerCoordinates.x][game.playerCoordinates.y] = alreadyVisited;
}

void printStatus(Game game) {
    cout << "Health: " << game.health << ", Gathered relics: " << game.relicsGathered << endl;
    cout << "Relics to be found: " << game.relicsTotal << endl;
}

void printWorld(Game game){
    for(int i = 0; i < game.width; i++){
        for(int j = 0; j < game.height; j++){
            if (i == game.enemyCoordinates.x && j == game.enemyCoordinates.y){
                cout << "E" << " ";
            } else if (i == game.playerCoordinates.x && j == game.playerCoordinates.y){
                cout << "X" << " ";
            } else if(game.world[i][j] != alreadyVisited){
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

    cout << "All tests successful." << endl;
}

void testPlayThrough(Game& game){
    char moves[4] = {'w', 'a', 's', 'd'};
    int moveCount = 0;

    // Main game loop.
    while(game.gameWon){
        game.enemyCoordinates.x = rand() % WIDTH;
        game.enemyCoordinates.y = rand() % HEIGHT;
        initializeWorld(game);
        handleField(game);
        printStatus(game);
        while (game.health > 0 && game.relicsTotal > 0) {
            printWorld(game);
            char currentMove = moves[rand() % 4];
            if (moveCharacter(game, currentMove)) {
                handleField(game);
                printStatus(game);
                moveEnemy(game);
            }


            if (game.relicsTotal == 0) {
                game.gameWon = true;
                cout << "Congratulations - you won!" << endl;
                cout << " " << endl;
                cout << " " << endl;
                cout << " " << endl;
                break;
            } else if (game.playerCoordinates.x == game.enemyCoordinates.x && game.playerCoordinates.y == game.enemyCoordinates.y) {
                game.gameWon = false;
                cout << "Damn it, you lost! The enemy caught you!" << endl;
                break;
            } else if (game.health <= 0) {
                game.gameWon = false;
                cout << "Damn it, you lost! You don't have any more health points!" << endl;
                break;
            }

            moveCount++;
            // Security measure to prevent an endless loop.
            if (moveCount > 1000) {
                cout << "Stop game after 1000 moves." << endl;
                break;
            }
        }
    }
}



int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    Game game;

    // testGame();
    // testPlayThrough(game);

    char currentMove = ' ';
    game.gameWon = true;


    while (game.gameWon && currentMove != 'n' && currentMove != 'x') {
        initializeWorld(game);
        handleField(game);
        printStatus(game);
        game.enemyCoordinates.x = rand() % WIDTH;
        game.enemyCoordinates.y = rand() % HEIGHT;
        game.health = 5;
        game.relicsGathered = 0;
        cout << "Level " << game.level << endl;

        while (game.health > 0 && game.relicsTotal > 0 && (game.playerCoordinates.x != game.enemyCoordinates.x || game.playerCoordinates.y != game.enemyCoordinates.y)) {
            cout << " " << endl;
            printWorld(game);
            cout << "Type in your next move (w = up, a = left, s = down, d = right, x = end game): ";
            cin >> currentMove;
            if (currentMove == 'x') {
                cout << "Game ended." << endl;
                return 0;
            }
            if (moveCharacter(game, currentMove)) {
                handleField(game);
                printStatus(game);
                moveEnemy(game);
            }
        }

        if (game.relicsTotal == 0 && (game.playerCoordinates.x != game.enemyCoordinates.x || game.playerCoordinates.y != game.enemyCoordinates.y)) {
            cout << "Congratulations - you won!" << endl;
            cout << "Do you want to rise to the next level? (y / n): ";
            cin >> currentMove;
            if(currentMove == 'n') {
                return 0;
            }
            game.level++;
        } else if (game.health <= 0) {
            printWorld(game);
            game.gameWon = false;
            cout << "Damn it, you lost! The enemy caught you!" << endl;
            return 0;
        } else if (game.playerCoordinates.x == game.enemyCoordinates.x && game.playerCoordinates.y == game.enemyCoordinates.y) {
            printWorld(game);
            game.gameWon = false;
            cout << "Damn it, you lost! You don't have any more health points!" << endl;
            return 0;
        }
    }


    return 0;
}
