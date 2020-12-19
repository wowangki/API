#include "stdafx.h"
#include "EditUI.h"
#include "EditBtnManager.h"
#include "Palette.h"
#include "Pannel.h"

EditUI::EditUI()
{
}


EditUI::~EditUI()
{
}

HRESULT EditUI::Init(void)
{
	menu = new Pannel;
	menu->Init("Menu", { 0, 0 }, { 0,0 }, NULL, UI_MENU, { 1.0f, 1.0f });
	menu->SetPos({ WINSIZEX / 2, WINSIZEY - menu->GetSize().height * 0.5f });
	btn = new EditBtnManager;
	btn->Init(menu);
	palette = new Palette;
	palette->Init(menu);

	return S_OK;
}

void EditUI::Release(void)
{
	menu->Release();
	btn->Releas();
	palette->Release();
}

void EditUI::Update(void)
{
	menu->Update();
	btn->Update();
	palette->Update(btn->SelectButton());

	rc = FRectMakeCenter(menu->GetPos().x, menu->GetPos().y,
		menu->GetSize().width + (btn->GetBtn(EBTN_SEASON)->GetSize().width * 2.0f),
		menu->GetSize().height + (btn->GetBtn(EBTN_HIDE)->GetSize().height * 2.0f));
}

void EditUI::Render(void)
{
	menu->Render();
	btn->Render();
	palette->Render();
}
