#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "MapTile.h"
class Enemy
{
public:

	Enemy(SDL_Renderer* renderer, Vector2 pos);
	~Enemy();

	void setDestinationPos(Vector2 vec);
	void update();
	void render(SDL_Renderer* renderer);
	void reset();

	Vector2 getPos();

private:

	Vector2 m_pos;
	Vector2 m_startingPos;
	Vector2 m_destinationPos;
	SDL_Texture* m_texture;
	SDL_Rect* m_dstRect = new SDL_Rect;
};

