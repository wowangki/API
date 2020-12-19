#pragma once

class KeyModule;
class EditUI;
class Button;
class MapClass;
class Tile;
class Matter;
class Actor;
class ObjectManager;
class Data;
class EditController
{
// 인스턴스
private:
	KeyModule * key;
	EditUI * ui;
	Button* tBtn;
	MapClass* editMap;
	ObjectManager* manager;
//Select
private:
	struct Select {
		Tile* tile;
		Matter* matter;
		Actor* actor;
	};

	Select _select;

//SaveLoad
private:
	Data * data;
//MAPMOVE
private:
	D2D_POINT_2L camPivot;
	bool isMove;

public:
	EditController();
	~EditController();

	HRESULT Init(EditUI* ui, MapClass* editMap, ObjectManager* manager);
	void Release(void);
	void Update(void);
	void Render(void);

	void MapMove(void);
	void ButtonUpdate(void);
	void UIMove(void);
	void SelectPalette(void);
	void SetObject(void);
	void DeleteObject(void);
	void SaveObject(void);
	void LoadObject(void);

};

