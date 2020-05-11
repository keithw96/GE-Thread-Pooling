#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MapTile.h"
class Game
{
public:

	Game();
	~Game();

	void init();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool isRunning() { return m_running; }
private:

	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_event;
	bool m_running;

	std::vector<MapTile*> m_tiles;
};

