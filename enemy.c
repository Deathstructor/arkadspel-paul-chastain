typedef enum behavior
{
    ATTACK_MODE,
    PASSIVE_MODE,
    DEFENCE_MODE
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
    Rectangle view_area;
    Color col;
} enemy;

const int max_enemy_amount = 10;
enemy enemies[max_enemy_amount];
int current_enemies = 0;
int behavior_cooldown = 0; // Variable used as cooldown timer for the behavior to change

Texture2D enemy_img[6];

// Loads all enemy textures
void LoadEnemies()
{
    Image enemy_image1 = LoadImage("Images/enemy_image1.png");
    Image enemy_image2 = LoadImage("Images/enemy_image2.png");
    Image enemy_image3 = LoadImage("Images/enemy_image3.png");
    Image enemy_image4 = LoadImage("Images/enemy_image4.png");
    Image enemy_image5 = LoadImage("Images/enemy_image5.png");
    Image enemy_image6 = LoadImage("Images/enemy_image6.png");

    enemy_img[0] = LoadTextureFromImage(enemy_image1);
    enemy_img[1] = LoadTextureFromImage(enemy_image2);
    enemy_img[2] = LoadTextureFromImage(enemy_image3);
    enemy_img[3] = LoadTextureFromImage(enemy_image4);
    enemy_img[4] = LoadTextureFromImage(enemy_image5);
    enemy_img[5] = LoadTextureFromImage(enemy_image6);

    UnloadImage(enemy_image1);
    UnloadImage(enemy_image2);
    UnloadImage(enemy_image3);
    UnloadImage(enemy_image4);
    UnloadImage(enemy_image5);
    UnloadImage(enemy_image6);
}

// The cooldown for the enemies to change behavior
void BehaviorUpdate()
{
    if (behavior_cooldown <= 0)
    {
        for (int i = 0; i < max_enemy_amount; i++)
        {
            enemies[i].random_behavior_num = GetRandomValue(0, 2);                                                                          // Randomizes a new behavior
            enemies[i].random_passive_pos = (Vector2){GetScreenWidth() * 0.5 + GetRandomValue(-150, 150), 200 + GetRandomValue(-200, 200)}; // Randomizes a new position for passive mode enemies
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
        // Assigns values if the enemy does not exist
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
                enemies[i].view_area = (Rectangle){enemies[i].pos.x - 50, enemies[i].pos.y, enemies[i].pos.x - 50, enemies[i].pos.y + 200};
                break;
            case PASSIVE_MODE:
                enemies[i].speed = 0.008;
                enemies[i].col = GREEN;
                enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){enemies[i].random_passive_pos.x, enemies[i].random_passive_pos.y}, enemies[i].speed);
                enemies[i].view_area = (Rectangle){enemies[i].pos.x - 50, enemies[i].pos.y, enemies[i].pos.x - 50, enemies[i].pos.y + 200};
                break;
            case DEFENCE_MODE:
                enemies[i].speed = 0.012;
                enemies[i].col = BLUE;
                // if (CheckCollisionPointRec(enemies[i].view_area, INPUT PROJECTILE CODE HERE))
                // {
                //     /* code */
                // }

                enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
                enemies[i].view_area = (Rectangle){enemies[i].pos.x - 50, enemies[i].pos.y, enemies[i].pos.x - 50, enemies[i].pos.y + 200};
                // TODO: Use pointrec
                break;
            default:
                break;
            }
        }
        // DrawRectangleRec(enemies[i].view_area, YELLOW);

        DrawRectangle(enemies[i].pos.x, enemies[i].pos.y, 15, 15, enemies[i].col);
    }
}