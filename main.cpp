#include "Vector2D.h"
#include <cmath>
#include <raylib.h>

#include "Player.h"
#include "Map.h"
#include "ray.h"

using namespace raycaster;
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr float moveSpeed = 1; //squares per second
constexpr float turnSpeed = 0.5; //radians per second

void drawWall(int side, int screenX, double distance, int material);


int main(){
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(60);
    auto player = Player({1.5,1.5}, {1,0}, {0,-1});

    double previousTime=GetTime();
    double currentTime {0};
    double seconds_elapsed {0};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        currentTime = GetTime();
        seconds_elapsed = (currentTime - previousTime);


        player.handleMovement(moveSpeed, turnSpeed, seconds_elapsed);

        // Draw Ground and Sky;
        DrawRectangle(0, 0, screenWidth, screenHeight/2, SKYBLUE);
        DrawRectangle(0, screenHeight/2, screenWidth, screenHeight/2, DARKGREEN);

        for (int ScreenX = 0; ScreenX < screenWidth; ScreenX++) //Start of ray cast loop
        {
            Vector2D rayDirection = player.direction + player.cameraPlane * (static_cast<float>(ScreenX) / screenWidth - 0.5f);
            auto ray = raycaster::Ray(player.position, rayDirection);
            bool hit = false;
            int side=1;
            while (!hit) //DDA loop
            {
                if (ray.cumulativeDistance.x < ray.cumulativeDistance.y)
                {
                    ray.cumulativeDistance.x += ray.pathDistanceForGridStep.x;
                    ray.position.x += ray.step.x;
                    side=0;
                }
                else
                {
                    ray.cumulativeDistance.y += ray.pathDistanceForGridStep.y;
                    ray.position.y += ray.step.y;
                    side=1;
                }
                hit = (Map::getSquare(ray.position.x, ray.position.y) != 0);
            }
            double distance;
            if (side == 0)
            {
                distance = abs((ray.position.x - ray.origin.x + (1 - ray.step.x) / 2) / ray.direction.x);
            }
            else
            {
                distance = abs((ray.position.y - ray.origin.y + (1 - ray.step.y) / 2) / ray.direction.y);
            }

            drawWall(side, ScreenX, distance, Map::getSquare(ray.position.x,ray.position.y));
        }

        previousTime = currentTime;
        EndDrawing();
    }


CloseWindow();
    return 0;
}

void drawWall(const int side, const int screenX, const double distance, int material) {
    const int lineHeight = static_cast<int>(std::round(screenHeight / distance));
    int drawStart = std::floor(-lineHeight / 2 + screenHeight / 2);
    if(drawStart < 0) {
        drawStart = 0;
    }
    int drawEnd = std::round(lineHeight / 2 + screenHeight / 2);
    if(drawEnd >= screenHeight) {
        drawEnd = screenHeight - 1;
    }
    auto colour = MAROON;
    if (material==1) colour = WHITE;

    if (side == 0) colour = ColorBrightness(colour, -0.05*distance+0.05);
    else colour = ColorBrightness(colour, -0.05*distance);
    DrawRectangle(screenX, drawStart, 1, drawEnd - drawStart, colour);
}