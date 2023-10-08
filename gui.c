void DrawGUI()
{
    DrawText(TextFormat("Score: %d", player.score), 20, 20, 20, WHITE);

    if (player.lives > 0)
    {
        DrawTextureEx(ship_img, (Vector2){10, 790}, 0, 0.75f, GRAY);
    }
    if (player.lives > 1)
    {
        DrawTextureEx(ship_img, (Vector2){50, 790}, 0, 0.75f, GRAY);
    }
    if (player.lives > 2)
    {
        DrawTextureEx(ship_img, (Vector2){90, 790}, 0, 0.75f, GRAY);
    }
    if (player.lives > 3)
    {
        DrawTextureEx(ship_img, (Vector2){130, 790}, 0, 0.75f, GRAY);
    }
    if (player.lives > 4)
    {
        DrawTextureEx(ship_img, (Vector2){170, 790}, 0, 0.75f, GRAY);
    }
}