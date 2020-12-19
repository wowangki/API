#include "stdafx.h"
#include "World4.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"


World4::World4()
{
}


World4::~World4()
{
}

HRESULT World4::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World4", "Map_World4.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World4", "Object_World4.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World4::Release(void)
{
	World::Release();
}

void World4::Update(void)
{
	World::Update();
}

void World4::Render(void)
{
	World::Render();
}
