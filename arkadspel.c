#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

struct player
{
    int pos_x;
    int pos_y;
} player;

Texture2D ship_img;

void loadPlayer()
{
    Image player_image = LoadImage("Images/player_image.png");
    ImageResize(&player_image, 44, 48);
    ship_img = LoadTextureFromImage(player_image);
    UnloadImage(player_image);
}



int main()
{
    SetTargetFPS(60);
    InitWindow(600, 1000, "Pewpew");

    player.pos_x = GetScreenWidth()/2 - 22;
    player.pos_y = 900;

    loadPlayer();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ship_img, player.pos_x, player.pos_y, WHITE);

        EndDrawing();
    }
}