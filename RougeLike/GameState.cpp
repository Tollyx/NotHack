#include "stdafx.h"
#include "GameState.h"
#include "Map.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "DungeonGenerator.h"
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

	m_pxMap = DungeonGenerator::GenerateMap(m_iScreenTileWidth, m_iScreenTileHeight, 16, std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < 16*16; i++)
	{
		m_apxSprites.push_back(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/ascii.bmp", (i % 16) * 12, (i / 16) * 12 , 12, 12));
	}
}

bool GameState::Update(float p_fDeltaTime)
{
	return true;
}

void GameState::Exit()
{
	delete m_pxMap;
	m_pxMap = nullptr;

	auto it = m_apxSprites.begin();
	while (it != m_apxSprites.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite(*it);
		it++;
	}
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Clear();
	for (int y = 0; y < m_iScreenTileHeight; y++)
	{
		for (int x = 0; x < m_iScreenTileWidth; x++)
		{
			m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at(m_pxMap->GetTile(x, y)), x * 12, y * 12);
		}
	}
	/*
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('T'), 1 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('e'), 2 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('s'), 3 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('t'), 4 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('i'), 5 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('n'), 6 * 12, 1 * 12);
	m_xSystem.m_pxDrawManager->Draw(m_apxSprites.at('g'), 7 * 12, 1 * 12);
	*/
}

IState * GameState::NextState()
{
	return nullptr;
}
