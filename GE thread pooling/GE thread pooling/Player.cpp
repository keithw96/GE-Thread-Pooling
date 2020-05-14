#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("Assets/Textures/player.bmp");
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Player::~Player()
{
}

void Player::pollEvent(SDL_Event e, MapTile* maptile)
{

	//std::cout << "poll event" << std::endl;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				std::cout << "W key pressed" << std::endl;
				m_pos.y -= 32;
				break;
			case SDLK_DOWN:
				m_pos.y += 32;
				break;
			case SDLK_LEFT:
				m_pos.x -= 32;
				break;
			case SDLK_RIGHT:
				m_pos.x += 32;
				break;
			default:
				break;
			}
			break;
		}
	}
}

void Player::setPos(Vector2 pos)
{
	m_pos = pos;
	m_dstRect->x = pos.x; m_dstRect->y = pos.y; m_dstRect->w = 32; m_dstRect->h = 32;
}

void Player::moveLeft()
{
	m_pos.x -= 32;
}

void Player::moveRight()
{
	m_pos.x += 32;
}

void Player::moveUp()
{
	m_pos.y -= 32;
}

void Player::moveDown()
{
	m_pos.y += 32;
}

void Player::update()
{
	m_dstRect->x = m_pos.x; m_dstRect->y = m_pos.y;
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, m_dstRect);
}

Vector2 Player::getPos()
{
	return m_pos;
}
