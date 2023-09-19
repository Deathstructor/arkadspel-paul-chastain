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
    Vector2 random_passive_pos;
    float speed;
    behavior behaviors;
    int random_behavior_num;
    int shoot_cooldown;
    bool exist;
    Color col;
} enemy;

const int max_enemy_amount = 10;
enemy enemies[max_enemy_amount];
int current_enemies = 0;
int behavior_cooldown = 0;

void LoadEnemies()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
    }
}

void BehaviorUpdate()
{
    if (behavior_cooldown <= 0)
    {
        for (int i = 0; i < max_enemy_amount; i++)
        {
            enemies[i].random_behavior_num = GetRandomValue(0, BEHAVIOR_NUM);
            enemies[i].random_passive_pos = (Vector2){GetScreenWidth() * 0.5 + GetRandomValue(-150, 150), 200 + GetRandomValue(-200, 200)};
        }
        behavior_cooldown = 300;
    }
    behavior_cooldown -= GetFrameTime();
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

            switch (enemies[i].random_behavior_num)
            {
            case ATTACK_MODE:
                enemies[i].speed = 0.018;
                enemies[i].col = RED;
                enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
                break;
            case PASSIVE_MODE:
                enemies[i].speed = 0.008;
                enemies[i].col = GREEN;
                enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){enemies[i].random_passive_pos.x, enemies[i].random_passive_pos.y}, enemies[i].speed);
                break;
            case DEFENCE_MODE:
                enemies[i].speed = 0.012;
                enemies[i].col = BLUE;
                enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
                // TODO: Use pointrec
                break;
            default:
                break;
            }
        }
        DrawRectangle(enemies[i].pos.x, enemies[i].pos.y, 15, 15, enemies[i].col);
    }
}