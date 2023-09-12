#include "raylib.h"
#include "player.c"

typedef struct projectile
{
    Vector2 pos;
    int speed;
    int damage;
    Vector2 size;
    float cooldown;
    bool exist;
} projectile;

const int max_shots = 50;
projectile projectiles[max_shots] = {0};

void PlayerShooting()
{
    if (IsKeyPressed(KEY_SPACE)) // What happens if you press Space
    {
        for (int i = 0; i < max_shots; i++)
        {
            // If a projectile doesn't exist, it will set the following values
            // to the variables for each index of the AoS projectiles.
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
        // Checks if the projectile exists and removes is if it goes off screen.
        if (projectiles[i].exist)
        {
            projectiles[i].pos.y -= 8;

            if (projectiles[i].pos.y < 0 - projectiles->size.y)
            {
                projectiles[i].exist = false;
            }

            // Draws the projectile
            DrawRectangle(projectiles[i].pos.x, projectiles[i].pos.y, projectiles[i].size.x, projectiles[i].size.y, RED);
        }
    }
}