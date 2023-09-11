#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

struct player
{
    int pos_x;
    int pos_y;
    int speed;
} player;

typedef struct entity
{
    int pos_x;
    int pos_y;
} entity;

typedef struct projectile
{
    Vector2 pos;
    int speed;
    int damage;
    Vector2 size;
    float cooldown;
    bool exist;
} projectile;

Texture2D ship_img;

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
    if (player.pos_y < 750)
    {
        player.pos_y = 750;
    }
    if (player.pos_y > GetScreenHeight() - 48)
    {
        player.pos_y = GetScreenHeight() - 48;
    }
}

const int max_shots = 50;
projectile projectiles[max_shots] = {0};

void PlayerShooting()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        for (int i = 0; i < max_shots; i++)
        {
            if (!projectiles[i].exist)
            {
                projectiles[i].pos = (Vector2){player.pos_x + 20, player.pos_y - 12};
                projectiles[i].size = (Vector2){4, 20};
                projectiles[i].exist = true;
                break;
            }
        }
    }
    
    for (int i = 0; i < max_shots; i++)
    {
        if (projectiles[i].exist)
        {
            projectiles[i].pos.y -= 8;

            if (projectiles[i].exist && projectiles[i].pos.y < 0 - projectiles->size.y)
            {
                projectiles[i].exist = false;
            }

            DrawRectangle(projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].size.x, projectiles[i].size.y, RED);
        }
    }
}

int main()
{
    SetTargetFPS(60);
    InitWindow(600, 1000, "Pewpew");

    player.pos_x = GetScreenWidth() / 2 - 22;
    player.pos_y = 900;

    LoadPlayer();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ship_img, player.pos_x, player.pos_y, WHITE);
        PlayerMovement();
        PlayerShooting();

        EndDrawing();
    }
}