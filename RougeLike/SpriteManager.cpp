#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"

SpriteManager::SpriteManager(SDL_Renderer* p_pxRenderer)
{
	m_pxRenderer = p_pxRenderer;
}

SpriteManager::~SpriteManager()
{
	//TODO: Clean everything from vector and map
	{
		// http://en.cppreference.com/w/cpp/language/auto
		// auto with templates uses deduction to create the specific iterator we need
		// In the below example auto will be replaced with std::vector<Sprite*>::iterator
		// std::vector<Sprite*>::iterator it = m_apxSprites.begin();

		auto it = m_apxSprites.begin(); //Iterator starts at the beginning of the std::vector
		while (it != m_apxSprites.end())  // While the iterator does not point beyond the end of the std::vector we loop
		{
			
			delete (*it); // Delete the object at the memory adress the pointer is pointing to
			it++; // Increment what memory adress the pointer is pointing on
		}
		// The std::vector is still full of pointers even thou we delete the objects the pointers pointed to
		// therefor we need to clear the vector
		m_apxSprites.clear(); 
	}
	{
		// std::map contains std::pair's and each pair has a key and value. First is key, second is value std::map<key, value>
		// Same procedure as with the Sprite* std::vector but instead of deleting the objevt we uses
		// SDL_DestroyTexture to destroy the value in the key/value pair the iterator is pointing on.
		
		auto it = m_apxTextures.begin();
		while (it != m_apxTextures.end())
		{
			SDL_DestroyTexture(it->second);
			it++;
		}
		m_apxTextures.clear();
	}
}

Sprite* SpriteManager::CreateSprite(const std::string& p_sFilepath,	int p_iX, int p_iY, int p_iW, int p_iH)
{
	// First we try to find the texture in our std::map
	auto it = m_apxTextures.find(p_sFilepath);
	if (it == m_apxTextures.end())
	{
		
		// If we do not find the texture we need to load it and inser it in to our std::map so
		// that we may create pointers to the same texture for several sprites.
		SDL_Surface* xSurface = SDL_LoadBMP(p_sFilepath.c_str());
		SDL_SetColorKey(xSurface, 1, SDL_MapRGB(xSurface->format, 0xFF, 0, 0xFF));
		SDL_Texture* xTexture = SDL_CreateTextureFromSurface(m_pxRenderer, xSurface);
		SDL_FreeSurface(xSurface);
		m_apxTextures.insert(std::pair<std::string,SDL_Texture*>(p_sFilepath, xTexture));
		it = m_apxTextures.find(p_sFilepath);
	}

	Sprite* xSprite = new Sprite(it->second,p_iX, p_iY, p_iW, p_iH);
	m_apxSprites.push_back(xSprite);
	return xSprite;
}

void SpriteManager::DestroySprite(Sprite* p_xSprite)
{
	auto it = m_apxSprites.begin();
	while (it != m_apxSprites.end())
	{
		if ((*it) == p_xSprite)
		{
			delete (*it);
			m_apxSprites.erase(it);
			return;
		}
		it++;
	}
}