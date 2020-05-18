#include "Game.h"

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	int time = SDL_GetTicks();

	Uint32 frameStart;
	int frameTime;

	Game game;

	game.init();

	while (game.isRunning())
	{
		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game.clean();

	return 0;
}