#include "stdafx.h"
#include "World1.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World1::World1()
{
}


World1::~World1()
{
}

HRESULT World1::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World1", "Map_World1.txt"));
	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World1", "Object_World1.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World1::Release(void)
{
	World::Release();
}

void World1::Update(void)
{
	World::Update();
}

void World1::Render(void)
{
	World::Render();
}
