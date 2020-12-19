#include "stdafx.h"
#include "PrograssBar.h"


PrograssBar::PrograssBar()
{
}


PrograssBar::~PrograssBar()
{
}

HRESULT PrograssBar::Init(void)
{
	total.pos.x = WINSIZEX / 2;
	total.pos.y = WINSIZEY;
	total.size.width = 800.0f;
	total.size.height = 20.0f;
	total.rc = FRectMakeCenter(total.pos.x, total.pos.y - total.size.height * 0.5f, total.size.width, total.size.height);
	total.progress = 100;
	progress.pos = total.pos;
	progress.size.width = 0.0f;
	progress.size.height = 20.0f;
	progress.rc = FRectMakeCenter(progress.pos.x, progress.pos.y - total.size.height * 0.5f, progress.size.width, progress.size.height);
	progress.progress = 0;

	isComplete = false;
	_BRUSH->CreateBrush("GREEN", RGB(0, 255, 0));
	return S_OK;
}

void PrograssBar::Release(void)
{
}

void PrograssBar::Update(void)
{
	progress.size.width = progress.progress * 8;

	progress.rc = FRectMakeCenter(progress.pos.x, progress.pos.y - total.size.height * 0.5f, progress.size.width, progress.size.height);

	if (progress.progress >= total.progress) isComplete = true;
}

void PrograssBar::Render(void)
{
	_RenderTarget->FillRectangle(total.rc, _Device->pDefaultBrush);
	_RenderTarget->FillRectangle(progress.rc, _BRUSH->GetBrush("GREEN"));
}
