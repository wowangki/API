#pragma once
#include "KeyModule.h"

enum Title_Menu {
	MENU_SELECT = 1,
	MENU_EDIT,
	MENU_OPTION
};

class TitleScene : public cApplication
{
private:
	struct TitleBtn {
		string name;
		ImageModule* img;
		D2D_POINT_2F pos;
		D2D_POINT_2L frame;
		D2D_RECT_F rc;
	};

	TitleBtn btn[4];

private:
	D2D_RECT_F selectRc;
	int selectIndex;

private:
	ImageModule * background;

private:
	KeyModule * key;

public:
	TitleScene();
	~TitleScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;


	void SelectBtn(void);
};

