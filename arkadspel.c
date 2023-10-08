#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.c"
#include "enemy.c"
#include "projectile.c"
#include "background.c"
#include "collision.c"
#include "path.c"
#include "formation.c"
#include "gui.c"

int main()
{
    SetTargetFPS(60);
    InitWindow(660, 840, "Pewpew");

    // Sets the initial player position
    player.pos.x = GetScreenWidth() / 2 - 22;
    player.pos.y = 720;

    LoadPlayer();      // Loads the player texture
    LoadEnemies();     // Loads the enemy texture
    CreateFormation(); // Creates the formation shape
    PathOrder();       // Sets the order that the enemies are in when following the path

    // A while loop where everything that needs to be constantly updated is put in.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        BackgroundEffect(); // Draws the background effect

        FollowPath();   // Makes the enemies follow a path
        SetFormation(); // Sets an enemy target position in the formation
        // SetRandomNum();

        DrawTexture(ship_img, player.pos.x, player.pos.y, WHITE); // Draws the player textures
        PlayerMovement();                                         // Loads the player movements and movement limits
        PlayerShooting();                                         // Draws the projectiles for the player
        EnemyShooting();                                          // Draws the projectiles for the enemies
        EnemyShootInterval();                                     // Loads the interval at which the enemies will shoot
        EnemyHitbox();                                            // Loads the enemies hitboxes
        EnemyMovement();                                          // Loads the enemies movements

        DrawGUI(); // Draws the GUI

        EndDrawing();
    }

    return 0;
}