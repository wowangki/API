#include "stdafx.h"
#include "CommandUI.h"
#include "Button.h"
#include "Player.h"

CommandUI::CommandUI(Player* player)
{
	this->player = player;
}


CommandUI::~CommandUI()
{
}

HRESULT CommandUI::Init(void)
{
	CreateCommandBtn();

	return S_OK;
}

void CommandUI::Release(void)
{
	for (UINT i = 0; i < vBtn.size(); i++)
	{
		SafeRelease(vBtn[i]);
	}
	vBtn.clear();
}

void CommandUI::Update(void)
{
	if (!player->GetIsTurn()) return;

	D2D_POINT_2F pos[5];
	pos[0].x = player->GetPos().x + _CAM->x;
	pos[0].y = player->GetPos().y + _CAM->y - 10;
	pos[1].x = player->GetPos().x - player->GetSize().width * 0.5f + _CAM->x;
	pos[1].y = player->GetPos().y - player->GetSize().height * 0.5f + _CAM->y - 10;
	pos[2].x = player->GetPos().x + player->GetSize().width * 0.5f + _CAM->x;
	pos[2].y = player->GetPos().y - player->GetSize().height * 0.5f + _CAM->y - 10;
	pos[3].x = player->GetPos().x - player->GetSize().width * 0.5f + _CAM->x;
	pos[3].y = player->GetPos().y + player->GetSize().height * 0.5f + _CAM->y - 10;
	pos[4].x = player->GetPos().x + player->GetSize().width * 0.5f + _CAM->x;
	pos[4].y = player->GetPos().y + player->GetSize().height * 0.5f + _CAM->y - 10;

	for (UINT i = 0; i < vBtn.size(); i++)
	{
		vBtn[i]->Update();
		if (!MouseInRect(vBtn[i]->GetRc())) {
			vBtn[i]->SetSize({ vBtn[i]->GetImg()->GetFrameWidth(), vBtn[i]->GetImg()->GetFrameHeight() });
		}
		vBtn[i]->SetPos(pos[i]);
	}
}

void CommandUI::Render(void)
{
	if (!player->GetIsTurn()) return;

	if (player->GetComType() == COM_DEFAULT) {
		for (UINT i = 1; i < vBtn.size(); i++)
		{
			vBtn[i]->UnNameRender();
		}
	} else vBtn[COM_DEFAULT]->UnNameRender();
	
}

void CommandUI::CreateCommandBtn(void)
{
	string tStr[5] = { "Battle_Cancel", "Battle_Attack_Normal", "Battle_Attack_Strong", "Battle_Guard", "Battle_Avoid" };

	for (int i = 0; i < 5; i++)
	{
		Button* btn = new Button;
		btn->Init(tStr[i], { 0,0 }, { 0,0 }, i, UI_BUTTON);
		vBtn.push_back(btn);
	}
}

Button * CommandUI::SelectBtn(void)
{
	for (UINT i = 0; i < vBtn.size(); i++)
	{
		if (MouseInRect(vBtn[i]->GetRc())) {
			return vBtn[i];
		}
	}

	return nullptr;
}
