#pragma once
#include "GameObject.h"

enum Tile_Season {
	TILE_SEASON,
	TILE_NONSEASON
};

enum Tile_Type {
	TILE_DEFAULT,
	TILE_SPRING,
	TILE_SUMMER,
	TILE_AUTUMN,
	TILE_WINTER,
	TILE_DESERT,
	TILE_ROCKY,
	TILE_LAVA,
	TILE_LIQUDE,
	TILE_ENTERANCE
};
class Season;
class Tile : public GameObject
{
private:
	Season* season;

private:
	bool isSeason;
	float delta;

public:
	Tile();
	~Tile();

	HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind = TILE) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
	void EditRender(void);

	HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind = TILE) override;
	void PaletteUpdate(void) override;
	void PaletteRender(void) override;

	void SetName(int type) override;
	void SetSeason(int type);
	void ChangeSeason(void);

	bool GetIsSeason(void) { return isSeason; }
	void SetIsSeason(bool isSeason) { this->isSeason = isSeason; }
};

