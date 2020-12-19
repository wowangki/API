#include "stdafx.h"
#include "UIClass.h"


UIClass::UIClass()
{
}


UIClass::~UIClass()
{
}

HRESULT UIClass::Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale)
{
	this->name = imgKey;
	this->imgKey = imgKey;
	img = _IMAGE->FindImage(imgKey);
	this->pos = pos;
	this->frame = frame;
	this->type = type;
	this->kind = kind;
	opacity = 1.0f;
	isCull = false;
	isActive = false;
	size.width = img->GetFrameWidth() * scale.width;
	size.height = img->GetFrameHeight() * scale.height;

	return S_OK;
}

void UIClass::Release(void)
{
}

void UIClass::Update(void)
{
	rc = FRectMakeCenter(pos.x, pos.y, size.width, size.height);
	isCull = UIIsWindowOut(rc);
}

void UIClass::Render(void)
{
	if (isCull) return;
	img->CUiFrameRender(pos.x, pos.y, frame.x, frame.y, size.width, size.height, opacity);
}
