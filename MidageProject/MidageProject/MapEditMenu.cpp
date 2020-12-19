#include "stdafx.h"
#include "MapEditMenu.h"
#include "MapEditButton.h"


MapEditMenu::MapEditMenu()
{
}

MapEditMenu::MapEditMenu(D2D_POINT_2F pos, string FileName)
{
	this->pos = pos;
	this->isMove = false;
	this->isOpen = false;
	graphic = new UIGraphic(FileName);

	size.width = graphic->GetImg()->GetFrameWidth() * 1.2;
	size.height = graphic->GetImg()->GetFrameHeight() * 1.4f;

	rc = FRectMake(pos.x, pos.y, size.width, size.height);
}


MapEditMenu::~MapEditMenu()
{
}

void MapEditMenu::Update()
{
	rc = FRectMake(pos.x, pos.y, size.width, size.height);

	if (isMove) {
		if (rc.left > WINSIZEX || rc.right < WINSIZEX) {
			isMove = false;
			isOpen = !isOpen;
		}

		if (!isOpen) {
			pos.x -= moveSpeed;
		}
		else {
			pos.x += moveSpeed;
		}
	}
}
