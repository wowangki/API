#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


HRESULT GameObject::Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	SetName(type);
	img = _IMAGE->FindImage(imgKey);
	this->frame = frame;
	opacity = 1.0f;
	this->id = id;
	this->kind = kind;
	size.width = img->GetFrameWidth();
	size.height = img->GetFrameHeight();
	offset = size;
	frameTime = 0;
	elapsedTime = 10;
	isAlive = true;
	isCull = false;
	isEdit = false;
	ISOMake();
	rc = FRectMakeCenter(pos.x, pos.y, size.width, size.height);
	return S_OK;
}


void GameObject::Release(void)
{
	
}

void GameObject::Update(void)
{
	isCull = IsWindowOut(rc);
}
void GameObject::Render(void)
{
	img->CFrameRender(pos.x, pos.y, frame.x, frame.y, size.width, size.height, opacity);
}

void GameObject::ISOMake(void)
{
	pos = ISOPointMake(id, offset);
	
	RymBusPointMake(pos, rymPos, offset);
}
