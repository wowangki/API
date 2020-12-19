#include "stdafx.h"
#include "World5.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"


World5::World5()
{
}


World5::~World5()
{
}

HRESULT World5::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World5", "Map_World5.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World5", "Object_World5.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World5::Release(void)
{
	World::Release();
}

void World5::Update(void)
{
	World::Update();
}

void World5::Render(void)
{
	World::Render();
}
