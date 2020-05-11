#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;

	game.init();

	while (game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return 0;
}