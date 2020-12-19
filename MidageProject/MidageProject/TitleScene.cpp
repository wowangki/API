#include "stdafx.h"
#include "TitleScene.h"
#include "PlayerSelect.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

HRESULT TitleScene::Init(void)
{
	_CAM->x = 0;
	_CAM->y = 0;
	background = _IMAGE->FindImage("TitleBackGround");
	
	for (int i = 0; i < 4; i++)
	{
		switch (i) {
		case 0:
			btn[i].name = "TitleName";
			btn[i].img = _IMAGE->FindImage(btn[i].name);
			btn[i].pos = { WINSIZEX / 2, WINSIZEY / 3 };
			break;
		case 1:
			btn[i].name = "TitleNewGame";
			btn[i].img = _IMAGE->FindImage(btn[i].name);
			btn[i].pos = { WINSIZEX / 2, btn[i-1].pos.y + 100 };
			break;
		case 2:
			btn[i].name = "TitleEditGame";
			btn[i].img = _IMAGE->FindImage(btn[i].name);
			btn[i].pos = { WINSIZEX / 2, btn[i - 1].pos.y + 50 };
			break;
		case 3:
			btn[i].name = "TitleOption";
			btn[i].img = _IMAGE->FindImage(btn[i].name);
			btn[i].pos = { WINSIZEX / 2, btn[i - 1].pos.y + 50 };
			break;
		}

		btn[i].frame = { 0,0 };
		btn[i].rc = FRectMakeCenter(btn[i].pos.x, btn[i].pos.y, btn[i].img->GetFrameWidth(), btn[i].img->GetFrameHeight());
	}

	selectIndex = 1;

	key = new KeyModule;

	_SOUND->SetEffectVolume(0.5f);
	if (!_SOUND->isPlay("TitleBackground")) _SOUND->Play("TitleBackground");
	return S_OK;
}

void TitleScene::Release(void)
{
	
}

void TitleScene::Update(void)
{
	selectRc = FRectMakeCenter(btn[selectIndex].pos.x, btn[selectIndex].pos.y, 
		btn[selectIndex].img->GetFrameWidth(), btn[selectIndex].img->GetFrameHeight());

	for (int i = 0; i < 4; i++)
	{
		if (IsInRect(btn[i].rc, selectRc)) {
			btn[i].frame.y = 1;
		}
		else btn[i].frame.y = 0;
	}

	SelectBtn();
}

void TitleScene::Render(void)
{
	background->FrameRender(0, 0, 0, 0, WINSIZEX, WINSIZEY);
	for (int i = 0; i < 4; i++)
	{
		btn[i].img->CUiFrameRender(btn[i].pos.x, btn[i].pos.y, btn[i].frame.x, btn[i].frame.y, btn[i].img->GetFrameWidth(), btn[i].img->GetFrameHeight());
	}
}

void TitleScene::SelectBtn(void)
{
	if (key->isKeyDown(VK_DOWN)) {
		if (selectIndex == 3) return;
		selectIndex++;
		_SOUND->Play("TitleButtonMove");
	}
	else if (key->isKeyDown(VK_UP)) {
		if (selectIndex == 1) return;
		selectIndex--;
		_SOUND->Play("TitleButtonMove");
	}
	

	if (key->isKeyDown(VK_SPACE) || key->isKeyDown(VK_RETURN)) {
		
		switch (selectIndex) {
		case MENU_SELECT:
			_SCENE->ChangeScene("Select");
			break;
		case MENU_EDIT:
			_SCENE->ChangeScene("EditMap");
			_SOUND->Stop("TitleBackground");
			break;
		case MENU_OPTION:
			break;
		}
	}

}
