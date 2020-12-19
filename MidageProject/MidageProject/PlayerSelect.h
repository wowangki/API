#pragma once

class CreatePlayer;
class KeyModule;
class Player;
class Button;
class Data;
class PlayerSelect : public cApplication
{
public:
	struct CPlayerSlot {
		D2D_RECT_F rc;
		D2D_RECT_F imgRc;
		D2D_RECT_F statusRc[9];
		Player* player;
		Button* btn;
		string playerStatus[9];
	};

private:
	ImageModule* background;

	CPlayerSlot slot[3];

	Button* btn;

	bool isSelect;
	int slotNum;

private:
	KeyModule* key;
	CreatePlayer* create;
	Data* data;

public:
	PlayerSelect();
	~PlayerSelect();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;

	void SlotRender(void);

	void SetIsSelect(bool isSelect) { this->isSelect = isSelect; }
	void SetPlayerSlot(Player* player, int num);
	Data* GetData(void) { return data; }

};

