#include "Vector2D.h"
#include <cmath>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace raycaster;

int main(){
    const int map[][] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,1,0,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,2,2,2,0,0,1},
        {1,0,0,0,2,0,0,0,0,1},
        {1,0,0,0,2,2,0,0,0,1},
        {1,0,0,0,2,0,0,0,0,1},
        {1,0,0,0,2,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    int targetFPS=60;
    Vector2D playerPosition {1.4,2.3};
    Vector2D playerDirection {1,0};
    Vector2D cameraPlane {0,-2};













    return 0;
}