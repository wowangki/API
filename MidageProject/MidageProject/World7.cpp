#include "stdafx.h"
#include "World7.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World7::World7()
{
}


World7::~World7()
{
}

HRESULT World7::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World7", "Map_World7.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World7", "Object_World7.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World7::Release(void)
{
	World::Release();
}

void World7::Update(void)
{
	World::Update();
}

void World7::Render(void)
{
	World::Render();
}
