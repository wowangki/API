#include "stdafx.h"
#include "World3.h"
#include "Tile.h"
#include "Player.h"
#include "MapClass.h"
#include "ObjectManager.h"
#include "Data.h"
#include "PlayController.h"
#include "PlayUI.h"


World3::World3()
{
}


World3::~World3()
{
}

HRESULT World3::Init(void)
{
	World::Init();
	data->LoadMap(map, FileSource("Resource", "World/World3", "Map_World3.txt"));
	
	if (data->isExist(FileSource("Resource", "World/Progress", "ObjectProgress.txt"))) {
		data->LoadObjectPosition(object, FileSource("Resource", "Wolrd/Progress", "Object_Progress.txt"));
	}
	else data->LoadObjectPosition(object, FileSource("Resource", "World/World3", "Object_World3.txt"));
	ui->Init(map, object);
	controller->Init();

	return S_OK;
}

void World3::Release(void)
{
	World::Release();
}

void World3::Update(void)
{
	World::Update();
}

void World3::Render(void)
{
	World::Render();
}
