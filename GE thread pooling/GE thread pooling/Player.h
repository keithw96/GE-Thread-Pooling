#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Vector2.h"
#include "MapTile.h"
class Player
{
public:

	Player(SDL_Renderer* renderer);
	~Player();

	void setPos(Vector2 pos);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void update();
	void render(SDL_Renderer* renderer);
	void reset();
	Vector2 getPos();
private:

	Vector2 m_pos;
	Vector2 m_startingPos;
	SDL_Texture* m_texture;
	SDL_Rect* m_dstRect = new SDL_Rect;
};

