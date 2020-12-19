#include "stdafx.h"
#include "OptionUI.h"
#include "Pannel.h"
#include "Button.h"

OptionUI::OptionUI()
{
}


OptionUI::~OptionUI()
{
}

HRESULT OptionUI::Init(void)
{
	pannel = new Pannel;
	pannel->Init("Menu", { 0,0 }, { 0,0 }, 0, UI_MENU, { 1.0f, 0.5f });
	pannel->SetPos({ WINSIZEX - pannel->GetSize().width * 0.5f, -pannel->GetSize().height * 0.5f });
	
	message.size.width = pannel->GetSize().width;
	message.size.height = pannel->GetSize().height;
	message.isCull = false;

	D2D_POINT_2F pos;
	int minus = -1;
	pos = pannel->GetPos();
	for (int i = 0; i < 2; i++)
	{
		btn[i] = new Button;
		btn[i]->Init("DataButton", { 0, 0 }, { 0,0 }, i, UI_BUTTON);
		btn[i]->SetPos({ pos.x + (btn[i]->GetSize().width * minus), pos.y });

		if (i % 2 == 0)
			btn[i]->SetName("OK");
		else btn[i]->SetName("CANCEL");

		minus = -minus;
	}

	return S_OK;
}

void OptionUI::Release(void)
{
	SafeRelease(pannel);
	for (int i = 0; i < 2; i++)
	{
		SafeRelease(btn[i]);
	}
}

void OptionUI::Update(void)
{
	pannel->Update();
	message.rc = FRectMakeCenter(pannel->GetPos().x , pannel->GetPos().y + 10, message.size.width, message.size.height);
	message.isCull = UIIsWindowOut(message.rc);

	for (int i = 0; i < 2; i++)
	{
		btn[i]->Update();
	}
}

void OptionUI::Render(void)
{
	pannel->Render();

	for (int i = 0; i < 2; i++)
	{
		btn[i]->UnNameRender();
		_FONT->Render(btn[i]->GetName(), btn[i]->GetRc(), _BRUSH->GetBrush("BLACK"), "BTNNAME");
	}

	if (message.isCull) return;
	_FONT->Render("Are you save and quit this game?", message.rc, _BRUSH->GetBrush("BLACK"), "STATUS");
}

void OptionUI::OptionMove(void)
{
	float moveQuantity = pannel->GetSize().height + 1;

	if (pannel->GetIsCull()) {
		pannel->SetMovePos(0, moveQuantity);

		for (int i = 0; i < 2; i++)
		{
			btn[i]->SetMovePos(0, moveQuantity);
		}
	}
	else {
		pannel->SetMovePos(0, -moveQuantity);

		for (int i = 0; i < 2; i++)
		{
			btn[i]->SetMovePos(0, -moveQuantity);
		}
	}
}

Button * OptionUI::SelectBtn(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (MouseInRect(btn[i]->GetRc()))
			return btn[i];
	}
	return nullptr;
}
