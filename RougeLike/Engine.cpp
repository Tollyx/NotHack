#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "TileManager.h"
#include "AudioManager.h"
#include "StateManager.h"
#include "IState.h"
#include "MainmenuState.h"
#include "GameState.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "InputManager.h"
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
	if (m_pxDrawManager->Initialize(42 * 12, 32 * 12) == false)
	{
		return false;
	}

	m_pxAudioManager = new AudioManager();
	if (m_pxAudioManager->Initialize() == false)
	{
		return false;
	}

	m_pxInputManager = new InputManager();

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxTileManager = new TileManager(m_pxDrawManager, m_pxSpriteManager);
	m_pxTileManager->SetTileSet("../assets/12x12.bmp", 12, 12);
	//m_pxTileManager->SetTileSet("../assets/16x16.bmp", 16, 16);
	//m_pxTileManager->SetTileSet("../assets/24x24.bmp", 24, 24);

	m_pxStateManager = new StateManager();

	System system;
	system.m_pxTileManager = m_pxTileManager;
	system.m_pxAudioManager = m_pxAudioManager;
	system.m_pxInputManager = m_pxInputManager;
	m_pxStateManager->SetState(new MainmenuState(system));

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

	delete m_pxKeyboard;
	m_pxKeyboard = nullptr;

	m_pxAudioManager->Shutdown();
	delete m_pxAudioManager;
	m_pxAudioManager = nullptr;

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
		if (HandleEvents()) // Only update if needed, in other words, if a keypress happened.
		{
			if (!m_pxStateManager->Update())
			{
				m_bRunning = false;
			}
		}
		m_pxDrawManager->Clear();
		m_pxStateManager->Draw();

		m_pxDrawManager->Present();
		SDL_Delay(1000 / 60);
	}
}

bool Engine::HandleEvents()
{
	bool needsUpdate = false;
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{
		if (xEvent.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else
		{
			needsUpdate = m_pxInputManager->Update(xEvent);
		}
	}
	return needsUpdate;
}