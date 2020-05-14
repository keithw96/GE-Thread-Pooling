#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MapTile.h"
#include "Player.h"
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

	Player* m_player = nullptr;

	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_event;
	bool m_running;

	MapTile* m_maptiles[30][30];
	std::vector<MapTile*> m_tiles;
};

