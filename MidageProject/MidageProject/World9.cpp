#include "stdafx.h"
#include "World9.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World9::World9()
{
}


World9::~World9()
{
}

HRESULT World9::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World9", "Map_World9.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World9", "Object_World9.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World9::Release(void)
{
	World::Release();
}

void World9::Update(void)
{
	World::Update();
}

void World9::Render(void)
{
	World::Render();
}
