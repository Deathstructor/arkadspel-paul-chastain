#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

struct player
{
    int pos_x;
    int pos_y;
} player;

Texture2D ship_img;

void LoadPlayer() 
{
    Image player_image = LoadImage("Images/player_image.png");
    ImageResize(&player_image, 44, 48);
    ship_img = LoadTextureFromImage(player_image);
    UnloadImage(player_image);
}

void PlayerMovement()
{
    // Player movement on keypress
    if (IsKeyDown(KEY_A))
    {
        player.pos_x -= 4;
    }
    if (IsKeyDown(KEY_D))
    {
        player.pos_x += 4;
    }
    if (IsKeyDown(KEY_W))
    {
        player.pos_y -= 4;
    }
    if (IsKeyDown(KEY_S))
    {
        player.pos_y += 4;
    }
    
    // Player movement limits
    if (player.pos_x < 0)
    {
        player.pos_x = 0;
    }
    if (player.pos_x > GetScreenWidth() - 44)
    {
        player.pos_x = GetScreenWidth() - 44;
    }
    if (player.pos_y < 750)
    {
        player.pos_y = 750;
    }
    if (player.pos_y > GetScreenHeight() - 48)
    {
        player.pos_y = GetScreenHeight() - 48;
    }    
}

int main()
{
    SetTargetFPS(60);
    InitWindow(600, 1000, "Pewpew");

    player.pos_x = GetScreenWidth()/2 - 22;
    player.pos_y = 900;

    LoadPlayer();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ship_img, player.pos_x, player.pos_y, WHITE);
        PlayerMovement();

        EndDrawing();
    }
}