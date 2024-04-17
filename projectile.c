typedef struct projectile
{
    Vector2 pos;
    int damage;
    Vector2 size;
    float cooldown;
    bool exist;
    Rectangle bullet;
} projectile;

#define max_shots 50
projectile player_projectiles[max_shots];
projectile enemy_projectiles[max_shots];

// Updates the player and enemy projectiles
void UpdateProjectile()
{
    for (int i = 0; i < max_shots; i++)
    {
        if (player_projectiles[i].exist)
        {
            player_projectiles[i].pos.y -= 200 * GetFrameTime(); // The projectile speed and direction
            player_projectiles[i].bullet = (Rectangle){player_projectiles[i].pos.x, player_projectiles[i].pos.y, player_projectiles[i].size.x, player_projectiles[i].size.y};

            // Checks if the projectile exists and removes is if it goes off screen.
            if (player_projectiles[i].pos.y < 0 - player_projectiles->size.y)
            {
                player_projectiles[i].exist = false;
            }
        }

        if (enemy_projectiles[i].exist)
        {
            enemy_projectiles[i].pos.y += 200 * GetFrameTime(); // The projectile speed and direction
            enemy_projectiles[i].bullet = (Rectangle){enemy_projectiles[i].pos.x, enemy_projectiles[i].pos.y, enemy_projectiles[i].size.x, enemy_projectiles[i].size.y};

            // Checks if the projectile exists and removes is if it goes off screen.
            if (enemy_projectiles[i].pos.y > GetScreenHeight())
            {
                enemy_projectiles[i].exist = false;
                enemies[i].shoot = false;
            }
        }
    }
}

// Handles the player shooting
void PlayerShooting()
{
    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // What happens if you press Space
    {
        for (int i = 0; i < max_shots; i++)
        {
            // If a projectile doesn't exist, it will set the following values
            // to the variables for each index of the AoS projectiles.
            if (!player_projectiles[i].exist)
            {
                player_projectiles[i].pos = (Vector2){player.pos.x + 20, player.pos.y - 13};
                player_projectiles[i].size = (Vector2){4, 20};
                player_projectiles[i].exist = true;
                break;
            }
        }
    }
}

// The enemies projectiles
void EnemyShooting()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        // If a projectile doesn't exist, it will set the following values
        // to the variables for each index of the AoS projectiles.
        if (!enemy_projectiles[i].exist && enemies[i].shoot && enemies[i].exist)
        {
            enemy_projectiles[i].pos = (Vector2){enemies[i].pos.x, enemies[i].pos.y};
            enemy_projectiles[i].size = (Vector2){4, 20};
            enemy_projectiles[i].exist = true;
            break;
        }
    }
}

// Function that draws every projectile
void DrawProjectiles()
{
    for (int i = 0; i < max_shots; i++)
    {
        // If a player projectile exists, draw it
        if (player_projectiles[i].exist)
        {
            DrawRectangleRec(player_projectiles[i].bullet, RED);
        }
    }
    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (enemies[i].shoot && enemies[i].exist)
        {
            for (int j = 0; j < max_shots; j++)
            {
                // If an enemy projectile exists, draw it
                if (enemy_projectiles[j].exist)
                {
                    DrawRectangleRec(enemy_projectiles[i].bullet, PURPLE);
                }
            }
        }
    }
}