#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer,Vector2 pos)
{
	SDL_Surface* surface = SDL_LoadBMP("Assets/Textures/enemy.bmp");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_pos = pos;
}

Enemy::~Enemy()
{
}

void Enemy::update(Vector2 newPos)
{
	m_pos = newPos;

	m_dstRect->x = m_pos.x; m_dstRect->y = m_pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
}

void Enemy::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);
}

Vector2 Enemy::getPos()
{
	return m_pos;
}
