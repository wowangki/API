#include "stdafx.h"
#include "Battle.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

Battle::Battle()
{
}


Battle::~Battle()
{
}

HRESULT Battle::Init(void)
{
	data = new Data;
	map = new MapClass;
	object = new ObjectManager(map);
	ui = new PlayUI (UI_BATTLE);
	controller = new PlayController(object, ui, map, data);

	int quantity = GetRandomInt(1, 3);

	map->Init();
	object->Init();
	data->LoadBattleMap(map);
	data->LoadBattlePlayerPosition(object);
	data->LoadPlayerProperty(object->GetPlayer(), data->LoadSlotNum().proper);
	data->LoadBattleMonsterPosition(object, quantity);
	data->LoadBattleMonsterProperty(object);

	ui->Init(map, object);
	controller->Init();
	SetCam();
	object->SetObjectTimeBoard(ui->GetParameter());

	_SOUND->SetEffectVolume(0.1f);
	_SOUND->Play("WorldBattle");
	return S_OK;
}

void Battle::Release(void)
{
	World::Release();
	DeleteFile(StringToWstring(FileSource("Resource", "World/Battle", "Map_Battle.txt")).c_str());
	DeleteFile(StringToWstring(FileSource("Resource", "World/Battle", "Player_Pos_Battle.txt")).c_str());
	DeleteFile(StringToWstring(FileSource("Resource", "World/Battle", "Monster_Pos_Battle.txt")).c_str());
	DeleteFile(StringToWstring(FileSource("Resource", "World/Battle", "Monster_Proper_Battle.txt")).c_str());
	_SOUND->Stop("WorldBattle");
}

void Battle::Update(void)
{
	map->Update();
	object->BattleUpdate();
	ui->Update();
	controller->Update();

	if(object) IsEnd();
}

void Battle::Render(void)
{
	map->Render();
	object->Render();
	ui->Render();
}

void Battle::IsEnd(void)
{
	vector<vector<GameObject*>> vObject = object->GetVObject();

	ChkIsBattleEnd(vObject);
	ChkGameOver(vObject);

	if (isEndBattle) {
		Player* player = object->GetPlayer();
		data->SavePlayerProperty(player, data->LoadSlotNum().proper);
		_CAM->x = 0;
		_CAM->y = 0;
		_SCENE->ChangeScene(player->GetWorldInfoName());
	}
	else if (isGameOver) {
		DeleteFile(StringToWstring(data->LoadSlotNum().pos).c_str());
		DeleteFile(StringToWstring(data->LoadSlotNum().proper).c_str());
		_SCENE->ChangeScene("Title");
	}
}

void Battle::ChkIsBattleEnd(vector<vector<GameObject*>> vObject)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x]->GetKind() == ACTOR) {
				if (dynamic_cast<Actor*>(vObject[y][x])->GetActorKind() == MONSTER) {
					isEndBattle = false;
					return;
				}
				else {
					isEndBattle = true;
				}
			}
		}
	}
}

void Battle::ChkGameOver(vector<vector<GameObject*>> vObject)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x]->GetKind() == ACTOR) {
				if (dynamic_cast<Actor*>(vObject[y][x])->GetActorKind() == PLAYER) {
					isGameOver = false;
					return;
				}
				else isGameOver = true;
			}
		}
	}
}
