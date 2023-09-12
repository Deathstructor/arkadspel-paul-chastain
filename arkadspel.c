#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#include "projectile.c"
#include "background.c"

typedef struct entity
{
    int pos_x;
    int pos_y;
} entity;

int main()
{
    SetTargetFPS(60);
    InitWindow(480, 800, "Pewpew");

    player.pos_x = GetScreenWidth() / 2 - 22;
    player.pos_y = 720;

    LoadPlayer();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BackgroundEffect();

        DrawTexture(ship_img, player.pos_x, player.pos_y, WHITE);
        PlayerMovement();
        PlayerShooting();

        EndDrawing();
    }
}