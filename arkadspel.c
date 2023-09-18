#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.c"
#include "projectile.c"
#include "background.c"
#include "enemy.c"

int main()
{
    SetTargetFPS(60);
    InitWindow(480, 800, "Pewpew");

    // Sets the initial player position
    player.pos.x = GetScreenWidth() / 2 - 22;
    player.pos.y = 720;

    LoadPlayer();  // Loads the player texture
    LoadEnemies(); // Loads the enemy texture

    // A while loop where everything that needs to be constantly updated is put in.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BackgroundEffect(); // Draws the background effect

        DrawTexture(ship_img, player.pos.x, player.pos.y, WHITE); // Draws the player textures
        PlayerMovement();                                         // Loads the player movements and movement limits
        PlayerShooting();                                         // Loads the projectiles for the player
        EnemyMovement();                                          // Loads the enemies movements

        EndDrawing();
        enemy_behavior_cooldown -= GetFrameTime();
        if (enemy_behavior_cooldown <= 0)
        {
            BehaviorUpdate();
            enemy_behavior_cooldown = 5;
        }
    }

    return 0;
}