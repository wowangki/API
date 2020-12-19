#include "stdafx.h"
#include "World6.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World6::World6()
{
}


World6::~World6()
{
}

HRESULT World6::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World6", "Map_World6.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World6", "Object_World6.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World6::Release(void)
{
	World::Release();
}

void World6::Update(void)
{
	World::Update();
}

void World6::Render(void)
{
	World::Render();
}
