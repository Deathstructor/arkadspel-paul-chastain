#include "raylib.h"

typedef struct particle
{
    Vector2 pos;
    int speed;
    bool exist;
} particle;

const int particle_amount = 500;
particle particles[particle_amount];

void BackgroundEffect()
{
    for (int i = 0; i < particle_amount; i++)
    {
        if (!particles[i].exist)
        {
            particles[i].pos = (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(-700, 0)};
            particles[i].speed = GetRandomValue(2, 5);
            particles[i].exist = true;
        }

        if (particles[i].exist)
        {
            particles[i].pos.y += particles[i].speed;

            if (particles[i].pos.y > GetScreenHeight())
            {
                particles[i].exist = false;
            }
            
            DrawRectangle(particles[i].pos.x, particles[i].pos.y, 1, 1, WHITE);
        }   
    }
}