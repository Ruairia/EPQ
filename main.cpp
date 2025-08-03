#include "Vector2D.h"
#include <cmath>
#include <raylib.h>

#define TARGETFPS 60
using namespace raycaster;
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr int map[10][10] = {
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

    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(TARGETFPS);
    Vector2D playerPosition {1.4,2.3};
    Vector2D playerDirection {1,0};
    Vector2D cameraPlane {0,-2};
    const float moveSpeed = 1; //squares per second
    const float turnSpeed = 0.1; //radians per second
    double previousTime=GetTime();
    double currentTime {0};
    double seconds_elapsed {0};
    while (!WindowShouldClose())
    {
        BeginDrawing();
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




        // ClearBackground(BLACK);
        DrawRectangle(0, 0, screenWidth, screenHeight/2, SKYBLUE);
        DrawRectangle(0, screenHeight/2, screenWidth, screenHeight/2, DARKGREEN);

        for (int ScreenX = 0; ScreenX < screenWidth; ScreenX++) //Start of ray cast loop
        {
            Vector2D rayDirection = playerDirection + cameraPlane * (static_cast<float>(ScreenX) / screenWidth - 0.5f);
            rayDirection.normalise();
            Vector2D mapPosition = playerPosition.truncate();
            Vector2D deltaDist = {0,0};
            Vector2D sideDist = {0,0};
            deltaDist.x = (rayDirection.x == 0) ? 1e30 : abs(1 / rayDirection.x);
            deltaDist.y = (rayDirection.y == 0) ? 1e30 : abs(1 / rayDirection.y);
            Vector2D step = {0,0};
            if (rayDirection.x<0)
            {
                step.x = -1;
                sideDist.x = (playerPosition.x - mapPosition.x) * deltaDist.x;
            }
            else
            {
                step.x = 1;
                sideDist.x = (mapPosition.x + 1 - playerPosition.x) * deltaDist.x;
            }
            if (rayDirection.y<0)
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
            int side;
            while (!hit)
            {
                if (sideDist.x < sideDist.y)
                {
                    sideDist.x += deltaDist.x;
                    mapPosition.x += step.x;
                    side=0;
                }
                else
                {
                    sideDist.y += deltaDist.y;
                    mapPosition.y += step.y;
                    side=1;
                }
                hit = (map[static_cast<int>(mapPosition.y)][static_cast<int>(mapPosition.x)] != 0);
            }

            double perpendicularDistance;
            if (side == 0)
            {
                perpendicularDistance = (mapPosition.x - playerPosition.x + (1 - step.x) / 2) / rayDirection.x;
            }
            else
            {
                perpendicularDistance = (mapPosition.y - playerPosition.y + (1 - step.y) / 2) / rayDirection.y;
            }

            const int lineHeight = static_cast<int>(screenHeight / perpendicularDistance);
            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if(drawStart < 0)
            {
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if(drawEnd >= screenHeight)
            {
                drawEnd = screenHeight - 1;
            }
                auto colour = RAYWHITE;
            if (side == 0) colour = ColorBrightness(colour, -0.05*perpendicularDistance+0.05);
            else colour = ColorBrightness(colour, -0.05*perpendicularDistance);
            DrawRectangle(ScreenX, drawStart, 1, drawEnd - drawStart, colour);}

        previousTime = currentTime;
        EndDrawing();
    }


CloseWindow();
    return 0;
}