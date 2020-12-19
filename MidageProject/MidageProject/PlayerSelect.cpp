#include "stdafx.h"
#include "PlayerSelect.h"
#include "Player.h"
#include "PlayerStatus.h"
#include "Button.h"
#include "KeyModule.h"
#include "CreatePlayer.h"
#include "Data.h"

PlayerSelect::PlayerSelect()
{
}


PlayerSelect::~PlayerSelect()
{
}

HRESULT PlayerSelect::Init(void)
{
	background = _IMAGE->FindImage("TitleBackGround");
	data = new Data;

	D2D_POINT_2F pos;
	pos.x = WINSIZEX * 0.5f;
	pos.y = WINSIZEY * 0.5f;
	for (int i = 0; i < 3; i++)
	{
		slot[i].rc = FRectMakeCenter(pos.x, pos.y + (100 * (i - 1)) + (10 * i), 400, 100);
		slot[i].imgRc = FRectMakeCenter(pos.x - 150, pos.y + (100 * (i - 1)) + (10 * i), 60, 80);

		for (int j = 0; j < 5; j++)
		{
			slot[i].statusRc[j] = FRectMakeCenter(pos.x - 50, pos.y + (100 * (i - 1)) + (10 * i) + (20 * (j - 2)), 100, 20);
		}

		for (int j = 5; j < 9; j++)
		{
			slot[i].statusRc[j] = FRectMakeCenter(pos.x + 100, pos.y + (100 * (i - 1)) + (10 * i) + (20 * (j - 7)), 100, 20);
		}

		if (data->isExist(FileSource("Resource", "Player", "Player_slot" + to_string(i) + "_Property.txt"))) {
			Player* tPlayer = new Player;
			tPlayer->PaletteInit({ 0,0 }, { 0,0 }, 0);
			data->LoadPlayerProperty(tPlayer, FileSource("Resource", "Player", "Player_slot" + to_string(i) + "_Property.txt"));
			SetPlayerSlot(tPlayer, i);
		}
		else {
			slot[i].player = nullptr;
			slot[i].btn = nullptr;
		}
	}

	btn = new Button;
	btn->Init("DataButton", { WINSIZEX * 0.5f, WINSIZEY }, { 0,0 }, 0, UI_BUTTON, { 2,2 });
	btn->SetPos({ btn->GetPos().x, btn->GetPos().y - btn->GetSize().height * 0.5f });
	btn->SetName("");
	key = new KeyModule;

	create = new CreatePlayer(this);
	create->Init();

	isSelect = false;
	slotNum = 0;

	return S_OK;
}

void PlayerSelect::Release(void)
{
	for (int i = 0; i < 3; i++)
	{
		SafeRelease(slot[i].player);
		SafeRelease(slot[i].btn);
	}
	SafeDelete(data);
}

void PlayerSelect::Update(void)
{
	btn->Update();
	
	for (int i = 0; i < 3; i++)
	{
		if (slot[i].btn != nullptr)
		slot[i].btn->Update();
	}

	if (isSelect)
		create->Update(slotNum);

	if (key->StayKeyDown(VK_LBUTTON)) {
		if (MouseInRect(btn->GetRc())) {
			btn->SetDirection(BTN_DOWN);
			btn->SetFrame( { 0, btn->GetDirection() } );
		}
		else {
			if (!isSelect) {
				for (int i = 0; i < 3; i++)
				{
					if (slot[i].player != nullptr)
					{
						if (MouseInRect(slot[i].btn->GetRc())) {
							slot[i].btn->SetDirection(BTN_DOWN);
							slot[i].btn->SetFrame({ 0, slot[i].btn->GetDirection() });
							break;
						}
						else if (MouseInRect(slot[i].rc)) {
							data->SaveSlotNum(i);
							_SCENE->ChangeScene(slot[i].player->GetWorldInfoName());
							_SOUND->Stop("TitleBackground");
							return;
						}
					}
					else {
						if (MouseInRect(slot[i].rc)) {
							isSelect = true;
							slotNum = i;
							break;
						}
					}
				}
			}
		}
	}

	if (key->isKeyUp(VK_LBUTTON)) {

		for (int i = 0; i < 3; i++)
		{
			if (slot[i].btn == nullptr) continue;
			if (slot[i].btn->GetDirection() != BTN_DOWN) continue;
			data->DeletePlayer(i);
			create->GetPlayer()->StatusInit(0, 0, 0, 0);
			create->GetPlayer()->SetProperty(0, 0, 0, 0);
			create->GetStatus()->PointBarInit();
			slot[i].player = nullptr;
			slot[i].btn->SetDirection(BTN_UP);
			slot[i].btn->SetFrame({ 0, slot[i].btn->GetDirection() });
			break;
		}

		if (!isSelect) {
			if (btn->GetDirection() != BTN_DOWN) return;
			_SCENE->ChangeScene("Title");
		}
		else {
			if (btn->GetDirection() != BTN_DOWN) return;
			isSelect = false;
			create->GetPlayer()->StatusInit(0, 0, 0, 0);
			create->GetPlayer()->SetProperty(0, 0, 0, 0);
			create->GetStatus()->PointBarInit();
			create->GetStatus()->SetVName();
		}

		btn->SetDirection(BTN_UP);
		btn->SetFrame({ 0, btn->GetDirection() });
	}
}

void PlayerSelect::Render(void)
{
	background->FrameRender(0, 0, 0, 0, WINSIZEX, WINSIZEY);

	if (!isSelect) {
		SlotRender();
	}
	else create->Render();

	btn->UnNameRender();
	_FONT->Render("BACK", btn->GetRc(), _BRUSH->GetBrush("BLACK"), "STATUS");
}

void PlayerSelect::SlotRender(void)
{
	string status[9] = { "NAME : ", "LEVEL : ", "EXP : ", "HP : ", "MP : ", "VIT : ", "STR : ", "STA : ", "DEX : " };

	for (int i = 0; i < 3; i++)
	{
		_RenderTarget->FillRectangle(slot[i].rc, _Device->pDefaultBrush);

		if (MouseInRect(slot[i].rc)) {
			_RenderTarget->DrawRectangle(slot[i].rc, _BRUSH->GetBrush("YELLOW"));
		}
		else {
			_RenderTarget->DrawRectangle(slot[i].rc, _BRUSH->GetBrush("BLACK"));
		}
		
		_RenderTarget->DrawRectangle(slot[i].imgRc, _BRUSH->GetBrush("BLACK"));

		if (slot[i].player == nullptr) {
			for (int j = 0; j < 9; j++)
			{
				_FONT->Render(status[j], slot[i].statusRc[j], _BRUSH->GetBrush("BLACK"));
			}
		}
		else
		{
			slot[i].player->GetImg()->FrameRender(slot[i].imgRc.left, slot[i].imgRc.top, 0, 0,
				slot[i].imgRc.right - slot[i].imgRc.left, slot[i].imgRc.bottom - slot[i].imgRc.top);

			for (int j = 0; j < 9; j++)
			{
				_FONT->Render(status[j] + slot[i].playerStatus[j], slot[i].statusRc[j], _BRUSH->GetBrush("BLACK"));
			}

			slot[i].btn->UnNameRender();
			_FONT->Render(slot[i].btn->GetName(), slot[i].btn->GetRc(), _BRUSH->GetBrush("BLACK"), "SELECT");
		}
		
	}
}

void PlayerSelect::SetPlayerSlot(Player * player, int num)
{
	slot[num].player = player;
	slot[num].playerStatus[0] = player->GetName();
	slot[num].playerStatus[1] = to_string(player->GetLv());
	slot[num].playerStatus[2] = to_string(player->GetExp()) + " / " + to_string(player->GetMaxExp());
	slot[num].playerStatus[3] = to_string(player->GetHp()) + " / " + to_string(player->GetMaxHp());
	slot[num].playerStatus[4] = to_string(player->GetMp()) + " / " + to_string(player->GetMaxMp());
	slot[num].playerStatus[5] = to_string(player->GetVital());
	slot[num].playerStatus[6] = to_string(player->GetStrength());
	slot[num].playerStatus[7] = to_string(player->GetStamin());
	slot[num].playerStatus[8] = to_string(player->GetDexterity());

	slot[num].btn = new Button;
	slot[num].btn->Init("DataButton", { 0,0 }, { 0,0 }, 0, UI_BUTTON);
	slot[num].btn->SetName("DELETE");
	
	D2D_POINT_2F pos;
	pos.x = slot[num].rc.right - slot[num].btn->GetSize().width * 0.5f;
	pos.y = slot[num].rc.top + slot[num].btn->GetSize().height * 0.5f;
	slot[num].btn->SetPos(pos);
}
