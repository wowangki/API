#pragma once

class Player;
class PlayerStatus;
class Button;
class KeyModule;
class Data;
class PlayerSelect;
class CreatePlayer
{
private:
	PlayerSelect* select;

private:
	Player* player;
	PlayerStatus* status;
	Button* tBtn;
	KeyModule* key;
	Data* data;

public:
	CreatePlayer(PlayerSelect* select);
	~CreatePlayer();

	HRESULT Init(void);
	void Release(void);
	void Update(int slotNum);
	void Render(void);

	Player* GetPlayer() { return player; }
	PlayerStatus* GetStatus() { return status; }
};

