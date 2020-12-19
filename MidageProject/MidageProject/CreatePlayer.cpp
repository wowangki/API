#include "stdafx.h"
#include "CreatePlayer.h"
#include "Player.h"
#include "PlayerStatus.h"
#include "KeyModule.h"
#include "Button.h"
#include "Data.h"
#include "PlayerSelect.h"

CreatePlayer::CreatePlayer(PlayerSelect* select)
{
	this->select = select;
}


CreatePlayer::~CreatePlayer()
{
}

HRESULT CreatePlayer::Init(void)
{
	player = new Player;
	status = new PlayerStatus(player);
	key = new KeyModule;
	data = select->GetData();

	player->PaletteInit({ WINSIZEX * 0.5f, WINSIZEY * 0.5f }, { 0,0 }, PLAYER_MALE);
	player->SetSize({ player->GetImg()->GetFrameWidth() * 2.0f, player->GetImg()->GetFrameHeight() * 2.0f });
	player->StatusInit(0, 0, 0, 0);
	player->SetProperty(0, 0, 0, 0);

	status->CreateInit();
	tBtn = nullptr;
	return S_OK;
}

void CreatePlayer::Release(void)
{
	SafeDeleteClass(player);
	SafeDeleteClass(status);
}

void CreatePlayer::Update(int slotNum)
{
	string posFileName = FileSource("Resource", "Player", "Player_slot" + to_string(slotNum) + "_Pos.txt");
	string propertyFileName = FileSource("Resource", "Player", "Player_slot" + to_string(slotNum) + "_Property.txt");
	status->Update();

	if (key->isKeyDown(VK_LBUTTON)) {
		tBtn = status->SelectButton();
		if (tBtn == nullptr) return;
		tBtn->SetDirection(BTN_DOWN);
		tBtn->SetFrame({ 0,tBtn->GetDirection() });
	}
	else if (key->isKeyUp(VK_LBUTTON)) {
		if (tBtn == nullptr) return;
		if (tBtn->GetDirection() != BTN_DOWN) return;

		switch (tBtn->GetType())
		{
		case SBTN_OK:
			if (player->GetStatPoint() != 0 || player->GetPropertyPoint() != 0) break;
			player->SetWorldInfoNum(5);
			player->SetWorldInfoName("World5");
			data->LoadPlayerInitPosition(player);
			data->SavePlayerPosition(player, posFileName);
			data->SavePlayerProperty(player, propertyFileName);
			select->SetPlayerSlot(player, slotNum);
			player->StatusInit(0, 0, 0, 0);
			player->SetProperty(0, 0, 0, 0);
			status->PointBarInit();
			status->SetVName();
			select->SetIsSelect(false);
			break;
		case SBTN_INIT:
			player->StatusInit(0, 0, 0, 0);
			player->SetProperty(0, 0, 0, 0);
			status->PointBarInit();
			status->SetVName();
			break;
		case SBTN_MINUS:
			player->StatusDown(tBtn->GetName());
			status->SetPointBar(SBTN_MINUS);
			status->SetVName();
			break;

		case SBTN_PLUS:
			player->StatusUp(tBtn->GetName());
			status->SetPointBar(SBTN_PLUS);
			status->SetVName();
			break;
		}
		

		tBtn->SetDirection(BTN_UP);
		tBtn->SetFrame({ 0,tBtn->GetDirection() });
		tBtn = nullptr;
	}
}

void CreatePlayer::Render(void)
{
	player->PaletteRender();
	status->Render();
}
