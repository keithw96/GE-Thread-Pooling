#pragma once
#include "Vector2.h"
#include "SDL.h"
#include <iostream>
class MapTile
{
public:

	MapTile(SDL_Renderer* renderer, const char* path, Vector2 pos);
	~MapTile();

	void setPos(Vector2 vec);
	void setCost(int cost);

	void render(SDL_Renderer*& renderer);



private:
	Vector2 m_pos;
	SDL_Texture* m_texture;
	SDL_Rect* m_dstRect = new SDL_Rect;
};

