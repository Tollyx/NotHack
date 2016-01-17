#include "stdafx.h"
#include "TileManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "TileMap.h"
#include "IEntity.h"
#include "Dijkstra.h"

TileManager::TileManager(DrawManager* p_pxDrawManager, SpriteManager* p_pxSpriteManager)
{
	m_pxDrawManager = p_pxDrawManager;
	m_pxSpriteManager = p_pxSpriteManager;
	m_iWindowTileWidth = 52;
	m_iWindowTileHeight = 42;

	for (int i = 1; i < 256; i++)
	{
		m_apxSprites[i] = nullptr;
	}
}

TileManager::~TileManager()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_apxSprites[i] != nullptr)
		{
			m_pxSpriteManager->DestroySprite(m_apxSprites[i]);
			m_apxSprites[i] = nullptr;
		}
	}
}

void TileManager::SetTileSet(std::string p_sPath, int p_iTileWidth, int p_iTileHeight)
{
	m_iTileWidth = p_iTileWidth;
	m_iTileHeight = p_iTileHeight;

	for (int i = 0; i < 256; i++)
	{
		if (m_apxSprites[i] != nullptr)
		{
			m_pxSpriteManager->DestroySprite(m_apxSprites[i]);
			m_apxSprites[i] = nullptr;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		m_apxSprites[i] = m_pxSpriteManager->CreateSprite(
				p_sPath,
				(i % 16) * m_iTileWidth,
				(i / 16) * m_iTileHeight,
				m_iTileWidth, m_iTileHeight
				);
	}
	m_pxDrawManager->SetWindowSize(
		m_iTileWidth * m_iWindowTileWidth, m_iTileHeight * m_iWindowTileHeight);
}

void TileManager::DrawTile(Tile p_xTile, int p_iX, int p_iY)
{
	// First, draw the background to clear the tile
	m_pxDrawManager->DrawSprite(
		m_apxSprites[219],
		p_iX * m_iTileWidth, p_iY * m_iTileHeight,
		0x11, 0x12, 0x13); // TODO: Make background color customizable

	// Then draw the actual tile
	m_pxDrawManager->DrawSprite(
		m_apxSprites[p_xTile.spriteId], 
		p_iX * m_iTileWidth, p_iY * m_iTileHeight,
		p_xTile.r, p_xTile.g, p_xTile.b);
}

void TileManager::DrawTileMap(TileMap* p_pxTileMap, int p_iX, int p_iY, int p_iXOffset, int p_iYOffset, int p_iWidth, int p_iHeight)
{
	for (int y = 0; y < p_iHeight; y++)
	{
		for (int x = 0; x < p_iWidth; x++)
		{
			if (p_pxTileMap->IsSeen(x + p_iXOffset, y + p_iYOffset))
			{
				Tile temp = p_pxTileMap->GetTile(x + p_iXOffset, y + p_iYOffset);
				
				if (p_pxTileMap->IsVisible(x + p_iXOffset, y + p_iYOffset))
				{
					DrawTile(p_pxTileMap->GetTile(x + p_iXOffset, y + p_iYOffset),
						x + p_iX, y + p_iY);
				}
				else
				{
					temp.r /= 3;
					temp.g /= 3;
					temp.b /= 2;
					DrawTile(temp, x + p_iX, y + p_iY);
				}
			}
		}
	}
	std::vector<IEntity*> entities = p_pxTileMap->GetEntities();
	auto it = entities.begin();
	while (it != entities.end())
	{
		if ((*it)->IsVisible())
		{
			if (p_pxTileMap->IsVisible((*it)->GetX(), (*it)->GetY()))
			{
				if ((*it)->GetX() >= p_iXOffset && (*it)->GetX() < p_iXOffset + p_iWidth)
				{
					if ((*it)->GetY() >= p_iYOffset && (*it)->GetY() < p_iYOffset + p_iHeight)
					{
						DrawTile((*it)->GetTile(), (*it)->GetX() + p_iX - p_iXOffset, (*it)->GetY() + p_iY - p_iYOffset);
					}
				}
			}
		}
		it++;
	}
}

void TileManager::DrawText(std::string p_sText, int p_iX, int p_iY)
{
	int i = 0;
	auto it = p_sText.begin();
	while (it != p_sText.end())
	{
		if ((*it) >= 0 && (*it) < 256)
		{
			m_pxDrawManager->DrawSprite(
				m_apxSprites[(*it)],
				(p_iX + i) * m_iTileWidth, 
				p_iY * m_iTileHeight);
		}
		i++;
		it++;
	}
}

int TileManager::GetWindowTileWidth()
{
	return m_iWindowTileWidth;
}

int TileManager::GetWindowTileHeight()
{
	return m_iWindowTileHeight;
}
