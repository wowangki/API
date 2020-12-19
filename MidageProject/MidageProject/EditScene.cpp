#include "stdafx.h"
#include "EditScene.h"
#include "MapClass.h"
#include "EditUI.h"
#include "EditController.h"
#include "ObjectManager.h"

EditScene::EditScene()
{
}


EditScene::~EditScene()
{
}

HRESULT EditScene::Init(void)
{
	_CAM->x = 0;
	_CAM->y = 0;

	editMap = new MapClass;
	editUi = new EditUI;
	editMap->Init(30, 30);
	editUi->Init();
	manager = new ObjectManager;
	manager->Init();
	controller = new EditController;
	controller->Init(editUi, editMap, manager);

	return S_OK;
}

void EditScene::Release(void)
{
	SafeRelease(editMap);
	SafeRelease(editUi);
	SafeRelease(manager);
	SafeRelease(controller);
}

void EditScene::Update(void)
{
	editMap->Update();
	manager->Update();
	editUi->Update();
	controller->Update();
}

void EditScene::Render(void)
{
	editMap->EditRender();
	manager->Render();
	editUi->Render();
	controller->Render();
}
