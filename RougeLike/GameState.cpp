#include "stdafx.h"
#include "GameState.h"
#include "MainmenuState.h"
#include "Map.h"
#include "Player.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "AudioManager.h"
#include "Sprite.h"
#include "DungeonGenerator.h"
#include "InputManager.h"
#include <chrono>

GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxMap = nullptr;
}

GameState::~GameState()
{
	
}

void GameState::Enter()
{
	m_iScreenTileHeight = m_xSystem.m_iScreenHeight / 12;
	m_iScreenTileWidth = m_xSystem.m_iScreenWidth / 12;

	m_xCamera.x = 0;
	m_xCamera.y = 0;
	m_xCamera.w = m_iScreenTileWidth - 12;
	m_xCamera.h = m_iScreenTileHeight - 2;

	m_iLevelDepth = 0;
	m_iTurns = 0;

	for (int i = 0; i < 16*16; i++)
	{
		m_apxSprites.push_back(
			m_xSystem.m_pxSpriteManager->CreateSprite(
				"../assets/ascii.bmp", 
				(i % 16) * 12, 
				(i / 16) * 12, 
				12, 12
			)
		);
	}

	m_pxPlayer = new Player(0, 0);
	m_apxEntities.push_back(m_pxPlayer);
	NewMap();

	m_pxTestSound = m_xSystem.m_pxAudioManager->LoadSound("../assets/test.ogg");
}

bool GameState::Update(float p_fDeltaTime)
{
	int dx = 0, dy = 0;
	if (m_xSystem.m_pxInputManager->IsKeyDown('w'))
	{
		dy--;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown('a'))
	{
		dx--;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown('s'))
	{
		dy++;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown('d'))
	{
		dx++;
	}

	if (m_xSystem.m_pxInputManager->IsKeyDown(27)) // Escape
	{
		return false;
	}
	
	if (dx != 0 || dy != 0) {
		m_xSystem.m_pxAudioManager->PlaySound(m_pxTestSound, 1.0f);
		if (m_pxMap->GetTile(m_pxPlayer->GetX() + dx, m_pxPlayer->GetY() + dy).isSolid == false)
		{
			m_pxPlayer->Move(dx, dy);

			m_xCamera.x = m_pxPlayer->GetX() - m_xCamera.w / 2;
			m_xCamera.y = m_pxPlayer->GetY() - m_xCamera.h / 2;
		}

		SDL_Point exitPos = m_pxMap->GetExit();
		if ( exitPos.x == m_pxPlayer->GetX() && exitPos.y == m_pxPlayer->GetY())
		{
			m_iLevelDepth++;
			NewMap();
		}
		else
		{
			auto it = m_apxEntities.begin();
			while (it != m_apxEntities.end())
			{
				(*it)->Update();
				it++;
			}
		}
		//SDL_Delay(100);
		m_iTurns++;
	}

	if (m_pxPlayer->GetHP() <= 0)
	{
		return false;
	}

	return true;
}

void GameState::Exit()
{
	delete m_pxMap;
	m_pxMap = nullptr;
	{
		auto it = m_apxSprites.begin();
		while (it != m_apxSprites.end())
		{
			m_xSystem.m_pxSpriteManager->DestroySprite(*it);
			it++;
		}
	}
	{
		auto it = m_apxEntities.begin();
		while (it != m_apxEntities.end())
		{
			delete (*it);
			it++;
		}
	}
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Clear();
	for (int y = 0; y < m_xCamera.h; y++)
	{
		for (int x = 0; x < m_xCamera.w; x++)
		{
			Tile t = m_pxMap->GetTile(x + m_xCamera.x, y + m_xCamera.y);
			m_xSystem.m_pxDrawManager->DrawSprite(
				m_apxSprites.at(t.spriteId), 
				(x + 12) * 12, 
				(y + 0) * 12,
				t.r, t.g, t.b);
		}
	}

	auto it = m_apxEntities.begin();
	while (it != m_apxEntities.end())
	{
		// Background
		m_xSystem.m_pxDrawManager->DrawSprite(
			m_apxSprites.at(219), // A square that covers the entire tile
			((*it)->GetX() + 12 - m_xCamera.x) * 12, 
			((*it)->GetY() + 0 - m_xCamera.y) * 12,
			0, 0, 0);

		// Foreground
		Tile tile = (*it)->GetTile();
		m_xSystem.m_pxDrawManager->DrawSprite(
			m_apxSprites.at(tile.spriteId), 
			((*it)->GetX() + 12 - m_xCamera.x) * 12,
			((*it)->GetY() + 0 - m_xCamera.y) * 12,
			tile.r, tile.g, tile.b);

		it++;
	}

	/*
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('T'), 1 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('e'), 2 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('s'), 3 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('t'), 4 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('i'), 5 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('n'), 6 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->DrawSprite(m_apxSprites.at('g'), 7 * 12, 1 * 12);
	*/
}

IState * GameState::NextState()
{
	return new MainmenuState(m_xSystem); // Todo: goto gameover state
}

void GameState::NewMap()
{
	if (m_pxMap != nullptr)
	{
		delete m_pxMap;
	}
	m_pxMap = DungeonGenerator::GenerateMap(
		m_xCamera.w / 2 + m_iLevelDepth * 2, 
		m_xCamera.h / 2 + m_iLevelDepth * 2, 
		16 + m_iLevelDepth * 2, 
		std::chrono::system_clock::now().time_since_epoch().count());
	SDL_Point entrancePos = m_pxMap->GetEntrance();
	m_pxPlayer->SetPos(entrancePos.x, entrancePos.y);
	m_xCamera.x = m_pxPlayer->GetX() - m_xCamera.w / 2;
	m_xCamera.y = m_pxPlayer->GetY() - m_xCamera.h / 2;
}
