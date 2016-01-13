#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	m_fMasterVolume = 1.0f;
}

AudioManager::~AudioManager()
{
}

bool AudioManager::Initialize()
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
	return true;
}

void AudioManager::Shutdown()
{

	{
		auto it = m_apxSounds.begin();
		while (it != m_apxSounds.end())
		{
			Mix_FreeChunk(it->second);
			it++;
		}
	}

	Mix_CloseAudio();
}

void AudioManager::PlaySound(Mix_Chunk * p_pxSound, float p_fVolume)
{
	Mix_VolumeChunk(p_pxSound, 128 * m_fMasterVolume * p_fVolume);
	Mix_PlayChannel(-1, p_pxSound, 0);
}

Mix_Chunk* AudioManager::LoadSound(const std::string & p_sFilepath)
{
	auto it = m_apxSounds.find(p_sFilepath);
	if (it == m_apxSounds.end())
	{
		Mix_Chunk* xSound = Mix_LoadWAV(p_sFilepath.c_str());
		m_apxSounds.insert(std::pair<std::string, Mix_Chunk*>(p_sFilepath, xSound));
		it = m_apxSounds.find(p_sFilepath);
	}
	return it->second;
}

void AudioManager::DestroySound(const std::string & p_sFilepath)
{
	auto it = m_apxSounds.find(p_sFilepath);
	if (it != m_apxSounds.end())
	{
		Mix_FreeChunk(it->second);
		m_apxSounds.erase(it);
	}
}

void AudioManager::DestroySound(Mix_Chunk * p_pxSound)
{
	auto it = m_apxSounds.begin();
	while (it != m_apxSounds.end())
	{
		if (it->second == p_pxSound)
		{
			Mix_FreeChunk(it->second);
			m_apxSounds.erase(it);
		}
		it++;
	}
}

void AudioManager::SetMasterVolume(float p_fVolume)
{
	m_fMasterVolume = p_fVolume;
}
