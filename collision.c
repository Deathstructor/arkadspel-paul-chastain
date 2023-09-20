void EnemyHitbox()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        for (int j = 0; j < max_shots; j++)
        {
            if (CheckCollisionRecs(projectiles[j].bullet, enemies[i].hitbox))
            {
                projectiles[j].exist = false;
                enemies[i].exist = false;
            }
        }
    }
}