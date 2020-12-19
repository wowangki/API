#pragma once
#include <vector>

enum SPannel_Type {
	SPANNEL_DEFAULT,
	SPANNEL_MENU
};

enum SButton_Kind {
	SBKIND_VITAL,
	SBKIND_ATK,
	SBKIND_STAMIN,
	SBKIND_DEXTERITY
};

enum SButton_Type {
	SBTN_OK,
	SBTN_INIT,
	SBTN_PLUS,
	SBTN_MINUS
};

enum SProperty {
	S_EARTH,
	S_WATER,
	S_FIRE,
	S_WIND
};

class Pannel;
class Button;
class Player;
class PlayerStatus
{
private:
	Player* player;
	
private:
	vector<Pannel*> vPannel;
	vector<vector<Button*>> vBtn;

public:
	struct nameRc {
		string name;
		D2D_RECT_F rc;
		bool isCull;
		bool isSelect;
	};

private:
	vector<nameRc> vName;
	vector<vector<nameRc>> vPointBar;


public:
	PlayerStatus(Player* player);
	~PlayerStatus();

	HRESULT Init(void);
	HRESULT CreateInit(void);
	void Release(void);
	void Update(void);
	void Render(void);
	void StatusMove(void);

	void CreateMenu(void);
	void CreateSlotMenu(void);
	void CreateNamePannel(void);
	void CreateEditButton(void);
	void CreatePlayButton(void);
	void CreateFunButton(void);
	void CreatePointBar(void);

	string SetVName(int index);
	void SetVName(void);
	void PointBarInit(void);
	void SetPointBar(void);
	void SetPointBar(int type);
	void SetPointBar(int type, int properPoint);

	Button* SelectButton(void);
	int SelectNameRc(void);

	Pannel* GetMenu(void) { return vPannel[0]; }
	vector<vector<nameRc>> GetVPoint(void) { return vPointBar; }
};

