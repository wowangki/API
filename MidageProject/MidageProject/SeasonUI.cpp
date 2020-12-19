#include "stdafx.h"
#include "SeasonUI.h"
#include "MapClass.h"
#include "Season.h"
#include "Tile.h"

SeasonUI::SeasonUI(MapClass* map)
{
	this->map = map;
}


SeasonUI::~SeasonUI()
{
}

HRESULT SeasonUI::Init(void)
{
	_FONT->Create("SESONTXT", L"¸¼Àº °íµñ", 9.0f, DWRITE_TEXT_ALIGNMENT_CENTER);

	size = { 30,30 };
	seasonName[0] = "SPRING";
	seasonName[1] = "SUMMER";
	seasonName[2] = "AUTUMN";
	seasonName[3] = "WINTER";


	bool isFind = false;
	for (UINT y = 0; y < map->GetVMap().size(); y++)
	{
		if (isFind) break;
		for (UINT x = 0; x < map->GetVMap()[y].size(); x++)
		{
			if (map->GetVMap()[y][x]->GetIsSeason())
			{
				pivotTile = map->GetVMap()[y][x];
				type = pivotTile->GetType();
				isFind = true;
				switch (type) {
				case TILE_SPRING:
					if(!_SOUND->isPlay("WorldSpring"))
					_SOUND->Play("WorldSpring");
					break;
				case TILE_SUMMER:
					if (!_SOUND->isPlay("WorldSummer"))
					_SOUND->Play("WorldSummer");
					break;
				case TILE_AUTUMN:
					if (!_SOUND->isPlay("WorldAutumn"))
					_SOUND->Play("WorldAutumn");
					break;
				case TILE_WINTER:
					if (!_SOUND->isPlay("WorldWinter"))
					_SOUND->Play("WorldWinter");
					break;
				}
				break;
			}
		}
	}
	return S_OK;
}

void SeasonUI::Release(void)
{
	
}

void SeasonUI::Update(void)
{
	circle = CircleMake(size.width, WINSIZEY - size.height, size.width);
	rc = FRectMakeCenter(size.width, WINSIZEY - size.height, 40, 10);
	
	if (type != pivotTile->GetType()) {
		type = pivotTile->GetType();
		_SOUND->Stop("WorldSpring");
		_SOUND->Stop("WorldSummer");
		_SOUND->Stop("WorldAutumn");
		_SOUND->Stop("WorldWinter");
		switch (type) {
		case TILE_SPRING:
			_SOUND->Play("WorldSpring");
			break;
		case TILE_SUMMER:
			_SOUND->Play("WorldSummer");
			break;
		case TILE_AUTUMN:
			_SOUND->Play("WorldAutumn");
			break;
		case TILE_WINTER:
			_SOUND->Play("WorldWinter");
			break;
		}
	}
	
}

void SeasonUI::Render(void)
{
	switch (type) {
	case TILE_SPRING:
		_RenderTarget->FillEllipse(circle, _BRUSH->GetBrush("GREEN"));
		break;
	case TILE_SUMMER:
		_RenderTarget->FillEllipse(circle, _BRUSH->GetBrush("DGREEN"));
		break;
	case TILE_AUTUMN:
		_RenderTarget->FillEllipse(circle, _BRUSH->GetBrush("ORANGE"));
		break;
	case TILE_WINTER:
		_RenderTarget->FillEllipse(circle, _Device->pDefaultBrush);
		break;
	}

	_FONT->Render(seasonName[type - 1], rc, _BRUSH->GetBrush("BLACK"), "SESONTXT");
}