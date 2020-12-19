#pragma once
#include <vector>
#include "Button.h"

enum Ebtn_Type {
	EBTN_SEASON,
	EBTN_NONSEASON,
	EBTN_MAPOBJECT,
	EBTN_PLAYER,
	EBTN_BEAST,
	EBTN_DEMON,
	EBTN_HUMAN,
	EBTN_DRAGON,
	EBTN_BULIDING,
	EBTN_HIDE,
	EBTN_SIZEUP,
	EBTN_SIZEDOWN,
	EBTN_SAVE,
	EBTN_LOAD,
	EBTN_EXIT
};

class Pannel;
class EditBtnManager
{
private:
	vector<Button*> vUI;

public:
	EditBtnManager();
	~EditBtnManager();

	HRESULT Init(Pannel* menu);
	void Releas(void);
	void Update(void);
	void Render(void);

	
	Button* SelectButton(void);
	void SetMovePos(float x, float y);

	Button* GetBtn(UINT index) { return vUI[index]; }

	void SetName(Button* button, int type);
};

