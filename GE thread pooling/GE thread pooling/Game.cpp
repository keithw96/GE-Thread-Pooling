#include "Game.h"

/// <summary>
/// Constructor
/// </summary>
Game::Game()
{
}

/// <summary>
/// Deconstructor
/// </summary>
Game::~Game()
{
}

/// <summary>
/// Initialise the game
/// Read in the map and set each maptile's adjacents 
/// </summary>
void Game::init()
{
	m_running = true;

	m_window = SDL_CreateWindow("", 0, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

	m_player = new Player(m_renderer);
	m_enemyMovementTimer = 20;
	m_keyInputTimer = 5;

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
				m_maptiles[i][j].init(m_renderer, "Assets/Textures/wall.bmp", Vector2(i * 32, j * 32), true);
				m_tiles.push_back(&m_maptiles[i][j]);
				
			}
			if (mapArray[arrayIndex] == 4)
			{
				m_maptiles[i][j].init(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32), false);
				m_tiles.push_back(&m_maptiles[i][j]);
			}
			if (mapArray[arrayIndex] == 3)
			{
				m_maptiles[i][j].init(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32), false);
				m_tiles.push_back(&m_maptiles[i][j]);

				m_player->setPos(Vector2(i * 32, j * 32));
			}
			if (mapArray[arrayIndex] == 1)
			{
				m_maptiles[i][j].init(m_renderer, "Assets/Textures/emptyTile.bmp", Vector2(i * 32, j * 32), false);
				m_tiles.push_back(&m_maptiles[i][j]);

				Enemy* enemy = new Enemy(m_renderer, Vector2(i * 32, j * 32));
				m_enemies.push_back(enemy);
			}
			arrayIndex++;
		}
	}
	setAdjacents();
	threadPool = new ThreadPool();
}

/// <summary>
/// Event manager
/// </summary>
void Game::handleEvents()
{
	SDL_PollEvent(&m_event);

	if (m_keyInputTimer > 5)
	{
		switch (m_event.type)
		{
		case SDL_KEYDOWN:
			switch (m_event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_running = false;
				break;
			case SDLK_UP:
				if (!m_maptiles[(int)m_player->getPos().x / 32][((int)m_player->getPos().y / 32) - 1].getIsObstacle())
				{
					m_player->moveUp();
				}
				break;
			case SDLK_DOWN:
				if (!m_maptiles[(int)m_player->getPos().x / 32][((int)m_player->getPos().y / 32) + 1].getIsObstacle())
				{
					m_player->moveDown();
				}
				break;
			case SDLK_LEFT:
				if (!m_maptiles[((int)m_player->getPos().x / 32) - 1][(int)m_player->getPos().y / 32].getIsObstacle())
				{
					m_player->moveLeft();
				}
				break;
			case SDLK_RIGHT:
				if (!m_maptiles[((int)m_player->getPos().x / 32) + 1][(int)m_player->getPos().y / 32].getIsObstacle())
				{
					m_player->moveRight();
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		m_keyInputTimer = 0;
	}
	m_keyInputTimer++;
}

/// <summary>
/// Update game elements
/// </summary>
void Game::update()
{
	m_player->update();
	
	setFlowField();

	enemyMovement();

}

/// <summary>
/// Render game elements
/// </summary>
void Game::render()
{
	SDL_RenderClear(m_renderer);

	for (auto t : m_tiles)
	{
		t->render(m_renderer);
	}
	for (auto e : m_enemies)
	{
		e->render(m_renderer);
	}

	m_player->render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

/// <summary>
/// Destroy the window and renderer and clean subsystems
/// </summary>
void Game::clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

/// <summary>
/// For each tile in the map, add its neighbours to a vector of mapTiles 
/// </summary>
void Game::setAdjacents()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (i > 0)
			{
				m_maptiles[i][j].addAdjacent(m_maptiles[i - 1][j]);
			}

			if (i + 1 < 30)
			{
				m_maptiles[i][j].addAdjacent(m_maptiles[i + 1][j]);
			}

			if (j > 0)
			{
				m_maptiles[i][j].addAdjacent(m_maptiles[i][j - 1]);
			}

			if (j < 30)
			{
				m_maptiles[i][j].addAdjacent(m_maptiles[i][j + 1]);
			}
		}
	}
}

/// <summary>
/// Creates a flow field using the players position as a goal.
/// </summary>
void Game::setFlowField()
{
	MapTile* goal = &m_maptiles[(int)m_player->getPos().x / 32][(int)m_player->getPos().y / 32];
	
	std::list<MapTile*> queue;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			m_maptiles[i][j].setVisited(false);
		}
	}

	goal->setVisited(true);
	queue.push_back(goal);

	while (!queue.empty())
	{
		for (auto& a : queue.front()->getAdjacents())
		{
			if (!a->getVisited())
			{
				a->setVisited(true);
				if (!a->getIsObstacle())
				{
					a->setPrevious(*queue.front());
					queue.push_back(a);
				}
			}
		}
		queue.pop_front();
	}

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (m_maptiles[i][j].getPrevious() && m_maptiles[i][j].getIsObstacle() == false)
			{
				Vector2 vec = Vector2(((m_maptiles[i][j].getPrevious()->getCenter() - m_maptiles[i][j].getCenter()) / 3) + m_maptiles[i][j].getCenter());
				m_maptiles[i][j].setEnd(vec);
			}
		}
	}

}

/// <summary>
/// Sets the enemy's position to the current tile's destination tile.
/// Has a cooldown of 10 frames to slow the movement down
/// </summary>
void Game::enemyMovement()
{
	m_enemyMovementTimer++;

	if (m_enemyMovementTimer > 10)
	{
		for (auto e : m_enemies)
		{
			MapTile* tile = m_maptiles[(int)e->getPos().x / 32][(int)e->getPos().y / 32].getPrevious();
			Vector2 destPos;
			if (tile != NULL)
			{
				destPos = tile->getPosition();
			}
			else
			{
				destPos = m_maptiles[(int)e->getPos().x / 32][(int)e->getPos().y / 32].getPosition();
			}
			e->setDestinationPos(destPos);
			
			threadPool->addTask(std::bind(&Enemy::update, e));

			if (e->getPos() == m_player->getPos())
			{
				for (auto e : m_enemies)
				{
					threadPool->addTask(std::bind(&Enemy::reset, e));
					
				}
				m_player->reset();
			}

		}
		m_enemyMovementTimer = 0;
	}
}

