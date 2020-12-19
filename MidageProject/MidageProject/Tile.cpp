#include "stdafx.h"
#include "Tile.h"
#include "Season.h"

Tile::Tile()
{
}


Tile::~Tile()
{
}

HRESULT Tile::Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	GameObject::Init(id, frame, type, kind);
	this->type = type;
	SetSeason(this->type);

	frameTime = 0;
	elapsedTime = 20;
	
	return S_OK;
}

void Tile::Release(void)
{
	GameObject::Release();
}

void Tile::Update(void)
{
	GameObject::Update();

	if (type == TILE_ENTERANCE)
	{
		if (opacity == 1.0f) delta = -0.005f;
		else if (opacity == 0.5f) delta = 0.005f;

		opacity += delta;

		if (opacity >= 1.0f) opacity = 1.0f;
		else if (opacity <= 0.5f) opacity = 0.5f;
	}

	if (type == TILE_LIQUDE && frame.x == 0) {
		frameTime++;
		if (frameTime % elapsedTime == 0) {
			frame.y++;
			frameTime = 0;
			if (frame.y >= img->GetMaxFrameY()) {
				frame.y = 0;
			}
		}
	}

	if (season != nullptr) {
		season->Update();
		ChangeSeason();
	}
}

void Tile::Render(void)
{
	if (isCull) return;
	if(type != TILE_DEFAULT) GameObject::Render();
}

void Tile::EditRender(void)
{
	if (isCull) return;
	if (type != TILE_DEFAULT) GameObject::Render();
	else {
		_RenderTarget->DrawLine({ rymPos[0].x + _CAM->x , rymPos[0].y + _CAM->y }, { rymPos[1].x + _CAM->x , rymPos[1].y + _CAM->y }, _Device->pDefaultBrush);
		_RenderTarget->DrawLine({ rymPos[0].x + _CAM->x , rymPos[0].y + _CAM->y }, { rymPos[3].x + _CAM->x , rymPos[3].y + _CAM->y }, _Device->pDefaultBrush);
	}
}

void Tile::SetName(int type)
{
	switch (type) {
	case TILE_DEFAULT:
		name = "";
		imgKey = "Tile_Spring";
		break;
	case TILE_SPRING:
		name = "Tile_Spring";
		imgKey = "Tile_Spring";
		break;
	case TILE_SUMMER:
		name = "Tile_Summer";
		imgKey = "Tile_Summer";
		break;
	case TILE_AUTUMN:
		name = "Tile_Autumn";
		imgKey = "Tile_Autumn";
		break;
	case TILE_WINTER:
		name = "Tile_Winter";
		imgKey = "Tile_Winter";
		break;
	case TILE_DESERT:
		name = "Tile_Desert";
		imgKey = "Tile_Desert";
		break;
	case TILE_ROCKY:
		name = "Tile_Rocky";
		imgKey = "Tile_Rocky";
		break;
	case TILE_LAVA:
		name = "Tile_Lava";
		imgKey = "Tile_Lava";
		break;
	case TILE_LIQUDE:
		name = "Tile_Liqude";
		imgKey = "Tile_Liqude";
		break;
	case TILE_ENTERANCE:
		name = "Enterance";
		imgKey = "Enterance";
	}
}

void Tile::SetSeason(int type)
{
	switch (type)
	{
	case TILE_SPRING:
	case TILE_SUMMER:
	case TILE_AUTUMN:
	case TILE_WINTER:
		isSeason = true;
		season = new Season;
		break;
	default:
		isSeason = false;
		season = nullptr;
	break;
	}
}

void Tile::ChangeSeason(void)
{
	if (isSeason) {
		if (type == season->GetSeasonKind() + 1) return;
		type = season->GetSeasonKind() + 1;
		SetName(type);
		SetImg(imgKey);
	}
}

HRESULT Tile::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	GameObject::PaletteInit(pos, frame, type, kind);
	this->pos.x += size.width * 0.5f;
	this->pos.y += size.height * 0.5f;
	SetSeason(this->type);
	return S_OK;
}

void Tile::PaletteUpdate(void)
{
	GameObject::PaletteUpdate();
}

void Tile::PaletteRender(void)
{
	GameObject::PaletteRender();
}