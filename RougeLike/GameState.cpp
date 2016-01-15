#include "stdafx.h"
#include "GameState.h"
#include "MainmenuState.h"
#include "TileManager.h"
#include "TileMap.h"
#include "Player.h"
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
	m_xCamera.x = 0;
	m_xCamera.y = 0;
	m_xCamera.w = m_xSystem.m_pxTileManager->GetWindowTileWidth();
	m_xCamera.h = m_xSystem.m_pxTileManager->GetWindowTileHeight() - 8;

	m_iLevelDepth = 1;
	m_iTurns = 0;

	m_pxHitSound = m_xSystem.m_pxAudioManager->LoadSound("../assets/Hit.wav");
	m_pxLevelupSound = m_xSystem.m_pxAudioManager->LoadSound("../assets/Levelup.wav");

	m_pxPlayer = new Player(0, 0);
	NewMap();
}

bool GameState::Update(float p_fDeltaTime)
{
	bool update = false;
	int dx = 0, dy = 0;
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_UP) || 
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_8) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_7) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_9))
	{
		dy--;
		update = true;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_LEFT) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_4) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_7) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_1))
	{
		dx--;
		update = true;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_DOWN) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_2) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_1) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_3))
	{
		dy++;
		update = true;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_RIGHT) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_6) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_9) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_3))
	{
		dx++;
		update = true;
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_PERIOD) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_5))
	{
		update = true;
	}

	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_LCTRL) &&
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_l))
	{
		NewMap();
		update = true;
	}

	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_ESCAPE))
	{
		return false;
	}

	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_RETURN) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_ENTER) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_LESS))
	{
		SDL_Point exitPos = m_pxMap->GetExit();
		if (exitPos.x == m_pxPlayer->GetX() && exitPos.y == m_pxPlayer->GetY())
		{
			m_iLevelDepth++;
			m_asLog.push_back("You go down the stars to floor " + std::to_string(m_iLevelDepth) + ".");
			if (m_iLevelDepth > 8)
			{
				return false; // Congrats! You win!
			}
			NewMap();
			return true;
		}
		m_asLog.push_back("There's no stairs here.");
	}
	
	if (update) {
		if (m_pxMap->GetTile(m_pxPlayer->GetX() + dx, m_pxPlayer->GetY() + dy).isSolid == false)
		{
			// Player movement & attacking
			if (dx != 0 || dy != 0)
			{
				IEntity* entity = m_pxMap->GetEntityAt(m_pxPlayer->GetX() + dx, m_pxPlayer->GetY() + dy);
				if (entity == nullptr || !entity->IsVisible())
				{
					m_pxPlayer->Move(dx, dy);
					m_pxMap->ClearVisible();

					m_xCamera.x = m_pxPlayer->GetX() - m_xCamera.w / 2;
					m_xCamera.y = m_pxPlayer->GetY() - m_xCamera.h / 2;
				}
				else if (entity->GetType() == EENTITYTYPE::ENTITY_CREATURE)
				{
					ICreature* mob = static_cast<ICreature*>(entity);
				
					int dmg = mob->Hurt(m_pxPlayer->GetSTR());
					m_xSystem.m_pxAudioManager->PlaySound(m_pxHitSound, 0.4f);
					// Hardcoding the mob's name because I'm a lazy fuck. I mean, I don't have anything else than goblins ATM!
					m_asLog.push_back("You hit the goblin for " + std::to_string(dmg) + " damage.");
					if (mob->GetHP() <= 0)
					{
						m_asLog.push_back("The goblin died.");
						m_asLog.push_back("You gained " + std::to_string((int)(mob->GetLvl() * 1.5)) + "xp!");
						if (m_pxPlayer->AddXp(mob->GetLvl() * 1.5)) {
							m_xSystem.m_pxAudioManager->PlaySound(m_pxLevelupSound, 0.4f);
							m_asLog.push_back("You gained a level!");
						}
					}
				}
			}
		}
		m_pxMap->Update();
		m_pxMap->DoFOV(m_pxPlayer->GetX(), m_pxPlayer->GetY(), 16);
		m_iTurns++;
	}

	if (m_pxPlayer->GetHP() <= 0)
	{
		return false; // Congrats! You lost!
	}

	return true;
}

void GameState::Exit()
{
	delete m_pxMap;
	m_pxMap = nullptr;
	if (m_pxPlayer != nullptr)
	{
		delete m_pxPlayer;
		m_pxPlayer = nullptr;
	}
}

void GameState::Draw()
{
	m_xSystem.m_pxTileManager->DrawTileMap(m_pxMap, 0, 0, 
		m_xCamera.x, m_xCamera.y, 
		m_xCamera.w, m_xCamera.h);

	Tile temp;
	temp.r = 0xFF;
	temp.g = 0xFF;
	temp.b = 0xFF;

	int height = m_xSystem.m_pxTileManager->GetWindowTileHeight();
	int width = m_xSystem.m_pxTileManager->GetWindowTileWidth();

	// Horizontal seperator
	for (int i = 0; i < width; i++)
	{
		if (i == width - 16)
		{
			temp.spriteId = 16 * 12 + 2;
		}
		else
		{
			temp.spriteId = 16 * 12 + 4;
		}
		m_xSystem.m_pxTileManager->DrawTile(temp, i, m_xCamera.h);
	}

	// Log
	{
		int i = 0;
		auto it = m_asLog.rbegin();
		while (i < height - m_xCamera.h - 1 && it != m_asLog.rend())
		{
			m_xSystem.m_pxTileManager->DrawText((*it), 1, height - 1 - i);
			i++;
			it++;
		}
	}

	// Vertical seperator
	temp.spriteId = 16 * 11 + 3;
	for (int i = 0; i < height - m_xCamera.h; i++)
	{
		m_xSystem.m_pxTileManager->DrawTile(temp,
			width - 16, height - i);
	}

	// Health and max health
	m_xSystem.m_pxTileManager->DrawText(
		"HP:" + std::to_string(m_pxPlayer->GetHP()) + "/" + std::to_string(m_pxPlayer->GetMaxHP()),
		width - 14, m_xCamera.h + 2);


	// Level
	m_xSystem.m_pxTileManager->DrawText("LVL:" + std::to_string(m_pxPlayer->GetLvl()),
		width - 14, m_xCamera.h + 4);

	// Experience to next level
	m_xSystem.m_pxTileManager->DrawText("NXT:" + std::to_string(m_pxPlayer->NextLvl()),
		width - 7, m_xCamera.h + 4);

	// Strength
	m_xSystem.m_pxTileManager->DrawText("STR:" + std::to_string(m_pxPlayer->GetSTR()),
		width - 14, m_xCamera.h + 6);

	// Defence
	m_xSystem.m_pxTileManager->DrawText("DEF:" + std::to_string(m_pxPlayer->GetDEF()),
		width - 7, m_xCamera.h + 6);
}

IState * GameState::NextState()
{
	if (m_pxPlayer->GetHP() <= 0)
	{
		printf("\nYou died.\n\n");
		return new MainmenuState(m_xSystem); // TODO: gameover state
	}
	else if(m_iLevelDepth > 10)
	{
		printf("\nYou won!\n\n");
		return new MainmenuState(m_xSystem); // TODO: win state
	}
	// This one should never be returned. 
	// But if it does, the game will shut down.
	return nullptr;
}

void GameState::NewMap()
{
	if (m_pxMap != nullptr)
	{
		m_pxMap->RemoveEntity(m_pxPlayer);
		delete m_pxMap;
	}
	m_pxMap = DungeonGenerator::GenerateMap(
		30 + m_iLevelDepth * 2, 
		30 + m_iLevelDepth * 2, 
		16 + m_iLevelDepth * 2, 
		m_iLevelDepth * 2,
		std::chrono::system_clock::now().time_since_epoch().count());
	SDL_Point entrancePos = m_pxMap->GetEntrance();
	m_pxPlayer->SetPos(entrancePos.x, entrancePos.y);
	m_pxMap->AddEntity(m_pxPlayer);
	m_pxMap->DoFOV(m_pxPlayer->GetX(), m_pxPlayer->GetY(), 16);
	m_xCamera.x = m_pxPlayer->GetX() - m_xCamera.w / 2;
	m_xCamera.y = m_pxPlayer->GetY() - m_xCamera.h / 2;
}
