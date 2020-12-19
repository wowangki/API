#include "stdafx.h"
#include "PlayController.h"
#include "ObjectManager.h"
#include "Player.h"
#include "PlayUI.h"
#include "MapClass.h"
#include "Tile.h"
#include "PlayerStatus.h"
#include "OptionUI.h"
#include "Button.h"
#include "Pannel.h"
#include "CommandUI.h"
#include "AStar.h"
#include "Data.h"

PlayController::PlayController(ObjectManager* object, PlayUI* ui, MapClass* map, Data* data)
{
	key = new KeyModule;
	this->object = object;
	this->ui = ui;
	this->map = map;
	this->data = data;
	dest = nullptr;
	sTbtn = nullptr;
	bTbtn = nullptr;
	oTbtn = nullptr;
	isEdit = false;
}


PlayController::~PlayController()
{
}

HRESULT PlayController::Init(void)
{
	player = object->GetPlayer();
	camSpeed = player->GetMoveSpeed();

	return S_OK;
}

void PlayController::Update(void)
{
	if (ui->GetType() == UI_FIELD) {
		FieldMoveControl();
		StatusControl();
	}
	else if (ui->GetType() == UI_BATTLE) {
		BattleComControl();
		BattleControl();
	}

	OptionControl();
}

void PlayController::FieldMoveControl(void)
{
	SearchObject::SearchIt(*tCollision)[3] = player->GetSearch()->GetCollisionSearch();
	D2D_POINT_2F pos = player->GetPos();
	PlayerStatus* status = ui->GetStatus();
	if (MouseInRect(status->GetMenu()->GetRc())) return;

	preCAM = { _CAM->x, _CAM->y };
	
	if (key->StayKeyDown(VK_LBUTTON)) {
		dest = map->GetMapTile();
	}

	if (!dest) return;

	if (dest->GetPos().x >= pos.x - 1 &&
		dest->GetPos().x <= pos.x + 1 &&
		dest->GetPos().y >= pos.y - 1 &&
		dest->GetPos().y <= pos.y + 1) {
		dest = nullptr;
		return;
	}
		
	// аб
	if (dest->GetPos().x < pos.x) {
		if (!tCollision[2][0].isInISO) {
			_CAM->x += camSpeed * 0.5f;
			pos.x -= player->GetMoveSpeed() * 0.5f;
			player->SetPos(pos);
		}
	}
	// ©Л
	else if (dest->GetPos().x > pos.x) {
		if (!tCollision[0][2].isInISO) {
			_CAM->x -= camSpeed * 0.5f;
			pos.x += player->GetMoveSpeed() * 0.5f;
			player->SetPos(pos);
		}
	}

	// ╩С
	if (dest->GetPos().y < pos.y) {
		if (!tCollision[0][0].isInISO) {
			_CAM->y += camSpeed * 0.27f;
			pos.y -= player->GetMoveSpeed() * 0.27f;
			player->SetPos(pos);
		}
	}
	// го
	else if (dest->GetPos().y > pos.y) {
		if (!tCollision[2][2].isInISO) {
			_CAM->y -= camSpeed * 0.27f;
			pos.y += player->GetMoveSpeed() * 0.27f;
			player->SetPos(pos);
		}
	}


	/*
	if (key->StayKeyDown(VK_LEFT)) {
		if (!tCollision[2][0].isInISO) {
			_CAM->x += camSpeed * 0.5f;
			pos.x -= player->GetMoveSpeed() * 0.5f;
			player->SetPos(pos);
		}
	}
	else if (key->StayKeyDown(VK_RIGHT)) {
		if (!tCollision[0][2].isInISO) {
			_CAM->x -= camSpeed * 0.5f;
			pos.x += player->GetMoveSpeed() * 0.5f;
			player->SetPos(pos);
		}
	}

	if (key->StayKeyDown(VK_UP)) {
		if (!tCollision[0][0].isInISO) {
			_CAM->y += camSpeed * 0.27f;
			pos.y -= player->GetMoveSpeed() * 0.27f;
			player->SetPos(pos);
		}
	}
	else if (key->StayKeyDown(VK_DOWN)) {
		if (!tCollision[2][2].isInISO) {
			_CAM->y -= camSpeed * 0.27f;
			pos.y += player->GetMoveSpeed() * 0.27f;
			player->SetPos(pos);
		}
	}
	*/
}

void PlayController::StatusControl(void)
{
	PlayerStatus* status = ui->GetStatus();

	if (key->StayKeyDown(VK_CONTROL) && key->isKeyDown('S'))
	{
		status->StatusMove();
	}

	if (!MouseInRect(status->GetMenu()->GetRc())) return;

	if (key->StayKeyDown(VK_LBUTTON)) {
		sTbtn = status->SelectButton();
		if (sTbtn == nullptr) return;
		sTbtn->SetDirection(BTN_DOWN);
		sTbtn->SetFrame({ 0, sTbtn->GetDirection() });
	}
	else if (key->isKeyUp(VK_LBUTTON)) {
		if (sTbtn == nullptr) return;
		if (sTbtn->GetDirection() != BTN_DOWN) return;

		switch (sTbtn->GetType())
		{
		case SBTN_PLUS:
			player->StatusUp(sTbtn->GetName());
			status->SetVName();
			break;
		}
		sTbtn->SetDirection(BTN_UP);
		sTbtn->SetFrame({ 0, sTbtn->GetDirection() });
		sTbtn = nullptr;
	}

}

void PlayController::BattleControl(void)
{
	if (!player->GetIsTurn()) return;
	CommandUI* command = ui->GetCommand();
	
	if (player->GetComType() != COM_DEFAULT) {
		if (key->isKeyDown(VK_LBUTTON)) {
			bTbtn = command->SelectBtn();
			if (bTbtn != nullptr) {
				bTbtn = nullptr;
				return;
			}
			player->GetAstar()->SeleteTarget();
		}
	}
}

void PlayController::BattleComControl(void)
{
	if (!player->GetIsTurn()) return;
	CommandUI* command = ui->GetCommand();

	if (key->StayKeyDown(VK_LBUTTON)) {
			bTbtn = command->SelectBtn();
		if (bTbtn == nullptr) return;
		if (bTbtn->GetSize().width != bTbtn->GetImg()->GetFrameWidth() &&
			bTbtn->GetSize().height != bTbtn->GetImg()->GetFrameHeight()) return;

		bTbtn->SetSize({ bTbtn->GetSize().width * 2.0f, bTbtn->GetSize().height * 2.0f });
	}
	else if (key->isKeyUp(VK_LBUTTON)) {
		if (bTbtn == nullptr) return;

		player->SetComType(bTbtn->GetType());

		bTbtn->SetSize({ bTbtn->GetImg()->GetFrameWidth(), bTbtn->GetImg()->GetFrameHeight() });
		bTbtn = nullptr;
	}

}

void PlayController::OptionControl(void)
{
	OptionUI* option = ui->GetOption();

	if (key->isKeyDown(VK_F3)) {
		isEdit = !isEdit;
		object->SetEditMode(isEdit);
		map->SetEditMode(isEdit);
	}

	if (key->isKeyDown(VK_ESCAPE))
	{
		option->OptionMove();
	}

	if (!MouseInRect(option->GetMenu()->GetRc())) return;

	if (key->StayKeyDown(VK_LBUTTON)) {
		oTbtn = option->SelectBtn();
		if (oTbtn == nullptr) return;
		oTbtn->SetDirection(BTN_DOWN);
		oTbtn->SetFrame({ 0, oTbtn->GetDirection() });
	}
	else if (key->isKeyUp(VK_LBUTTON)) {
		if (oTbtn == nullptr) return;
		if (oTbtn->GetDirection() != BTN_DOWN) return;

		switch (oTbtn->GetType())
		{
		case O_QUIT:
			data->SavePlayerPosition(player, data->LoadSlotNum().pos);
			data->SaveObjectPosition(object, FileSource("Resource", "World/Progress", "Object_Progress.txt"));
			_SCENE->ChangeScene("Title");
			_SOUND->Stop("WorldSpring");
			_SOUND->Stop("WorldSummer");
			_SOUND->Stop("WorldAutumn");
			_SOUND->Stop("WorldWinter");
			return;
			break;
		case O_CANCEL:
			option->OptionMove();
			break;
		}

		oTbtn->SetDirection(BTN_UP);
		oTbtn->SetFrame({ 0, oTbtn->GetDirection() });
		oTbtn = nullptr;
	}
}
