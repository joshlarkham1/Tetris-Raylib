#include <raylib.h>
#include "game.h"
#include <iostream>

enum class GameState { StartMenu, Playing, GameOver };

int main()
{
    Color darkGrey = { 7, 7, 7, 255 };
    InitWindow(500, 660, "Tetris");
    SetTargetFPS(60);

    Font pixelFont = LoadFontEx("Font/PixelLetters.ttf", 64, 0, 0);
    Font NormalFont = LoadFontEx("Font/NormalLetters.ttf", 64, 0, 0);

    Game game = Game();
    GameState state = GameState::StartMenu;

    bool flashVisibleStart = true;
    bool flashVisibleGameOver = true;
    double lastFlashTimeStart = 0;
    double lastFlashTimeGameOver = 0;
    double lastGravityTime = 0;

    while (!WindowShouldClose())
    {
        double t = GetTime();
        BeginDrawing();
        ClearBackground(darkGrey);


        if (state == GameState::StartMenu)
        {
            DrawTextEx(pixelFont, "TETRIS", { 137, 247 }, 80, 2, grey);
            DrawTextEx(pixelFont, "TETRIS", { 140, 250 }, 80, 2, WHITE);

            if (t - lastFlashTimeStart >= 0.5)
            {
                flashVisibleStart = !flashVisibleStart;
                lastFlashTimeStart = t;
            }
            if (flashVisibleStart)
            {
                DrawTextEx(pixelFont, "PRESS ANY KEY TO START", { 124, 329 }, 20, 2, grey);
                DrawTextEx(pixelFont, "PRESS ANY KEY TO START", { 125, 330 }, 20, 2, WHITE);
            }

            if (GetKeyPressed() != 0)
            {
                state = GameState::Playing;
                game.Reset();
                flashVisibleStart = true;
                lastFlashTimeStart = t;
                lastGravityTime = t;
            }
        }
        else
        {
            if (state == GameState::Playing)
            {
                game.HandleInput();

                if (t - lastGravityTime >= 0.6)
                {
                    game.MoveBlockDown();
                    lastGravityTime = t;
                }
            }

            DrawTextEx(pixelFont, "SCORE", { 322, 12 }, 38, 2, grey);
            DrawTextEx(pixelFont, "SCORE", { 325, 15 }, 38, 2, WHITE);
            DrawTextEx(pixelFont, "NEXT", { 322, 172 }, 38, 2, grey);
            DrawTextEx(pixelFont, "NEXT", { 325, 175 }, 38, 2, WHITE);

            DrawRectangleRounded({ 320, 55, 170, 60 }, 0.2, 6, grey);

            char scoreText[10];
            sprintf_s(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(pixelFont, scoreText, 38, 2);

            DrawTextEx(pixelFont, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);

            DrawRectangleRounded({ 320, 215, 170, 180 }, 0.095, 6, grey);

            game.Draw();

            if (game.gameOver)
                state = GameState::GameOver;

            if (state == GameState::GameOver)
            {
                if (t - lastFlashTimeGameOver >= 0.5)
                {
                    flashVisibleGameOver = !flashVisibleGameOver;
                    lastFlashTimeGameOver = t;
                }

                if (flashVisibleGameOver)
                {
                    DrawTextEx(pixelFont, "GAME OVER!", { 67, 262 }, 70, 2, darkGrey);
                    DrawTextEx(pixelFont, "GAME OVER!", { 70, 265 }, 70, 2, WHITE);
                    DrawTextEx(pixelFont, "PRESS ANY KEY TO RESTART", { 139, 339 }, 15, 2, darkGrey);
                    DrawTextEx(pixelFont, "PRESS ANY KEY TO RESTART", { 140, 340 }, 15, 2, WHITE);
                }

                if (GetKeyPressed() != 0)
                {
                    state = GameState::Playing;
                    game.Reset();
                    lastGravityTime = GetTime();
                }
            }
            DrawRectangle(0, 0, 500, 10, darkGrey);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}