#pragma once
#include <vector>

enum CommandUI_Type {
	COM_DEFAULT,
	COM_ATTACK_N,
	COM_ATTACK_S,
	COM_GUARD,
	COM_AVOID
};

class Button;
class Player;
class CommandUI
{
private:
	Player* player;
private:
	vector<Button*> vBtn;

public:
	CommandUI(Player* player);
	~CommandUI();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void CreateCommandBtn(void);

	Button* SelectBtn(void);
};

