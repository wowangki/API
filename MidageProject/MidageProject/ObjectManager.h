#pragma once
#include <vector>

class ObjectManager
{
private:
	class MapClass * map;
	class EffectManager* effect;

private:
	vector<vector<class GameObject*>> vObject;

private:
	float sortTime;

public:
	ObjectManager();
	ObjectManager(class MapClass* map);
	~ObjectManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void BattleUpdate(void);
	void Render(void);

	void SetObject(class Matter* matter, class Tile* tile);
	void SetObject(class Actor* actor, class Tile* tile);
	void SetObject(string name, D2D_POINT_2L id, D2D_SIZE_F offset, D2D_POINT_2L frame, int objectKind, string typeName, int type, int kind, int properties);
	void SetObjectTimeBoard(class TurnParameter* parameter);
	void EraseObject(void);
	void DeleteObject(void);


	
	bool CheckOverLap(class GameObject* object);
	D2D_POINT_2L ChkIDOverLab(D2D_POINT_2L chkOverLab);
	void SortObject(UINT type, int start, int end);
	void SetEditMode(bool isEdit);

	vector<vector<class GameObject*>> GetVObject() { return vObject; }
	class Player* GetPlayer(void);
};