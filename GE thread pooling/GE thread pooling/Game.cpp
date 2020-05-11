#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	m_running = true;

	m_window = SDL_CreateWindow("", 0, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	std::string line;
	std::ifstream myFile("Assets/Maps/Map1.txt");
	std::vector<int> mapArray;

	if (myFile.is_open())
	{
		while (std::getline(myFile, line, ','))
		{
			mapArray.push_back(std::stoi(line));
		}
		myFile.close();
	}
	int arrayIndex = 0;
	for (int j = 0; j < 30; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			if (mapArray[arrayIndex] == 2)
			{
				MapTile* mapTile = new MapTile(m_renderer, "Assets/Textures/wall.bmp", Vector2(i * 32, j * 32));
				m_tiles.push_back(mapTile);
			}
			else if (mapArray[arrayIndex] == 4)
			{
				MapTile* nmapTile = new MapTile(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32));
				m_tiles.push_back(nmapTile);
			}
			arrayIndex++;
		}
	}
	
}

void Game::handleEvents()
{
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	default:
		break;
	}
}

void Game::update()
{
	//std::cout << "game loop" << std::endl;
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	for (auto t : m_tiles)
	{
		t->render(m_renderer);
	}
	SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}
