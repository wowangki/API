#include "stdafx.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World::World()
{
}


World::~World()
{
}

HRESULT World::Init(void)
{
	data = new Data;
	map = new MapClass;
	object = new ObjectManager(map);
	ui = new PlayUI(UI_FIELD);
	controller = new PlayController(object, ui, map, data);
	Data::PlayerLoad loadPlayer = data->LoadSlotNum();
	map->Init();
	object->Init();
	data->LoadPlayerPosition(object, loadPlayer.pos);
	data->LoadPlayerProperty(object->GetPlayer(), loadPlayer.proper);
	SetCam();

	return S_OK;
}

void World::Release(void)
{
	SafeDeleteClass(map);
	SafeDeleteClass(object);
	SafeDelete(data);
	SafeDeleteClass(ui);
	SafeDelete(controller);
}

void World::Update(void)
{
	SafeUpdate(map);
	SafeUpdate(ui);
	SafeUpdate(controller);
	SafeUpdate(object);
	//if(object)ChangeMap();
}

void World::Render(void)
{
	map->Render();
	object->Render();
	ui->Render();
}

void World::SetCam(void)
{
	Player* tPlayer = object->GetPlayer();
	if (tPlayer == nullptr) return;

	_CAM->x = WINSIZEX * 0.5f - tPlayer->GetPos().x;
	_CAM->y = WINSIZEY * 0.5f - tPlayer->GetPos().y;
}

void World::ChangeMap(void)
{
	Player* player = object->GetPlayer();

	if (player->GetIsMoveMap()) {
		DeleteFile(StringToWstring(FileSource("Resource", "World/Progress", "Object_Progress.txt")).c_str());
		data->SavePlayerPosition(player, data->LoadSlotNum().pos);
		data->SavePlayerProperty(player, data->LoadSlotNum().proper);

		_CAM->x = 0;
		_CAM->y = 0;
		_SCENE->ChangeScene(object->GetPlayer()->GetWorldInfoName());
	}

	if (player->GetEngage()) {

		data->SaveBattleMap(map, player);
		data->SaveBattlePlayerPosition(player);
		data->SaveBattleMonsterPosition(player->GetEngageMonster());
		data->SaveBattleMonsterProperty(player->GetEngageMonster());
		object->DeleteObject();
		data->SavePlayerPosition(player, data->LoadSlotNum().pos);
		data->SavePlayerProperty(player, data->LoadSlotNum().proper);
		data->SaveObjectPosition(object, FileSource("Resource", "World/Progress", "Object_Progress.txt"));

		_CAM->x = 0;
		_CAM->y = 0;
		_SCENE->ChangeScene("Battle");
		_SOUND->Stop("WorldSpring");
		_SOUND->Stop("WorldSummer");
		_SOUND->Stop("WorldAutumn");
		_SOUND->Stop("WorldWinter");
	}
}
