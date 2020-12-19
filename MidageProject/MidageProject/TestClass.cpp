#include "stdafx.h"
#include "TestClass.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

TestClass::TestClass()
{
}


TestClass::~TestClass()
{
}

HRESULT TestClass::Init(void)
{
	map = new MapClass;
	object = new ObjectManager(map);
	testData = new Data;
	ui = new PlayUI(UI_FIELD);
	controller = new PlayController(object, ui, map, testData);
	Data::PlayerLoad loadPlayer = testData->LoadSlotNum();

	map->Init();
	object->Init();
	testData->LoadPlayerPosition(object, loadPlayer.pos);
	testData->LoadPlayerProperty(object->GetPlayer(), loadPlayer.proper);

	testData->LoadMap(map, FileSource("Resource", "World/Test", "Map_Test.txt"));

	if (testData->isExist(FileSource("Resource", "World/Progress", "Object_Progress.txt"))) {
		testData->LoadObjectPosition(object, FileSource("Resource", "World/Progress", "Object_Progress.txt"));
	}
	else testData->LoadObjectPosition(object, FileSource("Resource", "World/Test", "Object_Test.txt"));

	ui->Init(map, object);
	controller->Init();

	_CAM->x = WINSIZEX * 0.5f - object->GetPlayer()->GetPos().x;
	_CAM->y = WINSIZEY * 0.5f - object->GetPlayer()->GetPos().y;
	return S_OK;
}

void TestClass::Release(void)
{
	SafeDeleteClass(map);
	SafeDeleteClass(object);
	SafeDelete(testData);
	SafeDeleteClass(ui);
	SafeDelete(controller);
}

void TestClass::Update(void)
{
	SafeUpdate(map);
	SafeUpdate(ui);
	SafeUpdate(controller);
	SafeUpdate(object);
	if(object) ChangeMap();
}

void TestClass::Render(void)
{
	map->Render();
	object->Render();
	ui->Render();
}

void TestClass::ChangeMap(void)
{
	Player* player = object->GetPlayer();

	if (player->GetIsMoveMap()) {
		DeleteFile(StringToWstring(FileSource("Resource", "World/Progress", "Object_Progress.txt")).c_str());
		testData->SavePlayerPosition(player, testData->LoadSlotNum().pos);
		testData->SavePlayerProperty(player, testData->LoadSlotNum().proper);

		_CAM->x = 0;
		_CAM->y = 0;
		_SCENE->ChangeScene(object->GetPlayer()->GetWorldInfoName());
	}

	if (player->GetEngage()) {

		testData->SaveBattleMap(map, player);
		testData->SaveBattlePlayerPosition(player);
		testData->SaveBattleMonsterPosition(player->GetEngageMonster());
		testData->SaveBattleMonsterProperty(player->GetEngageMonster());
		object->DeleteObject();
		testData->SavePlayerPosition(player, testData->LoadSlotNum().pos);
		testData->SavePlayerProperty(player, testData->LoadSlotNum().proper);
		testData->SaveObjectPosition(object, FileSource("Resource", "World/Progress", "Object_Progress.txt"));
		

		_CAM->x = 0;
		_CAM->y = 0;
		_SCENE->ChangeScene("Battle");
	}
	
	
}
