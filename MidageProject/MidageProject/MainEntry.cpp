#include "stdafx.h"
#include "MainEntry.h"
#include "LoadSource.h"
#include "EditScene.h"
#include "TitleScene.h"
#include "TestClass.h"
#include "Battle.h"
#include "PlayerSelect.h"
#include "World1.h"
#include "World2.h"
#include "World3.h"
#include "World4.h"
#include "World5.h"
#include "World6.h"
#include "World7.h"
#include "World8.h"
#include "World9.h"


MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_CAM->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_SCENE->ReleaseSingleton();
	_SOUND->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	_SCENE->CreateScene("Loading", new LoadSource);
	_SCENE->CreateScene("Title", new TitleScene);
	_SCENE->CreateScene("Select", new PlayerSelect);
	_SCENE->CreateScene("World1", new World1);
	_SCENE->CreateScene("World1", new World1);
	_SCENE->CreateScene("World2", new World2);
	_SCENE->CreateScene("World3", new World3);
	_SCENE->CreateScene("World4", new World4);
	_SCENE->CreateScene("World5", new World5);
	_SCENE->CreateScene("World6", new World6);
	_SCENE->CreateScene("World7", new World7);
	_SCENE->CreateScene("World8", new World8);
	_SCENE->CreateScene("World9", new World9);
	_SCENE->CreateScene("EditMap", new EditScene);
	_SCENE->CreateScene("Battle", new Battle);
	_SCENE->CreateScene("Test", new TestClass);
	_SCENE->ChangeScene("Loading");

	
	return S_OK;
}

void MainEntry::Release(void)
{
	
}

void MainEntry::Update(void)
{
	_SCENE->Update();
}

void MainEntry::Render(void)
{
	_SCENE->Render();
}
