#include "raylib.h"

struct player
{
    int pos_x;
    int pos_y;
    int speed;
} player;

Texture2D ship_img;

// Function that loads the player textures
void LoadPlayer()
{
    Image player_image = LoadImage("Images/player_image.png");
    ship_img = LoadTextureFromImage(player_image);
    UnloadImage(player_image);
}

void PlayerMovement()
{
    player.speed = 4;

    // Player movement on keypress
    if (IsKeyDown(KEY_A))
    {
        player.pos_x -= player.speed;
    }
    if (IsKeyDown(KEY_D))
    {
        player.pos_x += player.speed;
    }
    if (IsKeyDown(KEY_W))
    {
        player.pos_y -= player.speed;
    }
    if (IsKeyDown(KEY_S))
    {
        player.pos_y += player.speed;
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
    if (player.pos_y < 600)
    {
        player.pos_y = 600;
    }
    if (player.pos_y > GetScreenHeight() - 48)
    {
        player.pos_y = GetScreenHeight() - 48;
    }
}