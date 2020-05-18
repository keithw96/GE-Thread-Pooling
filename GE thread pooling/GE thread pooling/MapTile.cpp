#include "MapTile.h"

/// <summary>
/// Constructor
/// </summary>
MapTile::MapTile()
{
}

/// <summary>
/// Deconstructor
/// </summary>
MapTile::~MapTile()
{
}

/// <summary>
/// Init tile variables
/// </summary>
/// <param name="renderer"></param>
/// <param name="path"></param>
/// <param name="pos"></param>
/// <param name="isObstacle"></param>
void MapTile::init(SDL_Renderer* renderer, const char* path, Vector2 pos, bool isObstacle)
{
	SDL_Surface* surface = SDL_LoadBMP(path);

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_pos = pos;
	m_dstRect->x = pos.x; m_dstRect->y = pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
	m_isObstacle = isObstacle;
	m_center = Vector2(pos.x + 16, pos.y + 16);
	m_isObstacle = isObstacle;
}

/// <summary>
/// Render the tile
/// </summary>
/// <param name="renderer"></param>
void MapTile::render(SDL_Renderer*& renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);

	if (!m_isObstacle && m_end.x != 0)
	{
		SDL_RenderDrawLine(renderer, m_center.x, m_center.y, m_end.x, m_end.y);
	}

}

/// <summary>
/// Add passed neighbouring tile to vector
/// </summary>
/// <param name="mapTile"></param>
void MapTile::addAdjacent(MapTile& mapTile)
{
	m_adjacents.push_back(&mapTile);
}

/// <summary>
/// Store the destination tile 
/// </summary>
/// <param name="mapTile"></param>
void MapTile::setPrevious(MapTile& mapTile)
{
	m_previous = &mapTile;
}

/// <summary>
/// Sets the tile to visited when the algorithm checks the tile
/// </summary>
/// <param name="visited"></param>
void MapTile::setVisited(bool visited)
{
	m_visited = visited;
}

/// <summary>
/// Sets is obstacle to the passed bool
/// used to set the current tile the enemy is on to a wall so enemies path around it
/// </summary>
/// <param name="isObstacle"></param>
void MapTile::setIsObstacle(bool isObstacle)
{
	m_isObstacle = isObstacle;
}

/// <summary>
/// sets the end point of the vector
/// </summary>
/// <param name="end"></param>
void MapTile::setEnd(Vector2 end)
{
	m_end = end;
}

/// <summary>
/// Returns isObstacle
/// Used to check if tile is a wall to exclude it from the algorithm
/// </summary>
/// <returns></returns>
bool MapTile::getIsObstacle()
{
	return m_isObstacle;
}

/// <summary>
/// Returns m_visited
/// Used to check if the algorithm has checked the tile
/// </summary>
/// <returns></returns>
bool MapTile::getVisited()
{
	return m_visited;
}

/// <summary>
/// Returns the end point of the vector
/// </summary>
/// <returns></returns>
Vector2 MapTile::getEnd()
{
	return m_end;
}

/// <summary>
/// Returns the tiles center
/// </summary>
/// <returns></returns>
Vector2 MapTile::getCenter()
{
	return m_center;
}

/// <summary>
/// Returns the tiles position
/// </summary>
/// <returns></returns>
Vector2 MapTile::getPosition()
{
	return m_pos;
}

/// <summary>
/// Returns the list of the tiles neighbour tiles
/// </summary>
/// <returns></returns>
std::list<MapTile*>& MapTile::getAdjacents()
{
	return m_adjacents;
}

/// <summary>
/// Returns the destination tile
/// </summary>
/// <returns></returns>
MapTile* MapTile::getPrevious()
{
	return m_previous;
}
