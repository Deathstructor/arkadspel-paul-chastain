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
    Rectangle hitbox;

    float speed;
    float rotation;
    float spawn_cooldown;
    float completion;

    int current_state;
    int shoot_cooldown;
    int img_randomizer;
    int following;
    // int random_formation_pos;

    bool exist;
    bool in_pos;
} enemy;

const int max_enemy_amount = 30;
enemy enemies[max_enemy_amount];
int current_enemies = NULL;
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

        }
        // DrawRectangleRec(enemies[i].hitbox, YELLOW);
    }
}