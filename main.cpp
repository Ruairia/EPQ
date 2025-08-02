#include "Vector2D.h"
#include <cmath>
#include <raylib.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGETFPS 60
using namespace raycaster;

constexpr int map[][] = {
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

int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    SetTargetFPS(TARGETFPS);

    Vector2D playerPosition {1.4,2.3};
    Vector2D playerDirection {1,0};
    Vector2D cameraPlane {0,-2};
    const float moveSpeed = 0.1; //squares per second
    const float turnSpeed = 0.2; //radians per second
    double previousTime=GetTime();
    double currentTime {0};
    double seconds_elapsed {0};
    while (!WindowShouldClose())
    {
        currentTime = GetTime();
        seconds_elapsed = (currentTime - previousTime);

        if (IsKeyDown(KEY_W))
        {
            playerPosition += playerDirection * moveSpeed * seconds_elapsed;
        }

        if (IsKeyDown(KEY_S))
        {
            playerPosition -= playerDirection * moveSpeed * seconds_elapsed;
        }

        if (IsKeyDown(KEY_D))
        {
            playerDirection.rotate(-turnSpeed);
            cameraPlane.rotate(-turnSpeed);
        }

        if (IsKeyDown(KEY_A))
        {
            playerDirection.rotate(turnSpeed);
            cameraPlane.rotate(turnSpeed);
        }



        BeginDrawing();
        ClearBackground(BLACK);

        for (int ScreenX = 0; ScreenX < SCREEN_WIDTH; ScreenX++) //Start of ray cast loop
        {
            Vector2D rayDirection = playerDirection + cameraPlane * (static_cast<float>(ScreenX) / SCREEN_WIDTH - 0.5f);
            rayDirection.normalise();
            Vector2D mapPosition = playerPosition.truncate();
            Vector2D deltaDist = {0,0};
            Vector2D sideDist = {0,0};
            deltaDist.x = (rayDirection.x == 0) ? 1e30 : 1 / rayDirection.x;
            deltaDist.y = (rayDirection.y == 0) ? 1e30 : 1 / rayDirection.y;
            Vector2D step = {0,0};
            if (deltaDist.x<0)
            {
                step.x = -1;
                sideDist.x = (playerPosition.x - mapPosition.x) * deltaDist.x;
            }
            else
            {
                step.x = 1;
                sideDist.x = (mapPosition.x + 1 - playerPosition.x) * deltaDist.x;
            }
            if (deltaDist.y<0)
            {
                step.y = -1;
                sideDist.y = (playerPosition.y - mapPosition.y) * deltaDist.y;
            }
            else
            {
                step.y = 1;
                sideDist.y = (mapPosition.y + 1 - playerPosition.y) * deltaDist.y;
            }

            bool hit = false;
            while (!hit)
            {
                if (sideDist.x < sideDist.y)
                {
                    sideDist.x += deltaDist.x;
                    mapPosition.x += step.x;
                    hit = (map[static_cast<int>(mapPosition.y)][static_cast<int>(mapPosition.x)] == 1);
                }
            }

        }

        previousTime = currentTime();
    }



    return 0;
}