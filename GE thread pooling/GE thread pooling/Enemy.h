#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "MapTile.h"
class Enemy
{
public:

	Enemy(SDL_Renderer* renderer, Vector2 pos);
	~Enemy();

	void update(Vector2 newPos);
	void render(SDL_Renderer* renderer);

	Vector2 getPos();

private:

	Vector2 m_pos;
	SDL_Texture* m_texture;
	SDL_Rect* m_dstRect = new SDL_Rect;
};

