#pragma once

class Sprite
{
public:
	Sprite(SDL_Texture* p_pxTexture);
	Sprite(SDL_Texture* p_pxTexture, int p_iX, int p_iY, int p_iW, int p_iH);
	~Sprite();
	SDL_Texture* GetTexture();
	SDL_Rect* GetRegion();
private:
	SDL_Texture* m_pxTexture;
	SDL_Rect m_xRegion;
};
