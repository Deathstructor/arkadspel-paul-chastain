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

void PathOrder()
{
    for (int i = 0; i < max_enemy_amount; i++)
    {
        enemies[i].completion = (-i % (max_enemy_amount / 2)) * 0.4;
    }
}

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

void FollowPath()
{
    // Follow path 1
    for (int i = 0; i < max_enemy_amount; i++)
    {
        if (enemies[i].current_state == STATE_PATH)
        {
            if (enemies[i].following > 2)
            {
                enemies[i].current_state = STATE_FORMATION;
                
            }

            enemies[i].spawn_cooldown += 0.5f * GetFrameTime();
            if (enemies[i].spawn_cooldown > 1 && enemies[i].following < 3)
            {
                enemies[i].completion += 1.0f * GetFrameTime();
                if (enemies[i].completion >= 1.0f)
                {
                    enemies[i].completion -= 1.0f;
                    enemies[i].following++;
                }
                else
                {
                    enemies[i].prev_pos = enemies[i].pos;

                    if (i < 15)
                    {
                        enemies[i].pos = QuadraticLerp(p1_left.curves[enemies[i].following], enemies[i].completion);
                    }
                    else
                    {
                        enemies[i].pos = QuadraticLerp(p1_right.curves[enemies[i].following], enemies[i].completion);
                    }
                }
            }
        }
    }
}