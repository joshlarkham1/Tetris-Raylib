#include <raylib.h>
#include "game.h"
#include <iostream>

double lastUpdateTime = 0;
double lastFlashTime = 0;


bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if(currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

bool FlashEvent(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastFlashTime >= interval)
	{
		lastFlashTime = currentTime;
		return true;
	}
	return false;
}


int main()
{
	Color darkGrey = { 7, 7, 7, 255 };
	InitWindow(500, 660, "Tetris");
	SetTargetFPS(60);

	Font pixelFont = LoadFontEx("Font/PixelLetters.ttf", 64, 0, 0);
	Font NormalFont = LoadFontEx("Font/NormalLetters.ttf", 64, 0, 0);


	Game game = Game();

	while (WindowShouldClose() == false)
	{
		game.HandleInput();
		if(EventTriggered(0.6))
		{
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkGrey);
		DrawTextEx(pixelFont, "SCORE", { 322, 12 }, 38, 2, grey);
		DrawTextEx(pixelFont, "SCORE", { 325, 15 }, 38, 2, WHITE);
		DrawTextEx(pixelFont, "NEXT", { 322, 172 }, 38, 2, grey);
		DrawTextEx(pixelFont, "NEXT", { 325, 175 }, 38, 2, WHITE);
		
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.2, 6, grey);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(pixelFont, scoreText, 38, 2);

		DrawTextEx(pixelFont, scoreText, { 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.095, 6, grey);

		game.Draw();
		static bool flashVisible = true;

		if (game.gameOver)
		{
			if (FlashEvent(0.5))
			{
				flashVisible = !flashVisible;
			}
			if (flashVisible)
			{
				DrawTextEx(pixelFont, "GAME OVER!", { 67, 262 }, 70, 2, darkGrey);
				DrawTextEx(pixelFont, "GAME OVER!", { 70, 265 }, 70, 2, WHITE);
				DrawTextEx(pixelFont, "PRESS ANY KEY TO RESTART", { 139, 339 }, 15, 2, darkGrey);
				DrawTextEx(pixelFont, "PRESS ANY KEY TO RESTART", { 140, 340 }, 15, 2, WHITE);
			}
		}
		EndDrawing();
	}
	
	CloseWindow();

	return 0;
};
