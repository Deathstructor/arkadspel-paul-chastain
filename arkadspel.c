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

int main()
{
    SetTargetFPS(60);
    InitWindow(660, 840, "Pewpew");

    // Sets the initial player position
    player.pos.x = GetScreenWidth() / 2 - 22;
    player.pos.y = 720;

    LoadPlayer();  // Loads the player texture
    LoadEnemies(); // Loads the enemy texture

    // CreatePath();

    // A while loop where everything that needs to be constantly updated is put in.
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BackgroundEffect(); // Draws the background effect

        DrawTexture(ship_img, player.pos.x, player.pos.y, WHITE); // Draws the player textures
        PlayerMovement();                                         // Loads the player movements and movement limits
        PlayerShooting();                                         // Loads the projectiles for the player
        // EnemyMovement();                                          // Loads the enemies movements
        // EnemyHitbox(); // Loads the enemies hitboxes

        FollowPath();
        DrawEnemies(); // Draws the enemy textures

        // DrawLineBezierCubic((Vector2){GetScreenWidth() * 0.5 - 50, -50},
        //                     (Vector2){GetScreenWidth() * 0.5 - 50, 100},
        //                     (Vector2){GetScreenWidth() * 0.5 - 50, -100},
        //                     (Vector2){GetScreenWidth() * 0.5 - 50, 150},
        //                     2,
        //                     YELLOW);
        // DrawLineBezierCubic((Vector2){GetScreenWidth() * 0.5 - 50, 100},
        //                     (Vector2){100, 350},
        //                     (Vector2){GetScreenWidth() * 0.5 - 50, 200},
        //                     (Vector2){100, 250},
        //                     2,
        //                     YELLOW);
        // DrawLineBezierCubic((Vector2){100, 350},
        //                     (Vector2){275, 350},
        //                     (Vector2){100, 500},
        //                     (Vector2){275, 500},
        //                     2,
        //                     YELLOW);

        DrawLineBezierCubic(p1_left.curves[0].startPos, p1_left.curves[0].endPos, p1_left.curves[0].startControlPos, p1_left.curves[0].endControlPos, p1_left.curves[0].thick, p1_left.curves[0].color);
        DrawLineBezierCubic(p1_left.curves[1].startPos, p1_left.curves[1].endPos, p1_left.curves[1].startControlPos, p1_left.curves[1].endControlPos, p1_left.curves[1].thick, p1_left.curves[1].color);
        DrawLineBezierCubic(p1_left.curves[2].startPos, p1_left.curves[2].endPos, p1_left.curves[2].startControlPos, p1_left.curves[2].endControlPos, p1_left.curves[2].thick, p1_left.curves[2].color);
        
        DrawLineBezierCubic(p1_right.curves[0].startPos, p1_right.curves[0].endPos, p1_right.curves[0].startControlPos, p1_right.curves[0].endControlPos, p1_right.curves[0].thick, p1_right.curves[0].color);
        DrawLineBezierCubic(p1_right.curves[1].startPos, p1_right.curves[1].endPos, p1_right.curves[1].startControlPos, p1_right.curves[1].endControlPos, p1_right.curves[1].thick, p1_right.curves[1].color);
        DrawLineBezierCubic(p1_right.curves[2].startPos, p1_right.curves[2].endPos, p1_right.curves[2].startControlPos, p1_right.curves[2].endControlPos, p1_right.curves[2].thick, p1_right.curves[2].color);

        DrawText(TextFormat("Completion: %2f", enemies[0].completion), 8, 8, 16, WHITE);

        EndDrawing();

        // BehaviorUpdate(); // Updates the enemy behavior
    }

    return 0;
}