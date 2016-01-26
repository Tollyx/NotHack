#include "stdafx.h"
#include "StateManager.h"
#include "IState.h"

StateManager::StateManager()
{
	m_pxCurrentState = nullptr;
	m_iLastTick = SDL_GetTicks();
}

StateManager::~StateManager()
{
	if (m_pxCurrentState != nullptr)
	{
		delete m_pxCurrentState;
		m_pxCurrentState = nullptr;
	}
}

bool StateManager::Update()
{
	float fDeltaTime = (SDL_GetTicks() - m_iLastTick) * 0.01;
	m_iLastTick = SDL_GetTicks();

	if (m_pxCurrentState != nullptr)
	{
		if (m_pxCurrentState->Update(fDeltaTime) == false)
		{
			IState* nextState = m_pxCurrentState->NextState();
			if (nextState != nullptr)
			{
				SetState(nextState);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void StateManager::Draw()
{
	if (m_pxCurrentState != nullptr)
	{
		m_pxCurrentState->Draw();
	}
}

void StateManager::SetState(IState* p_pxState)
{
	if (m_pxCurrentState != nullptr)
	{
		m_pxCurrentState->Exit();
		delete m_pxCurrentState;
		m_pxCurrentState = nullptr;
	}
	m_pxCurrentState = p_pxState;
	m_pxCurrentState->Enter();
}