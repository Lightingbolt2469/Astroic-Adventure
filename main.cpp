#include "raylib.h"

// Checks if the Asteroid touches the EnergyBlast
void Collide_EnergyBlast_Asteroid(int &a_x, int &b_x, int &a_y, int &b_y, int a_width, int b_width, int a_height, int b_height, int &a_speed, int &b_speed, bool &b_active, Sound ExplodeSound, int &Score)
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

void Heart_Hit_Player(int &a_x, int &b_x, int &a_y, int &b_y, int a_width, int b_width, int a_height, int b_height, int &a_speed, bool &a_active, int &a_wd, int &Lives, int &Score)
{
    if (a_x < b_x + b_width && b_x < a_x + a_width && a_y < b_y + b_height && b_y < a_y + a_height)
    {
        Lives += 1;
        a_y = 0;
        a_x = GetRandomValue(0, GetScreenWidth() - a_width);
        a_speed = GetRandomValue(2, 4);
        a_wd = Score + GetRandomValue(2, 96);
        a_active = false;
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
    int EnergyBlastWidth = 30;
    int EnergyBlastHeight = 30;
    int EnergyBlastX[3] = {PlayerX + (EnergyBlastWidth + PlayerSpeed), PlayerX + (EnergyBlastWidth + PlayerSpeed), PlayerX + (EnergyBlastWidth + PlayerSpeed)};
    int EnergyBlastY[3] = {PlayerY + (PlayerHeight / 2), PlayerY + (PlayerHeight / 2), PlayerY + (PlayerHeight / 2)};
    int OldEnergyBlastX[3];
    int EnergyBlastSpeed = 12;
    bool EnergyBlastActive = false;
    bool EnergyBlastActive1 = false;
    bool EnergyBlastActive2 = false;
    bool MeasuringOldX = true;
    bool MeasuringOldX1 = true;
    bool MeasuringOldX2 = true;
    int HeartWidth = 150;
    int HeartHeight = 150;
    int HeartX = GetRandomValue(0, GetScreenWidth() - HeartWidth);
    int HeartY = 0;
    int HeartSpeed = GetRandomValue(2, 4);
    bool DrawHeart = false;
    int Score = 1;
    int Lives = 5;
    int WhenDrawHeart = Score + GetRandomValue(5, 20);
    Texture2D PlayerSprite = LoadTexture("Sprites/Player.png");
    Texture2D EnergyBlastTexture = LoadTexture("Sprites/EnergyBlast.png");
    Texture2D AsteroidSprite = LoadTexture("Sprites/Asteroid.png");
    Texture2D HeartSprite = LoadTexture("Sprites/Heart.png");
    Texture2D Background = LoadTexture("Sprites/Background.png");
    Sound ExplodeSound = LoadSound("Sounds/Explosion.wav");
    Sound EnergyBlastShooting = LoadSound("Sounds/EnergyBlastShooting.wav");
    Music BackgroundMusic = LoadMusicStream("Sounds/Background Music.ogg");
    // Game loop
    PlayMusicStream(BackgroundMusic);
    while (!WindowShouldClose())
    {
        if (GameActive == 1)
        {
            UpdateMusicStream(BackgroundMusic);
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
            DrawTexture(EnergyBlastTexture, OldEnergyBlastX[0], EnergyBlastY[0], WHITE);
            DrawTexture(EnergyBlastTexture, OldEnergyBlastX[1], EnergyBlastY[1], WHITE);
            DrawTexture(EnergyBlastTexture, OldEnergyBlastX[2], EnergyBlastY[2], WHITE);
            DrawTexture(PlayerSprite, PlayerX, PlayerY, WHITE);
            EnergyBlastX[0] = PlayerX + (EnergyBlastWidth + PlayerSpeed);
            EnergyBlastX[1] = PlayerX + (EnergyBlastWidth + PlayerSpeed);
            EnergyBlastX[2] = PlayerX + (EnergyBlastWidth + PlayerSpeed);
            if (DrawAsteroid == true)
            {
                DrawTexture(AsteroidSprite, AsteroidX[0], AsteroidY[0], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[1], AsteroidY[1], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[2], AsteroidY[2], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[3], AsteroidY[3], WHITE);
                DrawTexture(AsteroidSprite, AsteroidX[4], AsteroidY[4], WHITE);
            }
            if (WhenDrawHeart == Score)
            {
                DrawHeart = true;
            }
            if (DrawHeart == true)
            {
                DrawTexture(HeartSprite, HeartX, HeartY, WHITE);
                if (HeartY >= 0)
                {
                    HeartY += HeartSpeed;
                }
                if (HeartY >= GetScreenHeight())
                {
                    DrawHeart = false;
                    HeartY = 0;
                    HeartX = GetRandomValue(0, GetScreenWidth() - HeartWidth);
                    WhenDrawHeart = Score + GetRandomValue(2, 96);
                }
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
            // This trigers the EnergyBlast
            if (IsKeyDown(KEY_SPACE))
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    if (!EnergyBlastActive)
                    {
                        EnergyBlastActive = true;
                    }
                    else if (!EnergyBlastActive1)
                    {
                        EnergyBlastActive1 = true;
                    }
                    else if (!EnergyBlastActive2)
                    {
                        EnergyBlastActive2 = true;
                    }
                }
                PlaySound(EnergyBlastShooting);
            }
            Collide_EnergyBlast_Asteroid(AsteroidX[0], EnergyBlastX[0], AsteroidY[0], EnergyBlastY[0], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[0], EnergyBlastSpeed, EnergyBlastActive, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[1], EnergyBlastX[0], AsteroidY[1], EnergyBlastY[0], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[1], EnergyBlastSpeed, EnergyBlastActive, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[2], EnergyBlastX[0], AsteroidY[2], EnergyBlastY[0], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[2], EnergyBlastSpeed, EnergyBlastActive, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[3], EnergyBlastX[0], AsteroidY[3], EnergyBlastY[0], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[3], EnergyBlastSpeed, EnergyBlastActive, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[4], EnergyBlastX[0], AsteroidY[4], EnergyBlastY[0], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[4], EnergyBlastSpeed, EnergyBlastActive, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[0], EnergyBlastX[1], AsteroidY[0], EnergyBlastY[1], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[0], EnergyBlastSpeed, EnergyBlastActive1, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[1], EnergyBlastX[1], AsteroidY[1], EnergyBlastY[1], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[1], EnergyBlastSpeed, EnergyBlastActive1, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[2], EnergyBlastX[1], AsteroidY[2], EnergyBlastY[1], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[2], EnergyBlastSpeed, EnergyBlastActive1, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[3], EnergyBlastX[1], AsteroidY[3], EnergyBlastY[1], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[3], EnergyBlastSpeed, EnergyBlastActive1, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[4], EnergyBlastX[1], AsteroidY[4], EnergyBlastY[1], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[4], EnergyBlastSpeed, EnergyBlastActive1, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[0], EnergyBlastX[2], AsteroidY[0], EnergyBlastY[2], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[0], EnergyBlastSpeed, EnergyBlastActive2, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[1], EnergyBlastX[2], AsteroidY[1], EnergyBlastY[2], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[1], EnergyBlastSpeed, EnergyBlastActive2, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[2], EnergyBlastX[2], AsteroidY[2], EnergyBlastY[2], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[2], EnergyBlastSpeed, EnergyBlastActive2, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[3], EnergyBlastX[2], AsteroidY[3], EnergyBlastY[2], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[3], EnergyBlastSpeed, EnergyBlastActive2, ExplodeSound, Score);
            Collide_EnergyBlast_Asteroid(AsteroidX[4], EnergyBlastX[2], AsteroidY[4], EnergyBlastY[2], AsteroidWidth, EnergyBlastWidth, AsteroidHeight, EnergyBlastHeight, AsteroidSpeed[4], EnergyBlastSpeed, EnergyBlastActive2, ExplodeSound, Score);
            Heart_Hit_Player(HeartX, PlayerX, HeartY, PlayerY, HeartWidth, PlayerWidth, HeartHeight, PlayerHeight, HeartSpeed, DrawHeart, WhenDrawHeart, Lives, Score);
            // EnergyBlast Movement
            if (EnergyBlastActive)
            {
                if (EnergyBlastY[0] > 0)
                {
                    EnergyBlastY[0] -= EnergyBlastSpeed;
                    MeasuringOldX = false;
                }
                else
                {
                    EnergyBlastActive = false;
                }
            }
            if (MeasuringOldX)
            {
                OldEnergyBlastX[0] = EnergyBlastX[0];
            }
            if (!EnergyBlastActive)
            {
                EnergyBlastY[0] = PlayerY + (PlayerHeight / 2);
                MeasuringOldX = true;
            }
            if (MeasuringOldX)
            {
                OldEnergyBlastX[0] = EnergyBlastX[0];
            }
            // ############################################################
            if (EnergyBlastActive1)
            {
                if (EnergyBlastY[1] > 0)
                {
                    EnergyBlastY[1] -= EnergyBlastSpeed;
                    MeasuringOldX1 = false;
                }
                else
                {
                    EnergyBlastActive1 = false;
                }
            }
            if (MeasuringOldX1)
            {
                OldEnergyBlastX[1] = EnergyBlastX[1];
            }
            if (!EnergyBlastActive1)
            {
                EnergyBlastY[1] = PlayerY + (PlayerHeight / 2);
                MeasuringOldX1 = true;
            }
            if (MeasuringOldX1)
            {
                OldEnergyBlastX[1] = EnergyBlastX[1];
            }
            // #################################################
            if (EnergyBlastActive2)
            {
                if (EnergyBlastY[2] > 0)
                {
                    EnergyBlastY[2] -= EnergyBlastSpeed;
                    MeasuringOldX2 = false;
                }
                else
                {
                    EnergyBlastActive2 = false;
                }
            }
            if (MeasuringOldX2)
            {
                OldEnergyBlastX[2] = EnergyBlastX[2];
            }
            if (!EnergyBlastActive2)
            {
                EnergyBlastY[2] = PlayerY + (PlayerHeight / 2);
                MeasuringOldX2 = true;
            }
            if (MeasuringOldX2)
            {
                OldEnergyBlastX[2] = EnergyBlastX[2];
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
            DrawText(TextFormat("Lives : %i", Lives), 40, 120, 60, WHITE);
            DrawText(TextFormat("Score : %i", Score), 40, 40, 60, WHITE);
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
    UnloadTexture(EnergyBlastTexture);
    UnloadTexture(AsteroidSprite);
    UnloadTexture(Background);
    UnloadSound(ExplodeSound);
    UnloadSound(EnergyBlastShooting);
    CloseAudioDevice();
    CloseWindow();
    // This returns 0 meaning the script was a success
    return 0;
}