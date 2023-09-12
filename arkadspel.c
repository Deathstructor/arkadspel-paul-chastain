#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#include "projectile.c"
#include "background.c"

int main()
{
    SetTargetFPS(60);
    InitWindow(480, 800, "Pewpew");

    // Sets the initial player position
    player.pos_x = GetScreenWidth() / 2 - 22;
    player.pos_y = 720;

    LoadPlayer(); // Loads the player textures

    // A while loop where everything that needs to be constantly updated is put in.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BackgroundEffect(); // Draws the background effect

        DrawTexture(ship_img, player.pos_x, player.pos_y, WHITE); // Draws the player textures
        PlayerMovement(); // Loads the player movements and movement limits
        PlayerShooting(); // Loads the projectiles for the player

        EndDrawing();
    }
}