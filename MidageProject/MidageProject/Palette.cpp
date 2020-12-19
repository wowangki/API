#include "stdafx.h"
#include "Palette.h"
#include "Tile.h"
#include "Pannel.h"
#include "Button.h"

Palette::Palette()
{
}


Palette::~Palette()
{
}

HRESULT Palette::Init(Pannel * menu)
{
	CreateSeasonTile(menu);
	CreateNonSeasonTile(menu);
	CreateMatter(menu);
	CreatePlayer(menu);
	CreateBeast(menu);
	CreateDemon(menu);
	CreateHuman(menu);
	CreateDragon(menu);

	ChangePalette("SEASON");

	return S_OK;
}



void Palette::Release(void)
{
	for (UINT y = 0; y < vPalette.size(); y++)
	{
		for (UINT x = 0; x < vPalette[y].size(); x++)
		{
			SafeRelease(vPalette[y][x]);
		}
	}
	vPalette.clear();
}

void Palette::Update(Button * btn)
{
	for (UINT y = 0; y < vPalette.size(); y++)
	{
		for (UINT x = 0; x < vPalette[y].size(); x++)
		{
			vPalette[y][x]->PaletteUpdate();
		}
	}
}

void Palette::Render(void)
{
	for (UINT y = 0; y < vPalette.size(); y++)
	{
		for (UINT x = 0; x < vPalette[y].size(); x++)
		{
			vPalette[y][x]->PaletteRender();
			_RenderTarget->DrawRectangle(vPalette[y][x]->GetRc(), _Device->pDefaultBrush);
		}
	}
}
