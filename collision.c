void EnemyHitbox()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        for (int j = 0; j < max_shots; j++)
        {
            if (!enemies[i].exist)
            {
                continue;
            }
            
            if (CheckCollisionRecs(enemies[i].hitbox, player_projectiles[j].bullet) && player_projectiles[j].exist)
            {
                player_projectiles[j].exist = false;
                player.score += 100;
                enemies[i].exist = false;
            }

            if (CheckCollisionRecs(player.hitbox, enemy_projectiles[i].bullet) && enemy_projectiles[i].exist)
            {
                enemy_projectiles[i].exist = false;
                player.lives--;
            }

            if (CheckCollisionRecs(enemies[i].hitbox, player.hitbox))
            {
                player.score += 100;
                player.lives--;
                enemies[i].exist = false;
            }
        }
    }
}