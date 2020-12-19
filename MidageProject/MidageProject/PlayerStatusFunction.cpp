#include "stdafx.h"
#include "PlayerStatus.h"
#include "Pannel.h"
#include "Button.h"
#include "Player.h"

void PlayerStatus::CreateMenu(void)
{
	Pannel* pannel = new Pannel;
	pannel->Init("Menu", { 0, 0 }, { 0,0 }, SPANNEL_MENU, UI_MENU, { 1, 2 });
	pannel->SetPos({ -pannel->GetSize().width * 0.5f, WINSIZEY * 0.5f });
	vPannel.push_back(pannel);
}

void PlayerStatus::CreateSlotMenu(void)
{
	Pannel* pannel = new Pannel;
	pannel->Init("Menu", { 0, 0 }, { 0,0 }, SPANNEL_MENU, UI_MENU, { 1, 2 });
	pannel->SetPos({ pannel->GetSize().width * 0.5f, WINSIZEY * 0.5f });
	vPannel.push_back(pannel);
}

void PlayerStatus::CreateNamePannel(void)
{
	D2D_POINT_2F pos = vPannel[0]->GetPos();
	pos.x -= vPannel[0]->GetSize().width * 0.5f - 35;
	pos.y -= vPannel[0]->GetSize().height * 0.5f - 25;
	string name[18] = { "NAME", "LEVEL", "EXP", "NEXTEXP", "HP", "MP", "ATK", "DEF", "SPD",
		"EARTH", "WATER", "FIRE", "WIND", "VIT", "STR", "STA", "DEX", "POINT" };

	for (int i = 0; i < 18; i++)
	{
		Pannel* pannel = new Pannel;
		pannel->Init("StatusPannel", pos, { 0,0 }, SPANNEL_DEFAULT, UI_MENU, { 0.75f, 0.5f });
		pannel->SetName(name[i]);
		vPannel.push_back(pannel);
		pos.y += pannel->GetSize().height * 0.5f + 10;

		nameRc tName;
		tName.name = SetVName(i);
		tName.rc = FRectMake(pannel->GetPos().x + pannel->GetSize().width * 0.5f + 10,
			pannel->GetPos().y - (pannel->GetSize().height * 0.5f), 120, 18);
		tName.isSelect = false;
		tName.isCull = false;
		vName.push_back(tName);
	}
}

void PlayerStatus::CreateEditButton(void)
{
	int num = 9;

	for (int i = 0; i < 8; i++)
	{
		vector<Button*> vTemp;
		for (int j = 0; j < 2; j++)
		{
			Button* btn = new Button;
			if (j % 2 == 0) {
				btn->Init("Minus", { vName[num + i].rc.left + 10, (vName[num + i].rc.top + vName[num + i].rc.bottom) * 0.5f }, 
					{ 0,0 }, SBTN_MINUS, UI_BUTTON, { 0.5f, 0.5f });
				btn->SetName(vPannel[num + i + 1]->GetName());
			}
			else {
				btn->Init("Plus", { vName[num + i].rc.right - 10, (vName[num + i].rc.top + vName[num + i].rc.bottom) * 0.5f },
					{ 0,0 }, SBTN_PLUS, UI_BUTTON, { 0.5f, 0.5f });
				btn->SetName(vPannel[num + i + 1]->GetName());
			}
			vTemp.push_back(btn);
		}
		vBtn.push_back(vTemp);
		vTemp.clear();
	}
}

void PlayerStatus::CreatePlayButton(void)
{
	int num = 13;

	for (int i = 0; i < 4; i++)
	{
		vector<Button*> vTemp;
		for (int j = 0; j < 1; j++)
		{
			Button* btn = new Button;
			btn->Init("Plus", { vName[num + i].rc.right - 10, (vName[num + i].rc.top + vName[num + i].rc.bottom) * 0.5f },
				{ 0,0 }, SBTN_PLUS, UI_BUTTON, { 0.5f, 0.5f });
			btn->SetName(vPannel[num + i + 1]->GetName());
			vTemp.push_back(btn);
		}
		vBtn.push_back(vTemp);
		vTemp.clear();
	}
}

void PlayerStatus::CreateFunButton(void)
{
	vector<Button*> vTemp;
	float offset;

	for (int i = 0; i < 2; i++)
	{
		Button* btn = new Button;
		btn->Init("DataButton", { WINSIZEX * 0.5f, WINSIZEY }, { 0,0 }, i, UI_BUTTON, { 2,2 });

		offset = btn->GetSize().width;
		if (i % 2 == 0) offset = -offset;

		btn->SetPos({ btn->GetPos().x + offset, btn->GetPos().y - btn->GetSize().height * 0.5f });
		if (i % 2 == 0) {
			btn->SetName("OK");
		}
		else btn->SetName("INIT");
		
		vTemp.push_back(btn);
	}
	vBtn.push_back(vTemp);
	vTemp.clear();
}

void PlayerStatus::CreatePointBar(void)
{
	for (int i = 0; i < 4; i++)
	{
		D2D_POINT_2F pos;
		pos.x = vName[i + 9].rc.left + 20;
		pos.y = vName[i + 9].rc.top;
		D2D_SIZE_F size;
		size.width = (vName[i + 9].rc.right - vName[i + 9].rc.left - 40) / 10;
		size.height = vName[i + 9].rc.bottom - vName[i + 9].rc.top;

		vector<nameRc> vTemp;
		for (int j = 0; j < 10; j++)
		{
			nameRc temp;
			temp.name = "";
			temp.rc = FRectMake(pos.x, pos.y, size.width, size.height);
			temp.isSelect = false;
			temp.isCull = false;
			vTemp.push_back(temp);
			pos.x += size.width;
		}
		vPointBar.push_back(vTemp);
		vTemp.clear();
	}
}

string PlayerStatus::SetVName(int index)
{
	string name;
	switch (index)
	{
	case 0:
		name = player->GetName();
		break;
	case 1:
		name = to_string(player->GetLv());
		break;
	case 2:
		name = to_string(player->GetExp());
		break;
	case 3:
		name = to_string(player->GetMaxExp());
		break;
	case 4:
		name = to_string(player->GetHp()) + " / " + to_string(player->GetMaxHp());
		break;
	case 5:
		name = to_string(player->GetMp()) + " / " + to_string(player->GetMaxMp());
		break;
	case 6:
		name = to_string(player->GetAtk());
		break;
	case 7:
		name = to_string(player->GetDef());
		break;
	case 8:
		name = to_string(player->GetSpd());
		break;
	//case 9:
	//	name = to_string(player->GetEarthPoint());
	//	break;
	//case 10:
	//	name = to_string(player->GetWaterPoint());
	//	break;
	//case 11:
	//	name = to_string(player->GetFirePoint());
	//	break;
	//case 12:
	//	name = to_string(player->GetWindPoint());
	//	break;
	case 13:
		name = to_string(player->GetVital());
		break;
	case 14:
		name = to_string(player->GetStrength());
		break;
	case 15:
		name = to_string(player->GetStamin());
		break;
	case 16:
		name = to_string(player->GetDexterity());
		break;
	case 17:
		name = to_string(player->GetStatPoint());
		break;
	}

	return name;
}

void PlayerStatus::SetVName(void)
{
	for (int i = 4; i < 18; i++)
	{
		vName[i].name = SetVName(i);
	}
}

void PlayerStatus::PointBarInit(void)
{
	for (UINT y = 0; y < vPointBar.size(); y++)
	{
		for (UINT x = 0; x < vPointBar[y].size(); x++)
		{
			vPointBar[y][x].isSelect = false;
		}
	}
}

void PlayerStatus::SetPointBar(void)
{
	int point;
	int x;

	for (UINT y = 0; y < vPointBar.size(); y++)
	{
		switch (y)
		{
		case 0:
			x = 0;
			point = player->GetEarthPoint();
			while (true) {
				if (point <= x) break;
				vPointBar[y][x].isSelect = true;
				x++;
			}
			break;
		case 1:
			x = 0;
			point = player->GetWaterPoint();
			while (true) {
				if (point <= x) break;
				vPointBar[y][x].isSelect = true;
				x++;
			}
			break;
		case 2:
			x = 0;
			point = player->GetFirePoint();
			while (true) {
				if (point <= x) break;
				vPointBar[y][x].isSelect = true;
				x++;
			}
			break;
		case 3:
			x = 0;
			point = player->GetWindPoint();
			while (true) {
				if (point <= x) break;
				vPointBar[y][x].isSelect = true;
				x++;
			}
			break;
		}
	}
}

void PlayerStatus::SetPointBar(int type)
{
	for (UINT y = 0; y < vPointBar.size(); y++)
	{
		switch (type)
		{
		case SBTN_MINUS:
			SetPointBar(SBTN_MINUS, y);
			break;
		case SBTN_PLUS:
			SetPointBar(SBTN_PLUS, y);
			break;
		}
	}
}

void PlayerStatus::SetPointBar(int type, int properPoint)
{
	int point = 0;
	switch (type)
	{
	case SBTN_MINUS:
		switch (properPoint)
		{
		case S_EARTH:
			point = player->GetEarthPoint();
			vPointBar[properPoint][point].isSelect = false;
			break;
		case S_WATER:
			point = player->GetWaterPoint();
			vPointBar[properPoint][point].isSelect = false;
			break;
		case S_FIRE:
			point = player->GetFirePoint();
			vPointBar[properPoint][point].isSelect = false;
			break;
		case S_WIND:
			point = player->GetWindPoint();
			vPointBar[properPoint][point].isSelect = false;
			break;
		}
		break;
	case SBTN_PLUS:
		switch (properPoint)
		{
		case S_EARTH:
			point = player->GetEarthPoint() - 1;
			if (point < 0) return;
			vPointBar[properPoint][point].isSelect = true;
			break;
		case S_WATER:
			point = player->GetWaterPoint() - 1;
			if (point < 0) return;
			vPointBar[properPoint][point].isSelect = true;
			break;
		case S_FIRE:
			point = player->GetFirePoint() - 1;
			if (point < 0) return;
			vPointBar[properPoint][point].isSelect = true;
			break;
		case S_WIND:
			point = player->GetWindPoint() - 1;
			if (point < 0) return;
			vPointBar[properPoint][point].isSelect = true;
			break;
		}
		break;
	}
	
}
