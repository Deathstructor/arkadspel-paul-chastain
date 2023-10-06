#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.c"
#include "projectile.c"
#include "background.c"
#include "enemy.c"
#include "collision.c"
#include "path.c"
#include "formation.c"

int main()
{
    SetTargetFPS(60);
    InitWindow(660, 840, "Pewpew");

    // Sets the initial player position
    player.pos.x = GetScreenWidth() / 2 - 22;
    player.pos.y = 720;

    LoadPlayer();      // Loads the player texture
    LoadEnemies();     // Loads the enemy texture
    PathOrder();       // Sets the order that the enemies are in when following the path
    CreateFormation(); // Creates the formation shape

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
        EnemyHitbox();                                            // Loads the enemies hitboxes

        // SetRandomNum();
        FollowPath();
        SetFormation();

        EndDrawing();
    }

    return 0;
}