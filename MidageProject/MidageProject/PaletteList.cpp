#include "stdafx.h"
#include "Palette.h"
#include "Tile.h"
#include "Pannel.h"
#include "Button.h"
#include "Matter.h"
#include "Player.h"
#include "Monster.h"

HRESULT Palette::CreateSeasonTile(Pannel* menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < PALETTESIZEY; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;

		for (int x = 0; x < PALETTESIZEX; x++)
		{
			GameObject* tile = new Tile;
			tile->PaletteInit(tPos, { x,0 }, (TILE_SPRING + y), TILE);
			vTemp.push_back(tile);
			tPos.x += tile->GetSize().width;
		}
		vSeasonTile.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("SEASON", vSeasonTile));

	return S_OK;
}

HRESULT Palette::CreateNonSeasonTile(Pannel * menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < PALETTESIZEY; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;

		for (int x = 0; x < PALETTESIZEX; x++)
		{
			GameObject* tile = new Tile;
			if (TILE_DESERT + y == TILE_LIQUDE) {
				if (x == 2) {
					tile->PaletteInit(tPos, { 0,0 }, TILE_ENTERANCE, TILE);
					vTemp.push_back(tile);
				}
				else {
					tile->PaletteInit(tPos, { x,0 }, (TILE_DESERT + y), TILE);
					vTemp.push_back(tile);
				}
			}
			else {
				tile->PaletteInit(tPos, { x,0 }, (TILE_DESERT + y), TILE);
				vTemp.push_back(tile);
			}
			tPos.x += tile->GetSize().width;
		}
		vNonSeasonTile.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("NONSEASON", vNonSeasonTile));
	return S_OK;
}

HRESULT Palette::CreateMatter(Pannel* menu)
{
	D2D_POINT_2F tPos;
	int type = TREE_NEEDLED_HIGH;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;
	tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;

	vector<GameObject*> vTemp;
	for (int x = 0; x < PALETTESIZEX; x++)
	{
		if (type > TREE_ROOT) break;
		Matter* tree = new Matter;
		tree->PaletteInit(tPos, { x,0 }, TREE, type , MATTER);
		vTemp.push_back(tree);
		tPos.x += tree->GetSize().width;
		type++;
	}
	vMatter.push_back(vTemp);
	tPos.y += vTemp[0]->GetSize().height;
	vTemp.clear();

	mPalette.insert(make_pair("MAPOBJECT", vMatter));

	return S_OK;
}

HRESULT Palette::CreatePlayer(Pannel * menu)
{
	D2D_POINT_2F tPos;
	int type = PLAYER_MALE;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;
	tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;

	vector<GameObject*> vTemp;
	for (int x = 0; x < PALETTESIZEX; x++)
	{
		if (type > PLAYER_FEMALE) break;
		Player* player = new Player;
		player->PaletteInit(tPos, { x,0 }, type, ACTOR);
		vTemp.push_back(player);
		tPos.x += player->GetSize().width;
		type++;
	}
	vPlayer.push_back(vTemp);
	tPos.y += vTemp[0]->GetSize().height;
	vTemp.clear();

	mPalette.insert(make_pair("PLAYER", vPlayer));

	return S_OK;
}

HRESULT Palette::CreateBeast(Pannel * menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < PALETTESIZEY; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;
		int properties = MON_EARTH;
		for (int x = 0; x < PALETTESIZEX; x++)
		{
			Monster* beast = new Monster;
			beast->PaletteInit(tPos, { 0,0 }, (Monster_Properties)properties, MON_BAT + y, ACTOR);
			vTemp.push_back(beast);
			tPos.x += beast->GetSize().width;
			properties++;
		}
		vBeast.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("BEAST", vBeast));
	return S_OK;
}

HRESULT Palette::CreateDemon(Pannel * menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < PALETTESIZEY; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;
		int properties = MON_EARTH;
		for (int x = 0; x < PALETTESIZEX; x++)
		{
			Monster* demon = new Monster;
			demon->PaletteInit(tPos, { 0,0 }, (Monster_Properties)properties, MON_AQUADEMON + y, ACTOR);
			vTemp.push_back(demon);
			tPos.x += demon->GetSize().width;
			properties++;
		}
		vDemon.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("DEMON", vDemon));
	return S_OK;
}

HRESULT Palette::CreateHuman(Pannel * menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < 3; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;
		int properties = MON_EARTH;
		for (int x = 0; x < PALETTESIZEX; x++)
		{
			Monster* human = new Monster;
			human->PaletteInit(tPos, { 0,0 }, (Monster_Properties)properties, MON_KNIGHT + y, ACTOR);
			vTemp.push_back(human);
			tPos.x += human->GetSize().width;
			properties++;
		}
		vHuman.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("HUMAN", vHuman));
	return S_OK;
}

HRESULT Palette::CreateDragon(Pannel * menu)
{
	D2D_POINT_2F tPos;
	tPos.y = menu->GetPos().y - menu->GetSize().height * 0.5f + 8;

	for (int y = 0; y < 2; y++)
	{
		tPos.x = menu->GetPos().x - menu->GetSize().width * 0.5f + 8;
		vector<GameObject*> vTemp;
		int properties = MON_EARTH;
		for (int x = 0; x < PALETTESIZEX; x++)
		{
			Monster* dragon = new Monster;
			dragon->PaletteInit(tPos, { 0,0 }, (Monster_Properties)properties, MON_DRAGON + y, ACTOR);
			vTemp.push_back(dragon);
			tPos.x += dragon->GetSize().width;
			properties++;
		}
		vDragon.push_back(vTemp);
		tPos.y += vTemp[0]->GetSize().height;
		vTemp.clear();
	}
	mPalette.insert(make_pair("DRAGON", vDragon));
	return S_OK;
}
