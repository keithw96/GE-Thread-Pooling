#include "MapTile.h"

MapTile::MapTile()
{
}

MapTile::~MapTile()
{
}

void MapTile::init(SDL_Renderer* renderer, const char* path, Vector2 pos, bool isObstacle)
{
	SDL_Surface* surface = SDL_LoadBMP(path);

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_pos = pos;
	m_dstRect->x = pos.x; m_dstRect->y = pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
	m_isObstacle = isObstacle;
	m_center = Vector2(pos.x + 16, pos.y + 16);
	m_cost = 0;
	m_isObstacle = isObstacle;
}

void MapTile::render(SDL_Renderer*& renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);

	if (!m_isObstacle && m_end.x != 0)
	{
		SDL_RenderDrawLine(renderer, m_center.x, m_center.y, m_end.x, m_end.y);
	}

}

void MapTile::addAdjacent(MapTile& mapTile)
{
	m_adjacents.push_back(&mapTile);
}

void MapTile::setPrevious(MapTile& mapTile)
{
	m_previous = &mapTile;
}

void MapTile::setCost(int cost)
{
	m_cost = cost;
}

void MapTile::setStart(bool start)
{
	m_start = start;
}

void MapTile::setGoal(bool goal)
{
	m_goal = goal;
}

void MapTile::setPath(bool path)
{
	m_path = path;
}

void MapTile::setVisited(bool visited)
{
	m_visited = visited;
}

void MapTile::setEnd(Vector2 end)
{
	m_end = end;
}

bool MapTile::getIsObstacle()
{
	return m_isObstacle;
}

bool MapTile::getStart()
{
	return m_start;
}

bool MapTile::getGoal()
{
	return m_goal;
}

bool MapTile::getPath()
{
	return m_path;
}

bool MapTile::getVisited()
{
	return m_visited;
}

Vector2 MapTile::getEnd()
{
	return m_end;
}

Vector2 MapTile::getCenter()
{
	return m_center;
}

Vector2 MapTile::getPosition()
{
	return m_pos;
}

int MapTile::getCost()
{
	return m_cost;
}

std::list<MapTile*>& MapTile::getAdjacents()
{
	return m_adjacents;
}

MapTile* MapTile::getPrevious()
{
	return m_previous;
}
