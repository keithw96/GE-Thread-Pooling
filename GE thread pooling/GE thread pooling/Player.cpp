#include "Player.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="renderer"></param>
Player::Player(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("Assets/Textures/player.bmp");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

/// <summary>
/// Deconstructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Set the players position to the passed vector
/// </summary>
/// <param name="pos"></param>
void Player::setPos(Vector2 pos)
{
	m_pos = pos;
	m_startingPos = pos;
	m_dstRect->x = pos.x; m_dstRect->y = pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
}

/// <summary>
/// Move the player one tile to the left
/// </summary>
void Player::moveLeft()
{
	m_pos.x -= 32;
}

/// <summary>
/// Move the player one tile to the right
/// </summary>
void Player::moveRight()
{
	m_pos.x += 32;
}

/// <summary>
/// Move the player one tile upwards
/// </summary>
void Player::moveUp()
{
	m_pos.y -= 32;
}

/// <summary>
/// Move the player one tile downwards
/// </summary>
void Player::moveDown()
{
	m_pos.y += 32;
}

/// <summary>
/// Set the render rectangle to the players position
/// </summary>
void Player::update()
{
	m_dstRect->x = m_pos.x; m_dstRect->y = m_pos.y;
}

/// <summary>
/// Render the player
/// </summary>
/// <param name="renderer"></param>
void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);
}

/// <summary>
/// Resets the player to its starting position
/// </summary>
void Player::reset()
{
	m_pos = m_startingPos;
}

/// <summary>
/// Return the players position
/// </summary>
/// <returns></returns>
Vector2 Player::getPos()
{
	return m_pos;
}
