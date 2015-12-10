#pragma once

class Mouse
{
public:
	Mouse();
	~Mouse();

	int GetX();
	int GetY();
	void SetPosition(int p_iX, int p_iY);
	bool IsButtonDown(int p_iIndex);
	void SetButton(int p_iIndex, 
						bool p_bValue);
private:
	bool m_abButtons[3];
	int m_iX;
	int m_iY;

	
};