typedef enum behavior
{
    ATTACK_MODE,
    PASSIVE_MODE,
    DEFENCE_MODE
} behavior;

typedef enum enemy_states
{
    STATE_PATH,
    STATE_FORMATION,
    STATE_DIVE
} enemy_states;

typedef struct enemy
{
    Vector2 prev_pos;
    Vector2 pos;
    float speed;
    float rotation;

    Vector2 random_passive_pos;
    behavior behaviors;
    int random_behavior_num;

    int current_state;

    float spawn_cooldown;
    int shoot_cooldown;
    int img_randomizer;
    bool exist;
    Rectangle hitbox;

    int following;
    float completion;
    bool in_pos;
    // int random_formation_pos;
} enemy;

const int max_enemy_amount = 30;
enemy enemies[max_enemy_amount];
int current_enemies = 0;
int behavior_cooldown = 0; // Variable used as cooldown timer for the behavior to change

Texture2D alien_img[6];

// Loads all enemy textures
void LoadEnemies()
{
    // char *name = TextFormat("Images/enemy_image%i.png", i);
    // alien_img[i - 1] = LoadTexture(name);

    Image enemy_image1 = LoadImage("Images/enemy_image1.png");
    Image enemy_image2 = LoadImage("Images/enemy_image2.png");
    Image enemy_image3 = LoadImage("Images/enemy_image3.png");
    Image enemy_image4 = LoadImage("Images/enemy_image4.png");
    Image enemy_image5 = LoadImage("Images/enemy_image5.png");
    Image enemy_image6 = LoadImage("Images/enemy_image6.png");

    alien_img[0] = LoadTextureFromImage(enemy_image1);
    alien_img[1] = LoadTextureFromImage(enemy_image2);
    alien_img[2] = LoadTextureFromImage(enemy_image3);
    alien_img[3] = LoadTextureFromImage(enemy_image4);
    alien_img[4] = LoadTextureFromImage(enemy_image5);
    alien_img[5] = LoadTextureFromImage(enemy_image6);

    UnloadImage(enemy_image1);
    UnloadImage(enemy_image2);
    UnloadImage(enemy_image3);
    UnloadImage(enemy_image4);
    UnloadImage(enemy_image5);
    UnloadImage(enemy_image6);
}

void DrawEnemies()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        // DrawTexture(alien_img[0], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 0)
            DrawTexture(alien_img[0], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 1)
            DrawTexture(alien_img[1], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 2)
            DrawTexture(alien_img[2], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 3)
            DrawTexture(alien_img[3], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 4)
            DrawTexture(alien_img[4], enemies[i].pos.x, enemies[i].pos.y, WHITE);
        if (enemies[i].img_randomizer == 5)
            DrawTexture(alien_img[5], enemies[i].pos.x, enemies[i].pos.y, WHITE);
    }
}

// The cooldown for the enemies to change behavior
// void BehaviorUpdate()
// {
//     if (behavior_cooldown <= 0)
//     {
//         for (int i = 0; i < max_enemy_amount; i++)
//         {
//             enemies[i].random_behavior_num = GetRandomValue(0, 2);                                                                          // Randomizes a new behavior
//             enemies[i].random_passive_pos = (Vector2){GetScreenWidth() * 0.5 + GetRandomValue(-150, 150), 200 + GetRandomValue(-200, 200)}; // Randomizes a new position for passive mode enemies
//         }
//         behavior_cooldown = 300;
//     }
//     behavior_cooldown -= GetFrameTime();
// }

void EnemyMovement()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        // Assigns values if the enemy does not exist
        if (!enemies[i].exist)
        {
            enemies[i].pos = (Vector2){0, -50};
            enemies[i].current_state = 0;
            enemies[i].in_pos = false;
            // enemies[i].random_formation_pos = -1;
            enemies[i].following = 0;
            enemies[i].spawn_cooldown = 0;
            enemies[i].exist = true;
        }

        if (enemies[i].exist)
        {
            enemies[i].hitbox = (Rectangle){enemies[i].pos.x - 22, enemies[i].pos.y - 24, 44, 48};

            if (enemies[i].current_state == STATE_PATH && !enemies[i].in_pos)
            {
                enemies[i].rotation = Vector2Angle(enemies[i].pos, enemies[i].prev_pos) * RAD2DEG + 90;
            }
            else
            {
                enemies[i].rotation = Lerp(enemies[i].rotation, PI * DEG2RAD, 0.075);
            }

            DrawTexturePro(
                alien_img[0],
                (Rectangle){0, 0, 44, 48},
                (Rectangle){enemies[i].pos.x, enemies[i].pos.y, 44, 48},
                (Vector2){22, 24},
                enemies[i].rotation,
                WHITE);

            // switch (enemies[i].random_behavior_num)
            // {
            // case ATTACK_MODE:
            //     enemies[i].speed = 0.018;
            //     enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
            //     break;
            // case PASSIVE_MODE:
            //     enemies[i].speed = 0.008;
            //     enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){enemies[i].random_passive_pos.x, enemies[i].random_passive_pos.y}, enemies[i].speed);
            //     break;
            // case DEFENCE_MODE:
            //     enemies[i].speed = 0.012;
            //     // if (CheckCollisionPointRec(enemies[i].view_area, INPUT PROJECTILE CODE HERE))
            //     // {
            //     //     /* code */
            //     // }

            //     enemies[i].pos = Vector2Lerp(enemies[i].pos, (Vector2){player.pos.x, player.pos.y - 200}, enemies[i].speed);
            //     // TODO: Use pointrec
            //     break;
            // default:
            //     break;
            // }
            // enemies[i].view_area = (Rectangle){enemies[i].pos.x - 50, enemies[i].pos.y, enemies[i].pos.x - 50, enemies[i].pos.y + 200};
        }
        // DrawRectangleRec(enemies[i].hitbox, YELLOW);
    }
}