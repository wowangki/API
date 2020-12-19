#include "stdafx.h"
#include "SearchObject.h"
#include "Actor.h"
#include "ObjectManager.h"
#include "MapClass.h"

SearchObject::SearchObject(int size)
{
	this->size = size;
	if (this->size % 2 == 0) {
		this->size++;
	}

	objectSearchSize = (int)(size * 0.5f);
	if (objectSearchSize % 2 == 0) {
		objectSearchSize++;
	}
}


SearchObject::~SearchObject()
{
}

HRESULT SearchObject::Init(Actor* actor, ObjectManager* manager, MapClass* map)
{
	this->actor = actor;
	this->manager = manager;
	this->map = map;
	CreateCollisionSearch();

	return S_OK;
}

void SearchObject::Update(void)
{
	if (!map) return;
	CollisionSearch();
	RymBusPointMake(actor->GetPos(), rymPos, { actor->GetOffset().width * objectSearchSize, actor->GetOffset().height * objectSearchSize });
	ObjectSearch();
}

void SearchObject::Render(void)
{	
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (!collisionSearch[y][x].isInISO) {
				_RenderTarget->DrawLine({collisionSearch[y][x].rymPos[0].x + _CAM->x, + collisionSearch[y][x].rymPos[0].y + _CAM->y}, {collisionSearch[y][x].rymPos[1].x + _CAM->x, collisionSearch[y][x].rymPos[1].y + _CAM->y}, _Device->pDefaultBrush);
				_RenderTarget->DrawLine({collisionSearch[y][x].rymPos[0].x + _CAM->x, + collisionSearch[y][x].rymPos[0].y + _CAM->y}, {collisionSearch[y][x].rymPos[3].x + _CAM->x, collisionSearch[y][x].rymPos[3].y + _CAM->y}, _Device->pDefaultBrush);
				_RenderTarget->DrawLine({collisionSearch[y][x].rymPos[1].x + _CAM->x, + collisionSearch[y][x].rymPos[1].y + _CAM->y}, {collisionSearch[y][x].rymPos[2].x + _CAM->x, collisionSearch[y][x].rymPos[2].y + _CAM->y}, _Device->pDefaultBrush);
				_RenderTarget->DrawLine({collisionSearch[y][x].rymPos[2].x + _CAM->x, + collisionSearch[y][x].rymPos[2].y + _CAM->y}, {collisionSearch[y][x].rymPos[3].x + _CAM->x, collisionSearch[y][x].rymPos[3].y + _CAM->y}, _Device->pDefaultBrush);
			}
			else {
				_RenderTarget->DrawLine({ collisionSearch[y][x].rymPos[0].x + _CAM->x, +collisionSearch[y][x].rymPos[0].y + _CAM->y }, { collisionSearch[y][x].rymPos[1].x + _CAM->x, collisionSearch[y][x].rymPos[1].y + _CAM->y }, _BRUSH->GetBrush("RED"));
				_RenderTarget->DrawLine({ collisionSearch[y][x].rymPos[0].x + _CAM->x, +collisionSearch[y][x].rymPos[0].y + _CAM->y }, { collisionSearch[y][x].rymPos[3].x + _CAM->x, collisionSearch[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("RED"));
				_RenderTarget->DrawLine({ collisionSearch[y][x].rymPos[1].x + _CAM->x, +collisionSearch[y][x].rymPos[1].y + _CAM->y }, { collisionSearch[y][x].rymPos[2].x + _CAM->x, collisionSearch[y][x].rymPos[2].y + _CAM->y }, _BRUSH->GetBrush("RED"));
				_RenderTarget->DrawLine({ collisionSearch[y][x].rymPos[2].x + _CAM->x, +collisionSearch[y][x].rymPos[2].y + _CAM->y }, { collisionSearch[y][x].rymPos[3].x + _CAM->x, collisionSearch[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("RED"));
			}
		}
	}
	
	//for (UINT i = 0; i < vObjectSearch.size(); i++)
	//{
	//	DrawISO(vObjectSearch[i]->GetRymPos(), "BLACK");
	//}
	//
	//DrawISO(rymPos, "BLACK");

}
