void EnemyHitbox()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        for (int j = 0; j < max_shots; j++)
        {
            if (CheckCollisionRecs(enemies[i].hitbox, projectiles[j].bullet) && projectiles[j].exist)
            {
                projectiles[j].exist = false;
                enemies[i].current_state = STATE_DEAD;
                current_enemies--;
                player.score += 100;
                enemies[i].exist = false;
            }
        }
    }
}