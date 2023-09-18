typedef enum behavior
{
    ATTACK_MODE,
    PASSIVE_MODE,
    DEFENCE_MODE,
    BEHAVIOR_NUM
} behavior;

typedef struct enemy
{
    Vector2 pos;
    float speed;
    behavior behaviors;
    bool exist;
} enemy;

const int max_enemy_amount = 10;
enemy enemies[max_enemy_amount];
int current_enemies = 0;
float enemy_behavior_cooldown = 0;

void LoadEnemies()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
    }
}

void EnemyMovement()
{
    current_enemies = GetRandomValue(1, max_enemy_amount);

    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (!enemies[i].exist)
        {
            enemies[i].pos = (Vector2){GetRandomValue(0, GetScreenWidth()), -50};
            enemies[i].exist = true;
        }

        if (enemies[i].exist)
        {
            if (enemies[i].pos.y < 50)
            {
                enemies[i].pos.y++;
            }
        }

        DrawRectangle(enemies[i].pos.x, enemies[i].pos.y, 15, 15, GREEN);
    }
}

void BehaviorUpdate()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        switch (GetRandomValue(0, BEHAVIOR_NUM))
        {
        case ATTACK_MODE:
            enemies[i].speed = 0.01;
            enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 300}, enemies[i].speed);
            break;
        case PASSIVE_MODE:
            enemies[i].speed = 0.003;
            enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){GetRandomValue(-100, 100), GetRandomValue(-100, 100)}, enemies[i].speed);
            break;
        case DEFENCE_MODE:
            enemies[i].speed = 0.006;
            // Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
            break;
        default:
            break;
        }

        
    }  
}