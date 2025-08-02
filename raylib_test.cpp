//
// Created by ruairi on 31/07/2025.
//

#include "raylib_test.h"

#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Test");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Raylib is working!", 200, 280, 20, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
