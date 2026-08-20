#include <raylib.h>

// Checks if the Asteroid touches the Grenade
void Collide_Grenade_Asteroid(int &a_x, int &b_x, int &a_y, int &b_y, int a_width, int b_width, int a_height, int b_height, int &a_speed, int &b_speed, bool &b_active, Sound ExplodeSound, int &Score)
{
    if (a_x < b_x + b_width && b_x < a_x + a_width && a_y < b_y + b_height && b_y < a_y + a_height)
    {
        a_y = 0;
        a_speed = GetRandomValue(2, 5);
        a_x = GetRandomValue(0, GetScreenWidth() - a_width);
        b_active = false;
        PlaySound(ExplodeSound);
        Score += 1;
    }
}

// Checks if the Player Hits the
void Player_Hit_Asteroid(int &a_x, int &b_x, int &a_y, int &b_y, int a_width, int b_width, int a_height, int b_height, int a_active, int &Lives)
{
    if (a_x < b_x + b_width && b_x < a_x + a_width && a_y < b_y + b_height && b_y < a_y + a_height)
    {
        a_x = GetRandomValue(0, GetScreenWidth() - a_width);
        a_y = 0;
        Lives -= 1;
    }
}

int main()
{
    // Starts the game window and sets the fps of the game
    InitWindow(1200, 800, "Space Shooters");
    InitAudioDevice();
    SetTargetFPS(60);
    // These are all the game variables required to run the game
    int GameActive = 1;
    int PlayerWidth = 124;
    int PlayerHeight = 124;
    int PlayerX = 600 - (PlayerWidth / 2);
    int PlayerY = 720 - (PlayerHeight / 2);
    int PlayerSpeed = 7;
    int AsteroidWidth = 176;
    int AsteroidHeight = 176;
    int AsteroidX[5] = {GetRandomValue(0, GetScreenWidth() - AsteroidWidth), GetRandomValue(0, GetScreenWidth() - AsteroidWidth), GetRandomValue(0, GetScreenWidth() - AsteroidWidth), GetRandomValue(0, GetScreenWidth() - AsteroidWidth), GetRandomValue(0, GetScreenWidth() - AsteroidWidth)};
    int AsteroidY[5] = {0, 0, 0, 0, 0};
    int AsteroidSpeed[5] = {GetRandomValue(2, 5), GetRandomValue(2, 5), GetRandomValue(2, 5), GetRandomValue(2, 5), GetRandomValue(2, 5)};
    bool DrawAsteroid = true;
    int GrenadeWidth = 30;
    int GrenadeHeight = 30;
    int GrenadeX[3] = {PlayerX + (GrenadeWidth + PlayerSpeed), PlayerX + (GrenadeWidth + PlayerSpeed), PlayerX + (GrenadeWidth + PlayerSpeed)};
    int GrenadeY[3] = {PlayerY + (PlayerHeight / 2), PlayerY + (PlayerHeight / 2), PlayerY + (PlayerHeight / 2)};
    int OldGrenadeX[3];
    int GrenadeSpeed = 15;
    bool GrenadeActive = false;
    bool MeasuringOldX = true;
    Texture2D PlayerSprite = LoadTexture("Sprites/Player.png");
    Texture2D GrenadeTexture = LoadTexture("Sprites/Grenade.png");
    Texture2D AsteroidSprite = LoadTexture("Sprites/Asteroid.png");
    Texture2D Background = LoadTexture("Sprites/Background.png");
    Sound ExplodeSound = LoadSound("Sounds/Explosion.wav");
    Sound GrenadeShooting = LoadSound("Sounds/GrenadeShooting.wav");
    int Score = 1;
    int Lives = 5;
    // Game loop
    while (!WindowShouldClose())
    {
        if (GameActive == 1)
        {
            // Player Movement
            if (IsKeyDown(KEY_RIGHT))
            {
                PlayerX += PlayerSpeed;
            }
            if (IsKeyDown(KEY_LEFT))
            {
                PlayerX -= PlayerSpeed;
            }
            if (IsKeyDown(KEY_D))
            {
                PlayerX += PlayerSpeed;
            }
            if (IsKeyDown(KEY_A))
            {
                PlayerX -= PlayerSpeed;
            }
            // This is where everything gets drawn
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(Background, 0, 0, WHITE);
            DrawTexture(GrenadeTexture, OldGrenadeX[0], GrenadeY[0], WHITE);
            DrawTexture(PlayerSprite, PlayerX, PlayerY, WHITE);
            GrenadeX[0] = PlayerX + (GrenadeWidth + PlayerSpeed);
            GrenadeX[1] = PlayerX + (GrenadeWidth + PlayerSpeed);
            GrenadeX[2] = PlayerX + (GrenadeWidth + PlayerSpeed);
            if (DrawAsteroid == true)
            {
                DrawTexture(AsteroidSprite, AsteroidX[0], AsteroidY[0], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[1], AsteroidY[1], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[2], AsteroidY[2], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[3], AsteroidY[3], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[4], AsteroidY[4], WHITE);
            }
            // Asteroid Movement
            AsteroidY[0] += AsteroidSpeed[0];
            AsteroidY[1] += AsteroidSpeed[1];
            AsteroidY[2] += AsteroidSpeed[2];
            AsteroidY[3] += AsteroidSpeed[3];
            AsteroidY[4] += AsteroidSpeed[4];
            if (PlayerX <= 0)
            {
                PlayerX = 0;
            }
            if (PlayerX + PlayerWidth >= GetScreenWidth())
            {
                PlayerX = GetScreenWidth() - PlayerWidth;
            }
            // This trigers the grenade
            if (IsKeyDown(KEY_SPACE))
            {
                GrenadeActive = true;
                PlaySound(GrenadeShooting);
            }
            Collide_Grenade_Asteroid(AsteroidX[0], GrenadeX[0], AsteroidY[0], GrenadeY[0], AsteroidWidth, GrenadeWidth, AsteroidHeight, GrenadeHeight, AsteroidSpeed[0], GrenadeSpeed, GrenadeActive, ExplodeSound, Score);
            Collide_Grenade_Asteroid(AsteroidX[1], GrenadeX[0], AsteroidY[1], GrenadeY[0], AsteroidWidth, GrenadeWidth, AsteroidHeight, GrenadeHeight, AsteroidSpeed[1], GrenadeSpeed, GrenadeActive, ExplodeSound, Score);
            Collide_Grenade_Asteroid(AsteroidX[2], GrenadeX[0], AsteroidY[2], GrenadeY[0], AsteroidWidth, GrenadeWidth, AsteroidHeight, GrenadeHeight, AsteroidSpeed[2], GrenadeSpeed, GrenadeActive, ExplodeSound, Score);
            Collide_Grenade_Asteroid(AsteroidX[3], GrenadeX[0], AsteroidY[3], GrenadeY[0], AsteroidWidth, GrenadeWidth, AsteroidHeight, GrenadeHeight, AsteroidSpeed[3], GrenadeSpeed, GrenadeActive, ExplodeSound, Score);
            Collide_Grenade_Asteroid(AsteroidX[4], GrenadeX[0], AsteroidY[4], GrenadeY[0], AsteroidWidth, GrenadeWidth, AsteroidHeight, GrenadeHeight, AsteroidSpeed[4], GrenadeSpeed, GrenadeActive, ExplodeSound, Score);
            // Grenade Movement
            if (GrenadeActive)
            {
                if (GrenadeY[0] > 0)
                {
                    GrenadeY[0] -= GrenadeSpeed;
                    MeasuringOldX = false;
                }
                else
                {
                    GrenadeActive = false;
                }
            }
            if (MeasuringOldX)
            {
                OldGrenadeX[0] = GrenadeX[0];
            }
            if (!GrenadeActive)
            {
                GrenadeY[0] = PlayerY + (PlayerHeight / 2);
                MeasuringOldX = true;
            }
            if (MeasuringOldX)
            {
                OldGrenadeX[0] = GrenadeX[0];
            }
            // This is where the asteroids get reset
            if (AsteroidY[0] + AsteroidHeight >= GetScreenHeight())
            {
                DrawAsteroid = false;
                AsteroidY[0] = 0;
                AsteroidX[0] = GetRandomValue(0, GetScreenWidth() - AsteroidWidth);
                DrawAsteroid = true;
                Score -= 1;
            }
            if (AsteroidY[1] + AsteroidHeight >= GetScreenHeight())
            {
                DrawAsteroid = false;
                AsteroidY[1] = 0;
                AsteroidX[1] = GetRandomValue(0, GetScreenWidth() - AsteroidWidth);
                DrawAsteroid = true;
                Score -= 1;
            }
            if (AsteroidY[2] + AsteroidHeight >= GetScreenHeight())
            {
                DrawAsteroid = false;
                AsteroidY[2] = 0;
                AsteroidX[2] = GetRandomValue(0, GetScreenWidth() - AsteroidWidth);
                DrawAsteroid = true;
                Score -= 1;
            }
            if (AsteroidY[3] + AsteroidHeight >= GetScreenHeight())
            {
                DrawAsteroid = false;
                AsteroidY[3] = 0;
                AsteroidX[3] = GetRandomValue(0, GetScreenWidth() - AsteroidWidth);
                DrawAsteroid = true;
                Score -= 1;
            }
            if (AsteroidY[4] + AsteroidHeight >= GetScreenHeight())
            {
                DrawAsteroid = false;
                AsteroidY[4] = 0;
                AsteroidX[4] = GetRandomValue(0, GetScreenWidth() - AsteroidWidth);
                DrawAsteroid = true;
                Score -= 1;
            }
            Player_Hit_Asteroid(AsteroidX[0], PlayerX, AsteroidY[0], PlayerY, AsteroidWidth, PlayerWidth, AsteroidHeight, PlayerHeight, DrawAsteroid, Lives);
            Player_Hit_Asteroid(AsteroidX[1], PlayerX, AsteroidY[1], PlayerY, AsteroidWidth, PlayerWidth, AsteroidHeight, PlayerHeight, DrawAsteroid, Lives);
            Player_Hit_Asteroid(AsteroidX[2], PlayerX, AsteroidY[2], PlayerY, AsteroidWidth, PlayerWidth, AsteroidHeight, PlayerHeight, DrawAsteroid, Lives);
            Player_Hit_Asteroid(AsteroidX[3], PlayerX, AsteroidY[3], PlayerY, AsteroidWidth, PlayerWidth, AsteroidHeight, PlayerHeight, DrawAsteroid, Lives);
            Player_Hit_Asteroid(AsteroidX[4], PlayerX, AsteroidY[4], PlayerY, AsteroidWidth, PlayerWidth, AsteroidHeight, PlayerHeight, DrawAsteroid, Lives);
            // Draws the score
            DrawText(TextFormat("Score : %i", Score), 75, 50, 60, WHITE);
            DrawText(TextFormat("Lives : %i", Lives), 75, 110, 60, WHITE);
            if (Score == 0 || Lives == 0)
            {
                GameActive = 0;
            }
            if (Score == 100)
            {
                GameActive = 2;
            }
            EndDrawing();
        }
        if (GameActive == 0)
        {
            // You Died message
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You Died", GetScreenWidth() / 2 - MeasureText("You Died", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
            EndDrawing();
        }
        if (GameActive == 2)
        {
            // You Won message
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You Won", GetScreenWidth() / 2 - MeasureText("You Won", 60) / 2, GetScreenHeight() / 2 - 30, 60, WHITE);
            EndDrawing();
        }
    }
    // Every texture and sound gets unloaded here
    UnloadTexture(PlayerSprite);
    UnloadTexture(GrenadeTexture);
    UnloadTexture(AsteroidSprite);
    UnloadTexture(Background);
    UnloadSound(ExplodeSound);
    UnloadSound(GrenadeShooting);
    CloseAudioDevice();
    CloseWindow();
    // This returns 0 meaning the script was a success
    return 0;
}