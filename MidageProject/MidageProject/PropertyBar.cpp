#include "stdafx.h"
#include "PropertyBar.h"
#include "Actor.h"

PropertyBar::PropertyBar(class Actor* actor)
	:actor(actor)
{
}


PropertyBar::~PropertyBar()
{
}

HRESULT PropertyBar::Init(void)
{
	totalHp = (float)actor->GetMaxHp();
	presentHp = (float)actor->GetHp();

	hpPersent = presentHp / totalHp;

	totalHpBar.size = { 40.0f, 10.0f };
	totalHpBar.pos = actor->GetRymPos()[2];
	totalHpBar.pos.y += totalHpBar.size.height * 0.5f;

	float destHpBarSize = ((1 - hpPersent) * totalHpBar.size.width);
	hpBar.size = { destHpBarSize, 10.0f };
	hpBar.pos.x = totalHpBar.pos.x - totalHpBar.size.width * 0.5f;
	hpBar.pos.y = totalHpBar.pos.y - totalHpBar.size.height * 0.5f;
	hpBar.progress = false;
	moveSpeed = 0.0f;
	return S_OK;
}

void PropertyBar::Release(void)
{
}

void PropertyBar::Update(void)
{
	HpBarMove();
	totalHpBar.pos = actor->GetRymPos()[2];
	totalHpBar.pos.y += totalHpBar.size.height * 0.5f;
	hpBar.pos.x = totalHpBar.pos.x - totalHpBar.size.width * 0.5f;
	hpBar.pos.y = totalHpBar.pos.y - totalHpBar.size.height * 0.5f;
	totalHpBar.rc = FRectMakeCenter(totalHpBar.pos.x + _CAM->x, totalHpBar.pos.y + _CAM->y, totalHpBar.size.width, totalHpBar.size.height);
	hpBar.rc = FRectMake(hpBar.pos.x + _CAM->x, hpBar.pos.y + _CAM->y, hpBar.size.width, hpBar.size.height);
}

void PropertyBar::Render(void)
{
	if (!hpBar.progress) return;
	_RenderTarget->FillRectangle(totalHpBar.rc, _BRUSH->GetBrush("GREEN"));
	_RenderTarget->FillRectangle(hpBar.rc, _BRUSH->GetBrush("RED"));
	
	WCHAR hpString[256];
	static TCHAR hpText[] = L"%d / %d";
	_stprintf_s(hpString, hpText, actor->GetHp(), actor->GetMaxHp());
	_FONT->Render(hpString, totalHpBar.rc, _BRUSH->GetBrush("BLACK"), "Hp");
}

void PropertyBar::HpBarMove(void)
{
	totalHp = (float)actor->GetMaxHp();
	presentHp = (float)actor->GetHp();

	hpPersent = presentHp / totalHp;

	float destHpBarSize = ((1 - hpPersent) * totalHpBar.size.width);

	if (moveSpeed == 0)	moveSpeed = destHpBarSize / 60.0f;

	if (hpBar.size.width < destHpBarSize) {
		hpBar.size.width += moveSpeed;
		hpBar.progress = true;
	}
	else {
		hpBar.progress = false;
		moveSpeed = 0.0f;
	}
	
}
