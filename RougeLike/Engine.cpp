#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "IState.h"
#include "GameState.h"
#include "Sprite.h"
#include "Mouse.h"
#include <iostream>

Engine::Engine()
{
	m_bRunning = false;
	m_pxDrawManager = nullptr;
	m_pxSpriteManager = nullptr;
	m_pxStateManager = nullptr;
	m_pxMouse = nullptr;
}

Engine::~Engine()
{

}


bool Engine::Initialize()
{
	// The initialize function will intialize libraries the program depends on and all manager we will create.
	 
	// Initializes the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	// Creates a new DrawManager and calls Initialize with width / height parameters.
	m_pxDrawManager = new DrawManager();
	if (m_pxDrawManager->Initialize(640, 480) == false)
	{
		return false;
	}
	m_pxMouse = new Mouse();

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();

	System system;
	system.m_iScreenWidth = 640;
	system.m_iScreenHeight = 480;
	system.m_pxDrawManager = m_pxDrawManager;
	system.m_pxSpriteManager = m_pxSpriteManager;
	system.m_pxMouse = m_pxMouse;
	m_pxStateManager->SetState(new GameState(system));

	m_bRunning = true;

	return true;
}

void Engine::Shutdown()
{
	// The shutdown function will quit, delete and shutdown everything we have started up or created in initialize (In reverse order of creation)
	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;

	delete m_pxStateManager;
	m_pxStateManager = nullptr;
	
	delete m_pxMouse;
	m_pxMouse = nullptr;

	// Shuts down the drawmanager before deleting the object and nulling the pointer.
	m_pxDrawManager->Shutdown();
	delete m_pxDrawManager;
	m_pxDrawManager = nullptr;

	SDL_Quit();
}

void Engine::Update()
{

	// Our engines core loop
	while (m_bRunning)
	{
		HandleEvents();
		if (!m_pxStateManager->Update()) 
		{
			m_bRunning = false;
		}
		m_pxDrawManager->Clear();
		m_pxStateManager->Draw();
		
		m_pxDrawManager->Present();
		SDL_Delay(10);
	}
}

void Engine::HandleEvents()
{
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{
		if (xEvent.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else if (xEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			m_pxMouse->SetButton(xEvent.button.button, true);
		}
		else if (xEvent.type == SDL_MOUSEBUTTONUP)
		{
			m_pxMouse->SetButton(xEvent.button.button, false);
		}
		else if (xEvent.type == SDL_MOUSEMOTION)
		{
			m_pxMouse->SetPosition(xEvent.motion.x, xEvent.motion.y);
		}
		else if (xEvent.type == SDL_KEYDOWN)
		{
			
		}
		else if (xEvent.type == SDL_KEYUP)
		{

		}
	}
}