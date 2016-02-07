#pragma once
#include "stdafx.h"
#include "GameOverState.h"
#include "MainmenuState.h"
#include "TileManager.h"
#include "InputManager.h"

GameOverState::GameOverState(System p_xSystem, GameOverData p_xData)
{
	m_xSystem = p_xSystem;
	m_xData = p_xData;
}

GameOverState::~GameOverState()
{
}

void GameOverState::Enter()
{
}

bool GameOverState::Update(float p_fDeltaTime)
{
	if (m_xSystem.m_pxInputManager->IsKeyDown(SDLK_RETURN) || m_xSystem.m_pxInputManager->IsKeyDown(SDLK_KP_ENTER) || m_xSystem.m_pxInputManager->IsKeyDown(SDLK_ESCAPE))
	{
		return false;
	}
	return true;
}

void GameOverState::Exit()
{
}

void GameOverState::Draw()
{
	m_xSystem.m_pxTileManager->DrawText("Game Over", 10, 10);
	int height = m_xSystem.m_pxTileManager->GetWindowTileHeight();
	m_xSystem.m_pxTileManager->DrawText("Press Enter to Continue.", 10, height - 10);

	m_xSystem.m_pxTileManager->DrawText("You died on floor " + std::to_string(m_xData.floor), 10, 20);
	m_xSystem.m_pxTileManager->DrawText("You lived for " + std::to_string(m_xData.turns) + " turns", 10, 21);
	m_xSystem.m_pxTileManager->DrawText("You were killed by a " + m_xData.killedBy, 10, 22);
	m_xSystem.m_pxTileManager->DrawText("You killed " + std::to_string(m_xData.kills) + " innocent creatures", 10, 23);
}

IState* GameOverState::NextState()
{
	return new MainmenuState(m_xSystem);
}
