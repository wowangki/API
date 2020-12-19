#include "stdafx.h"
#include "GameObject.h"


HRESULT GameObject::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	SetName(type);
	this->id = { 0,0 };
	this->pos = pos;
	img = _IMAGE->FindImage(imgKey);
	this->frame = frame;
	opacity = 1.0f;
	this->kind = kind;
	this->type = type;
	size.width = 35.0f;
	size.height = 35.0f;
	offset = size;
	frameTime = 0;
	elapsedTime = 10;
	isCull = false;
	return S_OK;
}

void GameObject::PaletteUpdate(void)
{
	rc = FRectMakeCenter(pos.x, pos.y, size.width, size.height);
	isCull = UIIsWindowOut(rc);
}

void GameObject::PaletteRender(void)
{
	if (img == nullptr) return;
	img->CUiFrameRender(pos.x, pos.y, frame.x, frame.y, size.width, size.height, opacity);
}

void GameObject::ChangeObject(D2D_POINT_2L frame, int type)
{
	this->frame = frame;
	this->type = type;
	SetName(type);
	SetImg(imgKey);
	this->opacity = 1.0f;
}

void GameObject::SetLoadObject(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	this->id = id;
	this->frame = frame;
	this->type = type;
	SetName(this->type);
	SetImg(imgKey);
	this->opacity = 1.0f;
}
