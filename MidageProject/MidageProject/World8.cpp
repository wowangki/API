#include "stdafx.h"
#include "World8.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"

World8::World8()
{
}


World8::~World8()
{
}

HRESULT World8::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World8", "Map_World8.txt"));

	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World8", "Object_World8.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World8::Release(void)
{
	World::Release();
}

void World8::Update(void)
{
	World::Update();
}

void World8::Render(void)
{
	World::Render();
}
