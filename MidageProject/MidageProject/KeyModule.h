#pragma once
class KeyModule
{
private:
	byte bKeyDown[256];
	byte PrevKey;
public:
	KeyModule();
	~KeyModule();

	bool isKeyDown(int KeyCode);
	bool StayKeyDown(int KeyCode);
	bool isKeyUp(int KeyCode);
	bool ToggleKeyDown(int KeyCode);
};

