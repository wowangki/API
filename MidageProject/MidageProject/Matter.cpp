#include "stdafx.h"
#include "Matter.h"


Matter::Matter()
{
}


Matter::~Matter()
{
}

HRESULT Matter::Init(D2D_POINT_2L id, D2D_POINT_2L frame, Matter_Kind matterKind, int type, GameObject_Kind kind)
{
	this->matterKind = matterKind;
	GameObject::Init(id, frame, type, kind);
	offset.width = size.width * 0.5f;
	offset.height = size.width * 0.5f;
	this->type = type;

	return S_OK;
}

void Matter::Release(void)
{
	GameObject::Release();
}

void Matter::Update(void)
{
	ISOMake();
	rc = FRectMakeCenter(pos.x, pos.y - size.height * 0.5f, size.width, size.height);
	isCull = IsWindowOut(rc);
}

void Matter::Render(void)
{
	if (isCull) return;
	img->CFrameRender(rymPos[2].x, rymPos[2].y, frame.x, frame.y, opacity);
}

HRESULT Matter::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, Matter_Kind matterKind, int type, GameObject_Kind kind)
{
	this->matterKind = matterKind;
	GameObject::PaletteInit(pos, frame, type, kind);
	this->size = { 35,35 };
	this->pos.x += size.width * 0.5f;
	this->pos.y += size.height * 0.5f;
	this->type = type;

	return S_OK;
}

void Matter::PaletteUpdate(void)
{
	GameObject::PaletteUpdate();
}

void Matter::PaletteRender(void)
{
	if (isCull) return;
	GameObject::PaletteRender();
}

void Matter::SetName(int type)
{
	switch (matterKind) {
	case TREE:
		imgKey = "Matter_Tree";
		break;
	}

	switch (type)
	{
	case TREE_NEEDLED_HIGH:
		name = "Tree_Needeled_High";
		break;
	case TREE_NEEDLED_MIDDLE:
		name = "Tree_Needeled_Middle";
		break;
	case TREE_NEEDLED_LOW:
		name = "Tree_Needeled_Low";
		break;
	case TREE_ROOT:
		name = "Tree_Root";
		break;
	}
}
