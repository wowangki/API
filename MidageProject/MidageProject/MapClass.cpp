#include "stdafx.h"
#include "MapClass.h"
#include "Tile.h"

MapClass::MapClass()
	:mapSizeX(MAPSIZE), mapSizeY(MAPSIZE)
{
}


MapClass::~MapClass()
{
}

HRESULT MapClass::Init(int mapSizeX, int mapSizeY)
{
	SetMapSize(mapSizeX, mapSizeY);
	for (int y = 0; y < mapSizeY; y++)
	{
		vector<Tile*> vTile;
		for (int x = 0; x < mapSizeX; x++)
		{
			Tile* tile = new Tile;
			tile->Init({ x,y }, { x,0 }, TILE_DEFAULT,TILE);
			vTile.push_back(tile);
		}
		vMap.push_back(vTile);
		vTile.clear();
	}

	backImg = _IMAGE->FindImage("Background");

	return S_OK;
}

void MapClass::Release(void)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->Release();
		}
	}
	vMap.clear();
}

void MapClass::Update(void)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->Update();
		}
	}
}

void MapClass::Render(void)
{
	backImg->UiFrameRender(0, 0, 0, 0, WINSIZEX, WINSIZEY);
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->Render();
			SelectMap(vMap[y][x]);
		}
	}
}

void MapClass::EditRender(void)
{
	WCHAR sizeString[256];
	static TCHAR sizeText[] = L"x:%d y:%d";
	_stprintf_s(sizeString, sizeText, mapSizeX, mapSizeY);
	_FONT->Render(sizeString, FRectMake(WINSIZEX - 50, 0, 50 , 100));


	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->EditRender();
			SelectMap(vMap[y][x]);

			//WCHAR idString[256];
			//static TCHAR idText[] = L"%d %d";
			//_stprintf_s(idString, idText, vMap[y][x]->GetId().x, vMap[y][x]->GetId().y);
			//_FONT->Render(idString, vMap[y][x]->GetRc());

		}
	}
}

void MapClass::SetEditMode(bool isEdit)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->SetIsEdit(isEdit);
		}
	}
}

void MapClass::SelectMap(Tile* tile)
{
	if (MouseInISO(tile->GetRymPos()))
	{
		for (int i = 0; i < 4; i++)
		{
			if (i != 3) {
				_RenderTarget->DrawLine({ tile->GetRymPos()[i].x + _CAM->x, tile->GetRymPos()[i].y + _CAM->y }, { tile->GetRymPos()[i + 1].x + _CAM->x, tile->GetRymPos()[i + 1].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
			}
			else _RenderTarget->DrawLine({ tile->GetRymPos()[i].x + _CAM->x, tile->GetRymPos()[i].y + _CAM->y }, { tile->GetRymPos()[0].x + _CAM->x, tile->GetRymPos()[0].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
		}
	}
}

void MapClass::IncreaseMap(void)
{
	mapSizeX++;																//int 형변수
	mapSizeY++;																//int 형변수

	for (int y = 0; y < mapSizeY; y++)
	{
		if (y != mapSizeY - 1)
		{
			Tile* tTile = new Tile;
			tTile->Init({ mapSizeX - 1, y }, { 0,0 }, TILE_DEFAULT, TILE);	//맵의 X축에 기본 타일 배치

			vMap[y].push_back(tTile);
		}
		else
		{
			vector<Tile*> vTemp;
			for (int x = 0; x < mapSizeX; x++)
			{
				Tile* tTile = new Tile;
				tTile->Init({ x,y }, { 0,0 }, TILE_DEFAULT, TILE);			//맵의 Y축에 기본 타일 배치
				vTemp.push_back(tTile);
			}
			vMap.push_back(vTemp);
			vTemp.clear();
		}
	}
}

void MapClass::DecreaseMap(void)
{
	if (vMap.size() == NULL) return;
	mapSizeX--;										//int 형 변수
	mapSizeY--;										//int 형 변수

	for (UINT y = 0; y < vMap.size(); y++)
	{
		vMap[y].pop_back();							//맵의 X축 타일 제거
	}
	vMap.pop_back();								//맵의 Y축 타일 제거
}

void MapClass::SetMap(GameObject * select)
{
	if (select == nullptr) return;

	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			if (MouseInISO(vMap[y][x]->GetRymPos()))
			{
				vMap[y][x]->ChangeObject(select->GetFrame(), select->GetType());
				return;
			}
		}
	}
}

void MapClass::DeleteMap(void)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			if (MouseInISO(vMap[y][x]->GetRymPos()))
			{
				vMap[y][x]->ChangeObject({ 0,0 }, TILE_DEFAULT);
				if (vMap[y][x]->GetIsSeason()) vMap[y][x]->SetIsSeason(false);
				return;
			}
		}
	}
}

Tile * MapClass::GetMapTile(void)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			if (MouseInISO(vMap[y][x]->GetRymPos()))
			{
				return vMap[y][x];
			}
		}
	}

	return nullptr;
}

void MapClass::SetMapSize(int mapSizeX, int mapSizeY)
{
	if (mapSizeX == MAPSIZE || mapSizeY == MAPSIZE) {
		this->mapSizeX = MAPSIZE;
		this->mapSizeY = MAPSIZE;
	}
	else {
		this->mapSizeX = mapSizeX;
		this->mapSizeY = mapSizeY;
	}
}

void MapClass::SetLoadMapSize(int mapSizeX, int mapSizeY)
{
	while (true) {
		if (mapSizeX == vMap.size()) break;

		if (mapSizeY > vMap.size()) {
			IncreaseMap();
		}
		else DecreaseMap();
	}
}
