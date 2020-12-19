#include "stdafx.h"
#include "EditBtnManager.h"
#include "Pannel.h"

EditBtnManager::EditBtnManager()
{
}


EditBtnManager::~EditBtnManager()
{
}

HRESULT EditBtnManager::Init(Pannel* menu)
{
	D2D_POINT_2F tPos;
	tPos.x = 0;
	tPos.y = 0;
	//ÁÂÃø - PALETTE BTN
	for (int i = 0; i <= EBTN_BULIDING; i++)
	{
		Button* eBtn = new Button;
		eBtn->Init("DataButton", tPos, { 0,0 }, i, UI_BUTTON);
		SetName(eBtn, eBtn->GetType());
		tPos.x = menu->GetPos().x - (menu->GetSize().width * 0.5f) - (eBtn->GetSize().width * 0.5f);
		if(i == 0) tPos.y = menu->GetPos().y - (menu->GetSize().height * 0.5f) + (eBtn->GetSize().height * 0.5f);
		eBtn->SetPos(tPos);
		vUI.push_back(eBtn);
		tPos.y += eBtn->GetSize().height;
	}

	// Áß¾Ó
	for (int i = EBTN_HIDE; i <= EBTN_HIDE; i++)
	{
		Button * eBtn = new Button;
		eBtn->Init("DataButton", tPos, { 0,0 }, i, UI_BUTTON);
		SetName(eBtn, eBtn->GetType());
		tPos.x = menu->GetPos().x;
		tPos.y = menu->GetPos().y - (menu->GetSize().height * 0.5f) - (eBtn->GetSize().height * 0.5f);
		eBtn->SetPos(tPos);
		vUI.push_back(eBtn);
	}

	//¿ìÃø - MAP & DATA BTN
	for (int i = EBTN_SIZEUP; i <= EBTN_EXIT; i++)
	{
		Button* eBtn = new Button;
		eBtn->Init("DataButton", tPos, { 0,0 }, i, UI_BUTTON);
		SetName(eBtn, eBtn->GetType());
		tPos.x = menu->GetPos().x + (menu->GetSize().width * 0.5f) + (eBtn->GetSize().width * 0.5f);
		if (i == EBTN_SIZEUP) tPos.y = menu->GetPos().y - (menu->GetSize().height * 0.5f) + (eBtn->GetSize().height * 0.5f);
		eBtn->SetPos(tPos);
		vUI.push_back(eBtn);
		tPos.y += eBtn->GetSize().height;
	}

	return S_OK;
}

void EditBtnManager::Releas(void)
{
	for (UINT i = 0; i < vUI.size(); i++)
	{
		SafeRelease(vUI[i]);
	}
	vUI.clear();
}

void EditBtnManager::Update(void)
{
	for (UINT i = 0; i < vUI.size(); i++)
	{
		vUI[i]->Update();
	}
}

void EditBtnManager::Render(void)
{
	for (UINT i = 0; i < vUI.size(); i++)
	{
		vUI[i]->Render();
	}
}

Button * EditBtnManager::SelectButton(void)
{
	for (UINT i = 0; i < vUI.size(); i++)
	{
		if (vUI[i]->GetKind() != UI_BUTTON) continue;
		
		if (MouseInRect(vUI[i]->GetRc())) {
			return vUI[i];
		}
	}
	return nullptr;
}

void EditBtnManager::SetMovePos(float x, float y)
{
	for (UINT i = 0; i < vUI.size(); i++)
	{
		vUI[i]->SetMovePos(x, y);
	}
}

void EditBtnManager::SetName(Button* button, int type)
{
	switch (type) {
	case EBTN_SEASON:
		button->SetName("SEASON");
		break;
	case EBTN_NONSEASON:
		button->SetName("NONSEASON");
		break;
	case EBTN_MAPOBJECT:
		button->SetName("MAPOBJECT");
		break;
	case EBTN_PLAYER:
		button->SetName("PLAYER");
		break;
	case EBTN_BEAST:
		button->SetName("BEAST");
		break;
	case EBTN_DEMON:
		button->SetName("DEMON");
		break;
	case EBTN_HUMAN:
		button->SetName("HUMAN");
		break;
	case EBTN_DRAGON:
		button->SetName("DRAGON");
		break;
	case EBTN_BULIDING:
		button->SetName("BULDING");
		break;
	case EBTN_HIDE:
		button->SetName("HIDE");
		break;
	case EBTN_SIZEUP:
		button->SetName("SIZEUP");
		break;
	case EBTN_SIZEDOWN:
		button->SetName("SIZEDOWN");
		break;
	case EBTN_SAVE:
		button->SetName("SAVE");
		break;
	case EBTN_LOAD:
		button->SetName("LOAD");
		break;
	case EBTN_EXIT:
		button->SetName("EXIT");
		break;
	}
}

