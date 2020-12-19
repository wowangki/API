#include "stdafx.h"
#include "World2.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World2::World2()
{
}


World2::~World2()
{
}

HRESULT World2::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World2", "Map_World2.txt"));
	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World2", "Object_World2.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World2::Release(void)
{
	World::Release();
}

void World2::Update(void)
{
	World::Update();
}

void World2::Render(void)
{
	World::Render();
}
