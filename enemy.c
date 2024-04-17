
typedef enum enemy_states
{
    STATE_PATH,
    STATE_FORMATION,
    STATE_DIVE
} enemy_states;

typedef struct enemy
{
    Vector2 pos;
    Vector2 prev_pos;
    Rectangle hitbox;

    float speed;
    float rotation;
    float spawn_cooldown;
    float shoot_cooldown;
    float completion_path;
    float completion_formation;

    int current_state;
    int img_randomizer;
    int following;
    // int random_formation_pos;

    bool exist;
    bool in_pos;
    bool shoot;
} enemy;

#define max_enemy_amount 30
enemy enemies[max_enemy_amount];

Texture2D alien_img[6];

// Sets the order that the enemies fly in on the screen
void PathOrder()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        enemies[i].completion_path = (-i % (max_enemy_amount / 2)) * 0.4;
    }
}

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

void EnemyMovement()
{
    bool any_alive = false;

    for (int i = 0; i < max_enemy_amount; i++)
    {   
        // What happens if an enemy exists
        if (enemies[i].exist)
        {
            enemies[i].hitbox = (Rectangle){enemies[i].pos.x - 22, enemies[i].pos.y - 24, 44, 48}; // Creates the enemy hitbox
            any_alive = true;

            // Rotates the enemy in the direction it's heading unless it's in position where it will be pointing down instead
            if (enemies[i].current_state == STATE_PATH && !enemies[i].in_pos)
            {
                enemies[i].rotation = Vector2Angle(enemies[i].pos, enemies[i].prev_pos) * RAD2DEG + 90;
            }
            else
            {
                enemies[i].rotation = Lerp(enemies[i].rotation, PI * DEG2RAD, 0.075);
            }

            // Draws the enemy texture
            DrawTexturePro(
                alien_img[0],
                (Rectangle){0, 0, 44, 48},
                (Rectangle){enemies[i].pos.x, enemies[i].pos.y, 44, 48},
                (Vector2){22, 24},
                enemies[i].rotation,
                WHITE);
        }
    }
    if (any_alive)
    {
        return;
    }

    // Assigns values if the enemy does not exist
    for (int i = 0; i < max_enemy_amount; i++)
    {
        enemies[i].pos = (Vector2){-100, -100};
        enemies[i].current_state = STATE_PATH;
        // enemies[i].random_formation_pos = -1;
        enemies[i].following = 0;
        enemies[i].in_pos = false;
        enemies[i].hitbox = (Rectangle){-10, -10, 0, 0};
        enemies[i].spawn_cooldown = 0;
        enemies[i].shoot_cooldown = 0;
        enemies[i].completion_formation = 0;
        enemies[i].exist = true;
    }

    PathOrder();
}

void EnemyShootInterval()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (enemies[i].current_state == STATE_FORMATION && !enemies[i].shoot)
        {
            float set_shoot_cooldown = GetRandomValue(5, 45);
            float update_shoot_cooldown = 1.0f * GetFrameTime();

            enemies[i].shoot_cooldown += update_shoot_cooldown;
            
            if (enemies[i].shoot_cooldown >= set_shoot_cooldown && GetRandomValue(1, 50) == 1)
            {
                enemies[i].shoot = true;
                enemies[i].shoot_cooldown = 0;
            }
        }
    }
    // printf("Cooldown: %f\n", enemies[0].shoot_cooldown);
    // printf("Position: %f, %f\n", enemies[0].pos.x, enemies[0].pos.y);
}