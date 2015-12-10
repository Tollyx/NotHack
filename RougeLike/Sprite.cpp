#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Texture* p_pxTexture)
{
	m_pxTexture = p_pxTexture;
	m_xRegion.x = 0;
	m_xRegion.y = 0;
	m_xRegion.w = 0;
	m_xRegion.h = 0;
};

Sprite::Sprite(SDL_Texture* p_pxTexture, int p_iX, int p_iY, int p_iW, int p_iH)
{
	m_pxTexture = p_pxTexture;
	m_xRegion.x = p_iX;
	m_xRegion.y = p_iY;
	m_xRegion.w = p_iW;
	m_xRegion.h = p_iH;
}

Sprite::~Sprite()
{
};

SDL_Texture* Sprite::GetTexture()
{
	return m_pxTexture;
};

SDL_Rect* Sprite::GetRegion()
{
	return &m_xRegion;
};