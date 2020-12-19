#include "stdafx.h"
#include "LoadSource.h"
#include "ImageSource.h"
#include "SoundSource.h"
#include "PrograssBar.h"

LoadSource::LoadSource()
	:totalLoadProgress(0), graphicProgress(0), soundProgress(0), kind(LOAD_GRAPHIC)
{
}

LoadSource::~LoadSource()
{
}

HRESULT LoadSource::Init(void)
{
	imgSource = new ImageSource;
	soundSource = new SoundSource;
	prograss = new PrograssBar;
	prograss->Init();
	img = _IMAGE->CreateFrameImage("Background", FileSource("Image", "Background", "Background.jpg"), 1, 1);
	progressPersent = 100 / (GRAPHIC_UI + 1 + SOUND_ACTOR + 1);
	return S_OK;
}

void LoadSource::Release(void)
{
	SafeDeleteClass(prograss);
}

void LoadSource::Update(void)
{
	if (LoadDone()) {
		_SCENE->ChangeScene("Title");
	}
}

void LoadSource::Render(void)
{
	img->FrameRender(0, 0, 0, 0, WINSIZEX, WINSIZEY);
	prograss->Render();
}

void LoadSource::FontInit(void)
{
	_FONT->Create("Hp", L"Èâ¸Õ±¼¸²Ã¼", 8.0f, DWRITE_TEXT_ALIGNMENT_CENTER);
	_FONT->Create("BTNNAME", L"ÈÞ¸Õ±¼¸²Ã¼", 8.0f, DWRITE_TEXT_ALIGNMENT_CENTER);
	_FONT->Create("PANNEL", L"ÈÞ¸Õ±¼¸²Ã¼", 10.0f, DWRITE_TEXT_ALIGNMENT_CENTER);
	_FONT->Create("SELECT", L"ÈÞ¸Õ±¼¸²Ã¼", 15.0f, DWRITE_TEXT_ALIGNMENT_CENTER);
	_FONT->Create("STATUS", L"ÈÞ¸Õ±¼¸²Ã¼", 12.0f, DWRITE_TEXT_ALIGNMENT_CENTER);

}

void LoadSource::BrushInit(void)
{
	_BRUSH->CreateBrush("BLACK", RGB(0, 0, 0));
	_BRUSH->CreateBrush("WHITE", RGB(255, 255, 255));
	_BRUSH->CreateBrush("GRAY", RGB(125, 125, 125));
	_BRUSH->CreateBrush("RED", RGB(255, 0, 0));
	_BRUSH->CreateBrush("GREEN", RGB(0, 255, 0));
	_BRUSH->CreateBrush("BLUE", RGB(0, 0, 255));
	_BRUSH->CreateBrush("YELLOW", RGB(255, 201, 14));
	_BRUSH->CreateBrush("MAGENTA", RGB(255, 0, 255));
	_BRUSH->CreateBrush("DGREEN", RGB(0, 145, 0));
	_BRUSH->CreateBrush("ORANGE", RGB(255, 168, 0));
}

bool LoadSource::LoadDone(void)
{
	prograss->Update();
	if (prograss->GetIsComplete()) return true;
	
	switch (kind) {
	case LOAD_GRAPHIC:
		GraphicLoad();
		break;
	case LOAD_SOUND:
		SoundLoad();
		break;
	}
	
	totalLoadProgress = graphicProgress + soundProgress;

	prograss->SetProgress(progressPersent * totalLoadProgress);
	return false;
}

void LoadSource::GraphicLoad(void)
{
	switch (graphicProgress) {
	case GRAPHIC_FONT:
		FontInit();
		break;
	case GRAPHIC_COLOR:
		BrushInit();
		break;
	case GRAPHIC_TITLE:
		imgSource->CreateTitleImage();
		break;
	case GRAPHIC_TILE:
		imgSource->CreateTileImage();
		break;
	case GRAPHIC_MONSTER:
		imgSource->CreateMonsterImage();
		break;
	case GRAPHIC_ITEM:
		imgSource->CreateItemImage();
		break;
	case GRAPHIC_PLAYER:
		imgSource->CreatePlayerImage();
		break;
	case GRAPHIC_MATTER:
		imgSource->CreateMatterImage();
		break;
	case GRAPHIC_EFFECT:
		imgSource->CreateEffectImage();
		break;
	case GRAPHIC_UI:
		imgSource->CreateUIImage();
		kind++;
		break;
	}
	graphicProgress++;
}

void LoadSource::SoundLoad(void)
{
	switch (soundProgress)
	{
	case SOUND_TITLE:
		soundSource->CreateTitleSound();
		break;
	case SOUND_WORLD:
		soundSource->CreateWorldSound();
		break;
	case SOUND_ACTOR:
		soundSource->CreateActorSound();
		break;
	}

	soundProgress++;
}
