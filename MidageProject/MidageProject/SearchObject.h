#pragma once
#include <vector>
#define COLLISIONSIZE 3

class GameObject;
class Actor;
class ObjectManager;
class MapClass;
class SearchObject
{
private:
	Actor* actor;
	ObjectManager* manager;
	MapClass* map;

public:
	struct SearchIt {
		D2D_POINT_2L id;
		D2D_POINT_2F pos;
		D2D_POINT_2F rymPos[4];
		// 장애물이 있으면 true 없으면 false;
		bool isInISO;
	};

private:
	SearchIt collisionSearch[COLLISIONSIZE][COLLISIONSIZE];
	SearchIt attackSearch;
	vector<GameObject*> vObjectSearch;

	D2D_POINT_2F rymPos[4];
	
	int size;
	int objectSearchSize;

public:
	SearchObject(int size);
	~SearchObject();

	HRESULT Init(Actor* actor, ObjectManager* manager, MapClass* map);
	void Update(void);
	void Render(void);

	void CreateCollisionSearch(void);

	void CollisionSearch(void);
	void ObjectSearch(void);
	void AttackSearch(void);

	int GetSize(void) { return size; }

	SearchIt (*GetCollisionSearch(void))[3] { return collisionSearch; }
	D2D_POINT_2F* GetRymPos(void) { return rymPos; }
	vector<GameObject*> GetVObjectSearch(void) { return vObjectSearch; }

};