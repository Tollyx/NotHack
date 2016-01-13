#pragma once

class Mix_Chunk;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	void Shutdown();
	void PlaySound(Mix_Chunk* p_pxSound, float p_fVolume);
	Mix_Chunk* LoadSound(const std::string& p_sFilepath);
	void DestroySound(const std::string& p_sFilepath);
	void DestroySound(Mix_Chunk* p_pxSound);
	void SetMasterVolume(float p_fVolume);
private:
	float m_fMasterVolume;
	std::map<std::string, Mix_Chunk*> m_apxSounds;
};
