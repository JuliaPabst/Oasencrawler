#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime> // time
#include <cassert> // assert()

#define WIDTH 5
#define HEIGHT 5

using namespace std;

// als Class machen mit public und private

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
    char currentMove = 'd';
} Player;


typedef struct {
    PlayingField playingField;
    Player player;

    void initializeWorld(){
        bool relicPlaced = false;
        for(int i = 0; i < this->playingField.width; i++){
            for(int j = 0; j < this->playingField.height; j++){
                int randomValue = rand() % 10;

                if(randomValue < 4){
                    this->playingField.world[i][j] = none;
                } else if(randomValue >= 4 && randomValue < 8){
                    this->playingField.world[i][j] = danger;
                } else if (randomValue == 8){
                    this->playingField.world[i][j] = well;
                } else if (randomValue == 9){
                    this->playingField.world[i][j] = relic;
                    this->playingField.relicsTotal++;
                    relicPlaced = true;
                }
            }
        }

        if (!relicPlaced){
            this->playingField.world[rand() % this->playingField.width][rand() % this->playingField.height] = relic;
            this->playingField.relicsTotal++;
        }
    }

    void handleField(){
        Fields currentField = this->playingField.world[this->player.playerCoordinates.x][this->player.playerCoordinates.y];
        switch (currentField) {
        case none:
            break;
        case danger:
            if (rand() % 6 == 0) {
                this->player.health--;
                cout << "Danger! You lost a health point." << endl;
            } else {
                cout << "Danger! Lucky you: You escaped." << endl;
            }
            break;
        case well:
            this->player.health++;
            cout << "You have found a well and get a health point." << endl;
            break;
        case relic:
            this->player.relicsGathered++;
            this->playingField.relicsTotal--;
            cout << "You found a relic!" << endl;
            break;
        case alreadyVisited:
            break;
        default:
            break;
        }

        this->playingField.world[this->player.playerCoordinates.x][this->player.playerCoordinates.y] = alreadyVisited;
    }

    bool moveCharacter(){
        int newX = this->player.playerCoordinates.x;
        int newY = this->player.playerCoordinates.y;
        switch (this->player.currentMove) {
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
            cout << "Invalid move. Try again! " << endl;
            return false;
        }

        if (newX >= 0 && newX < this->playingField.width && newY >= 0 && newY < this->playingField.height) {
            this->player.playerCoordinates.x = newX;
            this->player.playerCoordinates.y = newY;
            return true;
        } else {
            cout << "Movement out of borders. Try again! " << endl;
            return false;
        }
    }

    void printStatus(){
        cout << "Health: " << this->player.health << "; Gathered relics: " << this->player.relicsGathered << endl;
        cout << "Remaining relics: " << this->playingField.relicsTotal << endl;
        cout << " " << endl;
    }

    void printWorld(){
        for(int i = 0; i < this->playingField.width; i++){
            for(int j = 0; j < this->playingField.height; j++){
                if (i == this->player.playerCoordinates.x && j == this->player.playerCoordinates.y){
                    cout << "X" << " ";
                }
                else if(this->playingField.world[i][j] != alreadyVisited){
                    cout << "?" << " ";
                } else {
                    cout << "-" << " ";
                }

            }
            cout << " " << endl;
        }
    }

    void testGame(){
        this->initializeWorld();

        // Test: Initialization
        assert(this->player.health == 5);
        assert(this->player.relicsGathered == 0);
        assert(this->playingField.relicsTotal > 0);

        // Test: Movement within borders
        this->player.currentMove = 'd';
        bool canMove = moveCharacter();
        assert(canMove == true);
        assert(this->player.playerCoordinates.y == 1);

        // Test: Movement out of borders
        this->player.currentMove = 'a';
        this->player.playerCoordinates.x = 0; this->player.playerCoordinates.y = 0;
        canMove = this->moveCharacter();
        assert(canMove == false);

        // Test: gather relict
        this->playingField.world[1][1] = relic;
        this->player.playerCoordinates.x = 1; this->player.playerCoordinates.y = 1;
        int relicsBefore = this->playingField.relicsTotal;
        this->handleField();
        assert(this->player.relicsGathered == 1);
        assert(relicsBefore == this->playingField.relicsTotal + 1);

        cout << "All tests successful." << endl;
    }

    void testPlayThrough(){
        char moves[4] = {'w', 'a', 's', 'd'};
        int moveCount = 0;

        while (this->player.health > 0 && this->playingField.relicsTotal != 0) {
            this->printWorld();
            this->player.currentMove = moves[rand() % 4];

            if (this->moveCharacter()) {
                this->handleField();
            }

            moveCount++;

            if (moveCount > 1000) {
                cout << "Stopped game to prevent endless loop after more then 1000 moves." << endl;
                break;
            }
            this->printStatus();
        }
    }
} Game;


int main(){
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    Game game;
    game.initializeWorld();

    //game.testGame();
    // game.testPlayThrough();

    while (game.player.health > 0 && game.playingField.relicsTotal != 0) {
        cout << " " << endl;
        game.printWorld();
        cout << "Enter your next move (w = up, a = left, s = down, d = right, x = end game): ";
        cin >> game.player.currentMove;
        if (game.player.currentMove == 'x') {
            cout << "Game ended." << endl;
            break;
        }
        if (game.moveCharacter()) {
            game.handleField();
            game.printStatus();
        }
    }

    if (game.playingField.relicsTotal == 0) {
        cout << "Congratulations! You found all relics and have won!" << endl;
    } else if (game.player.health <= 0) {
        cout << "You lost all your health points and lost!" << endl;
    }

    return 0;
}
