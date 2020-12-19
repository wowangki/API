#pragma once
#include "UIClass.h"

enum Btn_Direction {
	BTN_UP,
	BTN_DOWN
};

class Button : public UIClass
{
private:
	int direction;

public:
	Button();
	~Button();

	HRESULT Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale = { 1,1 }) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
	void UnNameRender(void);

	int GetDirection() { return direction; }
	void SetDirection(int direction) { this->direction = direction; }
};

