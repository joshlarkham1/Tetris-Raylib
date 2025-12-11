#include <raylib.h>
#include "game.h"


double lastUpdateTime = 0;

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

int main()
{
	Color darkGrey = { 7, 7, 7, 255 };
	InitWindow(300, 600, "Tetris");
	SetTargetFPS(60);

	Game game = Game();

	while (WindowShouldClose() == false)
	{
		game.HandleInput();
		if(EventTriggered(0.2))
		{
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkGrey);
		game.Draw();
		EndDrawing();
	}
	
	CloseWindow();

	return 0;
};
