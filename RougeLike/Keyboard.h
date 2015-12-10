#pragma once

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	bool IsKeyDown(int p_iIndex);
	void SetKey(int p_iIndex, 
		bool p_bValue);
private:
	bool m_abKeys[256];
};