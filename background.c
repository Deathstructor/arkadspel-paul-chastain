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
        // If the particle doesn't exist, the following values will be set
        // to the variables of each index for the AoS particles.
        if (!particles[i].exist)
        {
            particles[i].pos = (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(-700, 0)};
            particles[i].speed = GetRandomValue(2, 5);
            particles[i].exist = true;
        }

        // Checks if a particle exists and removes it if it goes off screen. Also draws the particle.
        if (particles[i].exist)
        {
            particles[i].pos.y += particles[i].speed;

            if (particles[i].pos.y > GetScreenHeight())
            {
                particles[i].exist = false;
            }

            if (particles[i].speed == 2)
            {
                DrawRectangle(particles[i].pos.x, particles[i].pos.y, 1, 1, DARKGRAY);
            }
            if (particles[i].speed == 3)
            {
                DrawRectangle(particles[i].pos.x, particles[i].pos.y, 1, 1, GRAY);
            }
            if (particles[i].speed == 4)
            {
                DrawRectangle(particles[i].pos.x, particles[i].pos.y, 1, 1, LIGHTGRAY);
            }
            if (particles[i].speed == 5)
            {
                DrawRectangle(particles[i].pos.x, particles[i].pos.y, 1, 1, WHITE);
            }
        }
    }
}