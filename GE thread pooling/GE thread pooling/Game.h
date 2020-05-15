#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "MapTile.h"
#include "Player.h"
#include "Enemy.h"
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
	void setAdjacents();
	void setFlowField();
	void enemyMovement();
	bool isRunning() { return m_running; }

	MapTile m_maptiles[30][30];

private:

	Player* m_player = nullptr;
	int m_enemyMovementTimer, m_keyInputTimer;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_event;
	bool m_running;

	std::vector<MapTile*> m_tiles;
	std::vector<Enemy*> m_enemies;
};

