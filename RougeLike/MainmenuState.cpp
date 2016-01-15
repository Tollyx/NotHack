#include "stdafx.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "AudioManager.h"
#include "TileManager.h"
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
	m_asMenu.push_back("Start Game");
	m_asMenu.push_back("???");
	m_asMenu.push_back("Quit");
}

bool MainmenuState::Update(float p_fDeltaTime)
{

	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_UP) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_8))
	{
		m_iSelection--;
		if (m_iSelection < 0)
		{
			m_iSelection = 0;
		}
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_DOWN) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_2))
	{
		m_iSelection++;
		if (m_iSelection > 2)
		{
			m_iSelection = 2;
		}
	}
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_RETURN) ||
		m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_ENTER))
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

}

void MainmenuState::Draw()
{
	m_xSystem.m_pxTileManager->DrawText("| |  | | | _  _|", 2, 8);
	m_xSystem.m_pxTileManager->DrawText("|\\|/\\|-|-|/.|/ |/", 2, 9);
	m_xSystem.m_pxTileManager->DrawText("| |\\/\\_| |\\_|\\_|\\", 2, 10);
	{
		int i = 0;
		auto it = m_asMenu.begin();
		while (it != m_asMenu.end())
		{
			if (i == m_iSelection)
			{
				m_xSystem.m_pxTileManager->DrawText(">" + (*it) + "<", 2, 12 + i);
			}
			else
			{
				m_xSystem.m_pxTileManager->DrawText((*it), 3, 12 + i);
			}
			i++;
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
