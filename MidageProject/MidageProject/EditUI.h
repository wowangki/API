#pragma once

class Pannel;
class EditBtnManager;
class Palette;
class Select;
class EditUI
{
private:
	EditBtnManager* btn;
	Pannel* menu;
	Palette* palette;

private:
	D2D_RECT_F rc;

public:
	EditUI();
	~EditUI();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	EditBtnManager* GetEditBtn() { return btn; }
	Pannel* GetMenu() { return menu; }
	Palette* GetPalette() { return palette; }

	D2D_RECT_F GetUIRect() { return rc; }
};

