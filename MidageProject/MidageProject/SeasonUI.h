#pragma once

class Tile;
class MapClass;
class SeasonUI
{
private:
	MapClass* map;
	Tile* pivotTile;

private:
	string seasonName[4];
	D2D_SIZE_F size;
	D2D1_ELLIPSE circle;
	D2D_RECT_F rc;

	int type;

public:
	SeasonUI(MapClass* map);
	~SeasonUI();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

};

