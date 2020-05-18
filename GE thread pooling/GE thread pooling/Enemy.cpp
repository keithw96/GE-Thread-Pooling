#include "Enemy.h"

/// <summary>
/// Cosntructor
/// </summary>
/// <param name="renderer"></param>
/// <param name="pos"></param>
Enemy::Enemy(SDL_Renderer* renderer,Vector2 pos)
{
	SDL_Surface* surface = SDL_LoadBMP("Assets/Textures/enemy.bmp");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_pos = pos;
	m_startingPos = pos;
}

/// <summary>
/// Deconstructor
/// </summary>
Enemy::~Enemy()
{
}

void Enemy::setDestinationPos(Vector2 vec)
{
	m_destinationPos = vec;
}

/// <summary>
/// Update the enemy's movement and rendering rectangle
/// </summary>
/// <param name="newPos"></param>
void Enemy::update()
{
	m_pos = m_destinationPos;

	m_dstRect->x = m_pos.x; m_dstRect->y = m_pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
}

/// <summary>
/// Render the enemy
/// </summary>
/// <param name="renderer"></param>
void Enemy::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);
}

/// <summary>
/// Sets the enemys position to it's position that it was created at
/// </summary>
void Enemy::reset()
{
	m_pos = m_startingPos;
}

/// <summary>
/// Returns the enemy's position
/// </summary>
/// <returns></returns>
Vector2 Enemy::getPos()
{
	return m_pos;
}
