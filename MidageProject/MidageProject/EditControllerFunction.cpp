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
#include "ObjectManager.h"
#include "Data.h"

void EditController::MapMove(void)
{
	if (!isMove) {
		if (key->isKeyDown(VK_MBUTTON)) {
			isMove = true;
			camPivot = { AppMouse.x, AppMouse.y };
			return;
		}
	}
	else {
		if (key->StayKeyDown(VK_MBUTTON)) {
			D2D_POINT_2L camMove;
			camMove.x = AppMouse.x - camPivot.x;
			camMove.y = AppMouse.y - camPivot.y;

			_CAM->x += camMove.x;
			_CAM->y += camMove.y;

			camPivot = { AppMouse.x, AppMouse.y };
		}
		else if (key->isKeyUp(VK_MBUTTON)) {
			isMove = false;
		}
	}
}

void EditController::ButtonUpdate(void)
{
	if (key->StayKeyDown(VK_LBUTTON)) {
		tBtn = ui->GetEditBtn()->SelectButton();
		if (tBtn == nullptr) return;
		tBtn->SetDirection(BTN_DOWN);
		tBtn->SetFrame({ 0, tBtn->GetDirection() });
	}
	else if (key->isKeyUp(VK_LBUTTON)) {
		if (tBtn == nullptr) return;
		if (tBtn->GetDirection() != BTN_DOWN) return;
		switch (tBtn->GetType())							//enum을 int형 변수로 치환시켜 선택한 버튼의 타입을 가져온다.
		{
		case EBTN_SEASON:
		case EBTN_NONSEASON:
		case EBTN_MAPOBJECT:
		case EBTN_PLAYER:
		case EBTN_BEAST:
		case EBTN_DEMON:
		case EBTN_HUMAN:
		case EBTN_DRAGON:
		case EBTN_BULIDING:
			ui->GetPalette()->ChangePalette(tBtn->GetName()); // 팔레트 목록의 버튼을 누르면 해당 팔레트로 전환
			break;
		case EBTN_HIDE:
			UIMove();
			break;
		case EBTN_SIZEUP:
			editMap->IncreaseMap();
			break;
		case EBTN_SIZEDOWN:
			editMap->DecreaseMap();
			break;
		case EBTN_SAVE:
			SaveObject();
			break;
		case EBTN_LOAD:
			LoadObject();
			break;
		case EBTN_EXIT:
			_SCENE->ChangeScene("Title");
			break;
		}
		tBtn->SetDirection(BTN_UP);
		tBtn->SetFrame({ 0, tBtn->GetDirection() });
		tBtn = nullptr;
	}
}

void EditController::UIMove(void)
{
	float moveQuantity = ui->GetMenu()->GetSize().height + 1;

	if (ui->GetMenu()->GetIsCull()) {
		ui->GetMenu()->SetMovePos(0, -moveQuantity);
		ui->GetEditBtn()->SetMovePos(0, -moveQuantity);
		ui->GetPalette()->SetMovePos(0, -moveQuantity);
	}
	else {
		ui->GetMenu()->SetMovePos(0, moveQuantity);
		ui->GetEditBtn()->SetMovePos(0, moveQuantity);
		ui->GetPalette()->SetMovePos(0, moveQuantity);
	}
}

void EditController::SelectPalette(void)
{
	if (key->isKeyDown(VK_LBUTTON)) {

		if (ui->GetPalette()->GetPaletteName().find("MAPOBJECT") != string::npos) {
			_select.matter = dynamic_cast<Matter*>(ui->GetPalette()->SelectPalette());
			if (_select.matter) 
				if (!_select.matter->GetImg()) _select.matter = nullptr;
			_select.tile = nullptr;
			_select.actor = nullptr;
		}
		else if (ui->GetPalette()->GetPaletteName().find("PLAYER") != string::npos ||
			ui->GetPalette()->GetPaletteName().find("BEAST") != string::npos ||
			ui->GetPalette()->GetPaletteName().find("DEMON") != string::npos || 
			ui->GetPalette()->GetPaletteName().find("HUMAN") != string::npos || 
			ui->GetPalette()->GetPaletteName().find("DRAGON") != string::npos) {
			_select.actor = dynamic_cast<Actor*>(ui->GetPalette()->SelectPalette());
			if (_select.actor)
				if (!_select.actor->GetImg()) _select.actor = nullptr;
			_select.tile = nullptr;
			_select.matter = nullptr;

			
		}
		else {
			_select.tile = dynamic_cast<Tile*>(ui->GetPalette()->SelectPalette());
			if (_select.tile) {
				if (!_select.tile->GetImg()) _select.matter = nullptr;
			}
			else return;
				
			_select.matter = nullptr;
			_select.actor = nullptr;

			if (!_select.tile->GetImg()) _select.tile = nullptr;
		}
	}
}

void EditController::SetObject(void)
{
	if (!_select.tile && !_select.matter &&
		!_select.actor) return;

	if (key->StayKeyDown(VK_LBUTTON)) {
		if (_select.tile) {
			editMap->SetMap(_select.tile);
		}
		else if (_select.matter) {
			manager->SetObject(_select.matter, editMap->GetMapTile());
		}
		else if (_select.actor) {
			manager->SetObject(_select.actor, editMap->GetMapTile());
		}
	}
}

void EditController::DeleteObject(void)
{
	if (key->StayKeyDown(VK_RBUTTON))
	{
		manager->EraseObject();
		editMap->DeleteMap();
	}
}

void EditController::SaveObject(void)
{
	data->SaveMap(editMap, FileSource("Resource", "EditData","Map_Save.txt"));
	data->SaveObjectPosition(manager, FileSource("Resource", "EditData", "Object_Save.txt"));
	if (manager->GetPlayer())
		data->SavePlayerPosition(manager->GetPlayer(), FileSource("Resource", "EditData", "Player_Save.txt"));
}

void EditController::LoadObject(void)
{
	data->LoadMap(editMap, FileSource("Resource", "EditData", "Map_Save.txt"));
	data->LoadObjectPosition(manager, FileSource("Resource", "EditData", "Object_Save.txt"));
	if (data->isExist(FileSource("Resource", "EditData", "Player_Save.txt")))
		data->LoadPlayerPosition(manager, FileSource("Resource", "EditData", "Player_Save.txt"));
}
