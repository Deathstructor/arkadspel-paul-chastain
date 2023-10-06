typedef struct curve
{
    Vector2 startPos;
    Vector2 endPos;
    Vector2 startControlPos;
    Vector2 endControlPos;
    float thick;
    Color color;
} curve;

typedef struct path
{
    curve curves[3];
    char current_path;
} path;

// Calulate linear interpolation along a Bézier curve
Vector2 QuadraticLerp(curve c, float t)
{
    Vector2 A = Vector2Lerp(c.startPos, c.startControlPos, t);
    Vector2 B = Vector2Lerp(c.startControlPos, c.endControlPos, t);
    Vector2 C = Vector2Lerp(c.endControlPos, c.endPos, t);
    Vector2 D = Vector2Lerp(A, B, t);
    Vector2 E = Vector2Lerp(B, C, t);
    Vector2 point = Vector2Lerp(D, E, t);
    return point;
}

// The shape of the left path for path 1
path p1_left = (path){
    .current_path = 0,
    .curves = {
        (curve){
            .startPos = (Vector2){660 * 0.5 - 50, -100},
            .endPos = (Vector2){660 * 0.5 - 50, 150},
            .startControlPos = (Vector2){660 * 0.5 - 50, 0},
            .endControlPos = (Vector2){660 * 0.5 - 50, 50},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){660 * 0.5 - 50, 150},
            .endPos = (Vector2){100, 400},
            .startControlPos = (Vector2){660 * 0.5 - 50, 250},
            .endControlPos = (Vector2){100, 300},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){100, 400},
            .endPos = (Vector2){275, 400},
            .startControlPos = (Vector2){100, 550},
            .endControlPos = (Vector2){275, 550},
            .thick = 2,
            .color = YELLOW,
        },
    }};

// The shape of the right path for path 1
path p1_right = (path){
    .current_path = 0,
    .curves = {
        (curve){
            .startPos = (Vector2){660 * 0.5 + 50, -100},
            .endPos = (Vector2){660 * 0.5 + 50, 150},
            .startControlPos = (Vector2){660 * 0.5 + 50, 0},
            .endControlPos = (Vector2){660 * 0.5 + 50, 50},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){660 * 0.5 + 50, 150},
            .endPos = (Vector2){560, 400},
            .startControlPos = (Vector2){660 * 0.5 + 50, 250},
            .endControlPos = (Vector2){560, 300},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){560, 400},
            .endPos = (Vector2){385, 400},
            .startControlPos = (Vector2){560, 550},
            .endControlPos = (Vector2){385, 550},
            .thick = 2,
            .color = YELLOW,
        },
    }};

// Makes the enemies follow a path
void FollowPath()
{
    // Follow path 1
    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (enemies[i].current_state == STATE_PATH) // Checks if the current state is path to make the enemy follow a path
        {

            enemies[i].spawn_cooldown += 0.5f * GetFrameTime(); // The enemy spawn cooldown
            // Checks if an enemy should spawn or not
            if (enemies[i].spawn_cooldown > 1 && enemies[i].following < 3)
            {
                // Updates "completion" that tells where on a curve an enemy should be.
                // Also update which curve the enemy is on in the path and moves it to
                // the next one when it reaches the end of a curve.
                enemies[i].completion_path += 1.0f * GetFrameTime();
                if (enemies[i].completion_path >= 1.0f)
                {
                    enemies[i].completion_path -= 1.0f;
                    enemies[i].following++;
                }
                else
                {
                    enemies[i].prev_pos = enemies[i].pos; // Used to check which direction the enemy should be facing

                    // Moves the enemies on the left and right path
                    if (i < 15)
                    {
                        enemies[i].pos = QuadraticLerp(p1_left.curves[enemies[i].following], enemies[i].completion_path);
                    }
                    else
                    {
                        enemies[i].pos = QuadraticLerp(p1_right.curves[enemies[i].following], enemies[i].completion_path);
                    }
                }
            }
            
            // Checks if an enemy has reached the paths end and sets its state to STATE_FORMATION to get into a formation
            if (enemies[i].following > 2)
            {
                enemies[i].current_state = STATE_FORMATION;
            }
        }
    }
}