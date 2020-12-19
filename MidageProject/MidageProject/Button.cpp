#include "stdafx.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}

HRESULT Button::Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale)
{
	UIClass::Init(imgKey, pos, frame, type, kind, scale);
	direction = BTN_UP;
	return S_OK;
}

void Button::Release(void)
{
	UIClass::Release();
}

void Button::Update(void)
{
	UIClass::Update();
	if (!MouseInRect(rc)) {
		direction = BTN_UP;
		frame.y = direction;
	}
}

void Button::Render(void)
{
	UIClass::Render();
	_FONT->Render(name, rc, nullptr, "BTNNAME");
}

void Button::UnNameRender(void)
{
	UIClass::Render();
}
