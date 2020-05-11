#include "MapTile.h"

MapTile::MapTile(SDL_Renderer* renderer, const char* path, Vector2 pos)
{
	SDL_Surface* surface = SDL_LoadBMP(path);

	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_dstRect->x = pos.x; m_dstRect->y = pos.y, m_dstRect->w = 32; m_dstRect->h = 32;
}

MapTile::~MapTile()
{
}

void MapTile::setPos(Vector2 vec)
{
}

void MapTile::setCost(int cost)
{
}

void MapTile::render(SDL_Renderer*& renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);
}
