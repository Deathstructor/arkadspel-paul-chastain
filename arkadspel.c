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

    // A while loop where everything that needs to be constantly updated is put in.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        if (current_enemies == 0)
        {
            PathOrder(); // Sets the order that the enemies are in when following the path
        }

        BackgroundEffect(); // Draws the background effect

        DrawTexture(ship_img, player.pos.x, player.pos.y, WHITE); // Draws the player textures
        PlayerMovement();                                         // Loads the player movements and movement limits
        PlayerShooting();                                         // Loads the projectiles for the player
        EnemyHitbox();                                            // Loads the enemies hitboxes
        EnemyMovement();                                          // Loads the enemies movements


        DrawGUI(); // Draws the GUI
        printf("          State: %d\n", enemies[0].current_state);
        printf("Current enemies: %d\n", current_enemies);

        // SetRandomNum();
        FollowPath();   // Makes the enemies follow a path
        SetFormation(); // Sets an enemy target position in the formation

        EndDrawing();
    }

    return 0;
}