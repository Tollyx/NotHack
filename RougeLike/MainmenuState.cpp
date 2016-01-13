#include "stdafx.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "AudioManager.h"
#include "SpriteManager.h"
#include "MainmenuState.h"
#include "GameState.h"

MainmenuState::MainmenuState(System & p_xSystem)
{
	m_xSystem = p_xSystem;
	m_iSelection = 0;
}

MainmenuState::~MainmenuState()
{
}

void MainmenuState::Enter()
{
	for (int i = 0; i < 16 * 16; i++)
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
	
	m_asMenu.push_back("Start Game");
	m_asMenu.push_back("???");
	m_asMenu.push_back("Quit");
}

bool MainmenuState::Update(float p_fDeltaTime)
{

	if (m_xSystem.m_pxInputManager->IsKeyDown('w'))
	{
		m_iSelection--;
		if (m_iSelection < 0)
		{
			m_iSelection = 0;
		}
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown('s'))
	{
		m_iSelection++;
		if (m_iSelection > 2)
		{
			m_iSelection = 2;
		}
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(13)) // Enter
	{
		if (m_iSelection != 1)
		{
			return false;
		}
	}
	return true;
}

void MainmenuState::Exit()
{
	{
		auto it = m_apxSprites.begin();
		while (it != m_apxSprites.end())
		{
			m_xSystem.m_pxSpriteManager->DestroySprite(*it);
			it++;
		}
	}
}

void MainmenuState::Draw()
{
	std::string title = "NotHack";
	
	{
		int xPos = 3;
		auto it = title.begin();
		while (it != title.end())
		{
			m_xSystem.m_pxDrawManager->DrawSprite(
				m_apxSprites.at((*it)),
				xPos * 8, 12 * 4,
				225, 55, 55);
			xPos++;
			it++;
		}
	}
	{
		int yPos = 6;
		auto it = m_asMenu.begin();
		while (it != m_asMenu.end())
		{
			int xPos = 3;
			auto strIt = (*it).begin();
			while (strIt != (*it).end())
			{
				if (yPos - 6 == m_iSelection)
				{
					if (xPos == 3)
					{
						m_xSystem.m_pxDrawManager->DrawSprite(
							m_apxSprites.at('>'),
							xPos * 8 - 2, 12 * yPos,
							225, 225, 025);
					}
					m_xSystem.m_pxDrawManager->DrawSprite(
						m_apxSprites.at((*strIt)),
						(xPos + 1) * 8, 12 * yPos,
						225, 225, 025);
				}
				else
				{
					m_xSystem.m_pxDrawManager->DrawSprite(
						m_apxSprites.at((*strIt)),
						xPos * 8, 12 * yPos,
						225, 225, 225);
				}
				xPos++;
				strIt++;
			}
			yPos++;
			it++;
		}
	}
}

IState * MainmenuState::NextState()
{
	switch (m_iSelection)
	{
	case 0: // Start Game
		return new GameState(m_xSystem);

	case 1: // Leaderboards? Settings?
		return nullptr;

	case 2: // Quit
	default:
		return nullptr;
	}
	return nullptr;
}
