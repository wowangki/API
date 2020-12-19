#pragma once
#include <vector>

enum Astar_Type {
	MOVE_DEFAULT,
	MOVE_START,
	MOVE_END
};

class GameObject;
class Actor;
class MapClass;
class ObjectManager;
class AStar
{
private:
	Actor* actor;
	Actor* target;
	MapClass* map;

private:
	ObjectManager* manager;

public:
	struct MoveSearch {
		D2D_POINT_2L id;
		D2D_POINT_2F pos;
		D2D_POINT_2F rymPos[4];
		Astar_Type astarType;
		bool isOpen;
		float distance;
	};

	typedef vector<vector<MoveSearch>> _vMove;
	typedef vector<MoveSearch> vPath;
private:
	_vMove vTotalPath;
	vPath vOpenPath;
	vPath vPathResult;
	vPath endResult;

	MoveSearch* start;
	MoveSearch* end;
	MoveSearch* current;

	int fieldMoveSize;

private:
	vector<Actor*> vTarget;

public:
	AStar();
	AStar(Actor* actor, MapClass* map, int size);
	~AStar();

	void Update(void);
	void BattleUpdate(void);
	void Render(void);
	
	//FieldMove
	void FindTotalMovePath(void);
	void FindFieldEnd(void);
	//BattleMove
	void FindBattleMovePath(void);
	void SeleteTarget(void);
	void FindBattleEnd(void);

	//Find
	bool FindObject(void);

	//PathResult
	vPath addPathList(MoveSearch* current);
	void PathFinder(MoveSearch* current);

	//Clear
	void ClearAllPath(void) { vTotalPath.clear(); vOpenPath.clear(); vPathResult.clear(); }
	void ClearBattlePath(void) { vTotalPath.clear();  vOpenPath.clear(); vTarget.clear(); vPathResult.clear(); }
	void CheckEnd(void);

	Actor* GetTarget(void) { return target; }
	_vMove GetTotalPath(void) { return vTotalPath; }
	vPath GetPathResult(void) { return vPathResult; }
	MoveSearch* GetEnd(void) { return end; }

	void SetTarget(Actor* target) { this->target = target; }
	void SetEnd(MoveSearch* end) { this->end = end; }
};

