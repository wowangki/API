#pragma once
#include "KeyModule.h"

class Button;
class Tile;
class PlayController
{
private:
	class MapClass* map;
	class Player* player;
	class PlayUI* ui;
	class KeyModule* key;
	class ObjectManager* object;
	class Data* data;

private:
	Tile* dest;
	Button* sTbtn;
	Button* bTbtn;
	Button* oTbtn;

private:
	D2D_POINT_2F preCAM;
	float camSpeed;

private:
	bool isEdit;

public:
	PlayController(ObjectManager* object, PlayUI* ui, MapClass* map, Data* data);
	~PlayController();

	HRESULT Init(void);
	void Update(void);
	void FieldMoveControl(void);
	void StatusControl(void);
	
	void BattleControl(void);
	void BattleComControl(void);
	void OptionControl(void);
};

