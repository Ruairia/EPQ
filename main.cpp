#include "Vector2D.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <raylib.h>

#include "Player.h"
#include "Map.h"
#include "ray.h"

using namespace raycaster;
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr float moveSpeed = 2; //squares per second
constexpr float turnSpeed = 2; //radians per second

void drawWall(int side, int screenX, double distance, int hit);

int main(){
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(60);
auto player = Player({3,3},{1,0},{0,1.32});

    double previousTime=GetTime();
    double currentTime {0};
    double seconds_elapsed {0};

    while (!WindowShouldClose())
    {
        currentTime = GetTime();
        seconds_elapsed = currentTime - previousTime;
        previousTime = currentTime;

        player.handleMovement(moveSpeed, turnSpeed, seconds_elapsed);

        BeginDrawing();
        DrawRectangle(0, 0, screenWidth, screenHeight/2, SKYBLUE);
        DrawRectangle(0, screenHeight/2, screenWidth, screenHeight/2, DARKGREEN);

        for (int screenX  {0}; screenX < screenWidth; screenX++)
        {
            double  cameraX =
                (-0.5 + (static_cast<float>(screenX) / static_cast<float>(screenWidth)));
            Vector2D rayDirection = player.direction + player.cameraPlane * cameraX;
            auto ray = raycaster::Ray(player.position, rayDirection);


            int hit=0;
            int side=0;
            while (hit == 0 && Map::hasSquare(ray.mapPosition.x, ray.mapPosition.y))
            {
                if (ray.sideDist.x<ray.sideDist.y)
                {
                    ray.sideDist.x += ray.pathDistanceForGridStep.x;
                    ray.mapPosition.x += ray.step.x;
                    side=0;
                }

                else
                {
                    ray.sideDist.y += ray.pathDistanceForGridStep.y;
                    ray.mapPosition.y += ray.step.y;
                    side=1;
                }

                hit = Map::getSquare(ray.mapPosition.x, ray.mapPosition.y);

            }
            double perpendicularDistance = 0;
            if(side == 0) perpendicularDistance = (ray.sideDist.x - ray.pathDistanceForGridStep.x);
            else          perpendicularDistance = (ray.sideDist.y - ray.pathDistanceForGridStep.y);


            drawWall(side, screenX, perpendicularDistance, hit);

        }
        EndDrawing();
    }


    CloseWindow();
    return 0;
}

void drawWall(int side, int screenX, double distance, int hit) {
    if (distance <= 0) return;  // Avoid division by zero

    Color material;
    switch (hit) {
        case 1: material = WHITE; break;
        case 2: material = RED; break;
        case 3: material = BLUE; break;
        case 4: material = GREEN; break;
        default: material = BLACK; break;
    }
    if (side == 0)
        material = ColorBrightness(material, -0.1 * distance - 0.2);
    else
        material = ColorBrightness(material, -0.1 * distance);

    int wallHeight = static_cast<int>(screenHeight / distance);
    // Clamp wall height to prevent excessive values
    wallHeight = std::min(wallHeight, screenHeight * 2);

    const int drawStart = std::max(0, (screenHeight - wallHeight) / 2);
    const int drawHeight = std::min(wallHeight, screenHeight - drawStart);

    DrawRectangle(screenX, drawStart, 1, drawHeight, material);
}