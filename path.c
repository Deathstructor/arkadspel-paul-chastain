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
    for (int i = 0; i < 20; i++)
    {
        enemies[i].completion = (-i % 10) * 0.4;
    }
}

path p1_left = (path){
    .current_path = 0,
    .curves = {
        (curve){
            .startPos = (Vector2){660 * 0.5 - 50, -100},
            .endPos = (Vector2){660 * 0.5 - 50, 100},
            .startControlPos = (Vector2){660 * 0.5 - 50, 0},
            .endControlPos = (Vector2){660 * 0.5 - 50, 0},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){660 * 0.5 - 50, 100},
            .endPos = (Vector2){100, 350},
            .startControlPos = (Vector2){660 * 0.5 - 50, 200},
            .endControlPos = (Vector2){100, 250},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){100, 350},
            .endPos = (Vector2){275, 350},
            .startControlPos = (Vector2){100, 500},
            .endControlPos = (Vector2){275, 500},
            .thick = 2,
            .color = YELLOW,
        },
    }};

path p1_right = (path){
    .current_path = 0,
    .curves = {
        (curve){
            .startPos = (Vector2){660 * 0.5 + 50, -100},
            .endPos = (Vector2){660 * 0.5 + 50, 100},
            .startControlPos = (Vector2){660 * 0.5 + 50, 0},
            .endControlPos = (Vector2){660 * 0.5 + 50, 0},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){660 * 0.5 + 50, 100},
            .endPos = (Vector2){560, 350},
            .startControlPos = (Vector2){660 * 0.5 + 50, 200},
            .endControlPos = (Vector2){560, 250},
            .thick = 2,
            .color = YELLOW,
        },
        (curve){
            .startPos = (Vector2){560, 350},
            .endPos = (Vector2){385, 350},
            .startControlPos = (Vector2){560, 500},
            .endControlPos = (Vector2){385, 500},
            .thick = 2,
            .color = YELLOW,
        },
    }};

void FollowPath()
{
    if (enemies[0].following > 2)
    {
        enemies[0].current_state = STATE_FORMATION;
    }

    // Follow path 1
    for (int i = 0; i < 20; i++)
    {
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

                if (i < 10)
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