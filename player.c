#include "raylib.h"

struct player
{
    Vector2 pos;
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
        player.pos.x -= player.speed;
    }
    if (IsKeyDown(KEY_D))
    {
        player.pos.x += player.speed;
    }
    if (IsKeyDown(KEY_W))
    {
        player.pos.y -= player.speed;
    }
    if (IsKeyDown(KEY_S))
    {
        player.pos.y += player.speed;
    }

    // Player movement limits
    if (player.pos.x < 0)
    {
        player.pos.x = 0;
    }
    if (player.pos.x > GetScreenWidth() - 44)
    {
        player.pos.x = GetScreenWidth() - 44;
    }
    if (player.pos.y < 600)
    {
        player.pos.y = 600;
    }
    if (player.pos.y > GetScreenHeight() - 48)
    {
        player.pos.y = GetScreenHeight() - 48;
    }
}