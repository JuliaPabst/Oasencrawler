#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime> // time()

#define WIDTH 5
#define HEIGHT 5

using namespace std;

typedef enum {
    none, danger, well, relic
} fields;

struct game {
    fields world[WIDTH][HEIGHT];
    int x;
    int y;
    };

int main()
{
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)));



    return 0;
}
