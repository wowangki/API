#include "stdafx.h"
#include "EditController.h"
#include "KeyModule.h"
#include "EditUI.h"
#include "Pannel.h"
#include "EditBtnManager.h"
#include "Palette.h"
#include "MapClass.h"
#include "Tile.h"
#include "Matter.h"
#include "Actor.h"
#include "Data.h"

EditController::EditController()
	:isMove(false)
{	
}


EditController::~EditController()
{
	
}

HRESULT EditController::Init(EditUI* ui, MapClass* editMap, ObjectManager* manager)
{
	this->ui = ui;
	this->editMap = editMap;
	this->manager = manager;
	key = new KeyModule;
	data = new Data;
	_select.tile = nullptr;
	_select.matter = nullptr;
	_select.actor = nullptr;

	return S_OK;
}

void EditController::Release(void)
{
	SafeDelete(key);
	SafeDelete(_select.tile);
	SafeDelete(_select.matter);
	SafeDelete(_select.actor);
}

void EditController::Update(void)
{
	MapMove();
	if (MouseInRect(ui->GetUIRect()))
	{
		ButtonUpdate();
		if (MouseInRect(ui->GetMenu()->GetRc())) {
			SelectPalette();
		}
	}
	else
	{
		SetObject();
		DeleteObject();
	}
}

void EditController::Render(void)
{
	if (_select.tile != nullptr ) {
		_select.tile->GetImg()->CUiFrameRender((float)AppMouse.x, (float)AppMouse.y,
			_select.tile->GetFrame().x, _select.tile->GetFrame().y, 0.0f, 0.0f, 0.5f);
	}
	else if (_select.matter != nullptr) {
		_select.matter->GetImg()->CEditObjectFrameRender((float)AppMouse.x , (float)AppMouse.y,
			_select.matter->GetFrame().x, _select.matter->GetFrame().y, 0.5f);
	}
	else if (_select.actor != nullptr) {
		_select.actor->GetImg()->CEditObjectFrameRender((float)AppMouse.x, (float)AppMouse.y,
			_select.actor->GetFrame().x, _select.actor->GetFrame().y, 0.5f);
	}
}
