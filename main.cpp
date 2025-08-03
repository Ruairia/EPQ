#include "Vector2D.h"
#include <cmath>
#include <raylib.h>

#include "Player.h"
#include "Map.h"

using namespace raycaster;
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr float moveSpeed = 1; //squares per second
constexpr float turnSpeed = 0.5; //radians per second





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




        // ClearBackground(BLACK);
        DrawRectangle(0, 0, screenWidth, screenHeight/2, SKYBLUE);
        DrawRectangle(0, screenHeight/2, screenWidth, screenHeight/2, DARKGREEN);

        for (int ScreenX = 0; ScreenX < screenWidth; ScreenX++) //Start of ray cast loop
        {
            Vector2D rayDirection = player.direction + player.cameraPlane * (static_cast<float>(ScreenX) / screenWidth - 0.5f);
            Vector2D mapPosition = player.position.truncate();
            Vector2D rayPathDistanceForGridStep = {0,0};
            Vector2D rayCumulativeDistance = {0,0};
            rayPathDistanceForGridStep.x = (rayDirection.x == 0) ? 1e30 : abs(1 / rayDirection.x);
            rayPathDistanceForGridStep.y = (rayDirection.y == 0) ? 1e30 : abs(1 / rayDirection.y);
            Vector2D step = {0,0};
            if (rayDirection.x<0)
            {
                step.x = -1;
                rayCumulativeDistance.x = (player.position.x - mapPosition.x) * rayPathDistanceForGridStep.x;
            }
            else
            {
                step.x = 1;
                rayCumulativeDistance.x = (mapPosition.x + 1 - player.position.x) * rayPathDistanceForGridStep.x;
            }
            if (rayDirection.y<0)
            {
                step.y = -1;
                rayCumulativeDistance.y = (player.position.y - mapPosition.y) * rayPathDistanceForGridStep.y;
            }
            else
            {
                step.y = 1;
                rayCumulativeDistance.y = (mapPosition.y + 1 - player.position.y) * rayPathDistanceForGridStep.y;
            }

            bool hit = false;
            int side;
            while (!hit)
            {
                if (rayCumulativeDistance.x < rayCumulativeDistance.y)
                {
                    rayCumulativeDistance.x += rayPathDistanceForGridStep.x;
                    mapPosition.x += step.x;
                    side=0;
                }
                else
                {
                    rayCumulativeDistance.y += rayPathDistanceForGridStep.y;
                    mapPosition.y += step.y;
                    side=1;
                }
                hit = (Map::getSquare(mapPosition.x,mapPosition.y) != 0);
            }

            double perpendicularDistance;
            if (side == 0)
            {
                perpendicularDistance = (mapPosition.x - player.position.x + (1 - step.x) / 2) / rayDirection.x;
            }
            else
            {
                perpendicularDistance = (mapPosition.y - player.position.y + (1 - step.y) / 2) / rayDirection.y;
            }

            const int lineHeight = static_cast<int>(std::round(screenHeight / perpendicularDistance));
            int drawStart = std::round( -lineHeight / 2 + screenHeight / 2);
            if(drawStart < 0)
            {
                drawStart = 0;
            }
            int drawEnd = std::round(lineHeight / 2 + screenHeight / 2);
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


