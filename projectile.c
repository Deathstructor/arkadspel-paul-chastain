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
projectile enemy_projectiles[30];

// The players projectiles
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

    for (int i = 0; i < max_shots; i++)
    {
        if (player_projectiles[i].exist)
        {
            player_projectiles[i].pos.y -= 8; // The projectile speed and direction
            player_projectiles[i].bullet = (Rectangle){player_projectiles[i].pos.x, player_projectiles[i].pos.y, player_projectiles[i].size.x, player_projectiles[i].size.y};

            // Checks if the projectile exists and removes is if it goes off screen.
            if (player_projectiles[i].pos.y < 0 - player_projectiles->size.y)
            {
                player_projectiles[i].exist = false;
            }

            // Draws the players projectiles
            DrawRectangleRec(player_projectiles[i].bullet, RED);
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

        if (enemy_projectiles[i].exist && enemies[i].shoot && enemies[i].exist)
        {
            enemy_projectiles[i].pos.y += 8; // The projectile speed and direction
            enemy_projectiles[i].bullet = (Rectangle){enemy_projectiles[i].pos.x, enemy_projectiles[i].pos.y, enemy_projectiles[i].size.x, enemy_projectiles[i].size.y};

            // Checks if the projectile exists and removes is if it goes off screen.
            if (enemy_projectiles[i].pos.y > GetScreenHeight())
            {
                if (enemy_projectiles[5].exist && enemy_projectiles[5].pos.y > GetScreenHeight())
                {
                    printf("projectile 5 deleted");
                }
                enemy_projectiles[i].exist = false;
                enemies[i].shoot = false;

                // for (int j = i; j < max_enemy_amount; j++)
                // {
                //     enemy_projectiles[j] = enemy_projectiles[j + 1];
                // }

                
                // enemy_projectiles[i].exist = false;
                // enemies[i].shoot = false;
            }

            // Draws the enemies projectiles
            if (enemy_projectiles[5].exist) {
                printf("projectile %d exists\n", 5);
                DrawRectangleRec(enemy_projectiles[5].bullet, GREEN);
            } else {
                DrawRectangleRec(enemy_projectiles[i].bullet, PURPLE);
            }
        }
    }
}