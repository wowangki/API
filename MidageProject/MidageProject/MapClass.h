#pragma once
#include <vector>
#define MAPSIZE 5

class Tile;
class GameObject;
class MapClass
{
public:
	typedef vector<vector<Tile*>> _vMap;

// ≈∏¿œ ∫§≈Õ
protected:
	_vMap vMap;
// ∏  ≈©±‚
protected:
	int mapSizeX;
	int mapSizeY;
	ImageModule* backImg;

public:
	MapClass();
	~MapClass();

	HRESULT Init(int mapSizeX = MAPSIZE, int mapSizeY = MAPSIZE);
	void Release(void);
	void Update(void);
	void Render(void);
	void EditRender(void);

	void SetEditMode(bool isEdit);
	void SelectMap(Tile* tile);
	void IncreaseMap(void);
	void DecreaseMap(void);
	void SetMap(GameObject* select);
	void DeleteMap(void);
	Tile* GetMapTile(void);


	void SetMapSize(int mapSizeX, int mapSizeY);
	void SetLoadMapSize(int mapSizeX, int mapSizeY);
	_vMap GetVMap() { return vMap; }

	int GetMapSizeX(void) { return mapSizeX; }
	int GetMapSizeY(void) { return mapSizeY; }

	
};

