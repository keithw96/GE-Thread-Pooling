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

	m_player = new Player(m_renderer);

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
				m_maptiles[i][j] = new MapTile(m_renderer, "Assets/Textures/wall.bmp", Vector2(i * 32, j * 32), true);
				m_tiles.push_back(m_maptiles[i][j]);
			}
			if (mapArray[arrayIndex] == 4)
			{
				m_maptiles[i][j] = new MapTile(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32), false);
				m_tiles.push_back(m_maptiles[i][j]);
			}
			if (mapArray[arrayIndex] == 3)
			{
				m_maptiles[i][j] = new MapTile(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32), false);
				m_tiles.push_back(m_maptiles[i][j]);

				m_player->setPos(Vector2(i * 32, j * 32));
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
	case SDL_KEYDOWN:
		switch (m_event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			m_running = false;
			break;
		case SDLK_UP:
			if (!m_maptiles[(int)m_player->getPos().x / 32][((int)m_player->getPos().y / 32) - 1]->getIsObstacle())
			{
				m_player->moveUp();
			}
			break;
		case SDLK_DOWN:
			if (!m_maptiles[(int)m_player->getPos().x / 32][((int)m_player->getPos().y / 32) + 1]->getIsObstacle())
			{
				m_player->moveDown();
			}
			break;
		case SDLK_LEFT:
			if (!m_maptiles[((int)m_player->getPos().x / 32) - 1][(int)m_player->getPos().y / 32]->getIsObstacle())
			{
				m_player->moveLeft();
			}
			break;
		case SDLK_RIGHT:
			if (!m_maptiles[((int)m_player->getPos().x / 32) + 1][(int)m_player->getPos().y / 32]->getIsObstacle())
			{
				m_player->moveRight();
			}
			break;
		default:
			break;
		}
		SDL_Delay(100);

		break;
	default:
		break;
	}
}

void Game::update()
{
	m_player->update();
}

void Game::render()
{
	SDL_RenderClear(m_renderer);

	for (auto t : m_tiles)
	{
		t->render(m_renderer);
	}

	m_player->render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}
