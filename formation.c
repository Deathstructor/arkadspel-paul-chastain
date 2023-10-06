typedef struct formation
{
    Vector2 pos;
    bool is_full;

    Rectangle pos_tester;
} formation;

formation target_pos[max_enemy_amount];
int check_availability[max_enemy_amount];
int formation_width = 6;
int formation_height = 5;

// Creates the formation layout
void CreateFormation()
{
    for (int x = 0; x < formation_width; x++)
    {
        for (int y = 0; y < formation_height; y++)
        {
            target_pos[x + y * formation_width].pos = (Vector2){x * 70 + 154.5, y * 60 + 74};
        }
    }
}

// void SetRandomNum()
// {
//     int check_num;

//     for (int i = 0; i < max_enemy_amount; i++)
//     {
//         if (enemies[i].random_formation_pos == -1 || formation_box[i].is_full == check_availability[i - 1])
//         {
//             enemies[i].random_formation_pos = GetRandomValue(0, max_enemy_amount - 1);
//             formation_box[enemies[i].random_formation_pos].is_full = true;
//             check_availability[i] = formation_box[enemies[i].random_formation_pos].is_full;
//             check_num++;

//             printf("Formation %d, Full: %d\n", enemies[i].random_formation_pos, formation_box[enemies[i].random_formation_pos].is_full);
//         }
//     }
// }

// Decides which spot in the formation each enemy should go to
void SetFormation()
{

    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (enemies[i].current_state == STATE_FORMATION) // Checks if the enemies state is STATE_FORMATION
        {
            float completion_update = 0.1f * GetFrameTime(); // Variable to update enemies completion
            
            enemies[i].completion_formation += completion_update;

            enemies[i].pos = Vector2Lerp(enemies[i].pos, target_pos[i].pos, enemies[i].completion_formation); // Lerps the enemy to its target position

            // Stopts updating completion and tells the program that the enemy is in position if "completion = 1"
            if (enemies[i].completion_formation >= 1.0f)
            {
                completion_update = 0;
                enemies[i].in_pos = true;
            }
        }
    }
}