#pragma once
#include "Actor.h"
#include "SearchObject.h"

enum Player_Gender {
	PLAYER_MALE,
	PLAYER_FEMALE
};

class Player : public Actor
{
private:
	struct World_Info {
		string worldName;
		int worldNum;
	};

	World_Info worldInfo;
	
	bool isMapMove;
	bool isEngage;
	class Monster* engageMonster;

public:
	Player();
	Player(MapClass* map, ObjectManager* manager);
	~Player();

	HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind) override;
	void Release(void) override;
	void Update(void) override;
	void BattleUpdate(void) override;
	void Render(void) override;

	HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind = ACTOR) override;

	void SetName(int type) override;
	void ChangeImage(void);

	//속성 설정
	void StatusInit(int vital, int strength, int stamin, int dexterity) override;
	void StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint) override;

	// 행동 설정
	void MoveMap(void);
	void Engage(void);

	// Getter & Setter
	SearchObject* GetSearch() { return search; }
	string GetWorldInfoName(void) { return worldInfo.worldName; }
	int GetWorldNum(void) { return worldInfo.worldNum; }
	bool GetIsMoveMap(void) { return isMapMove; }
	bool GetEngage(void) { return isEngage; }
	Monster* GetEngageMonster(void) { return engageMonster;}
	
	void SetName(string name) { this->name = name; }
	void SetMaxHp(void) override { maxHp = 50 + (vital * 10); }
	void SetAtk(void) override { atk = 5 + strength; }
	void SetDef(void) override { def = 5 + stamin; }
	void SetSpd(void) override { spd = 5 + dexterity; }
	void SetWorldInfoName(string worldInfo) { this->worldInfo.worldName = worldInfo; }
	void SetWorldInfoNum(int num) { this->worldInfo.worldNum = num; }
	void SetEngage(bool isEngage) { this->isEngage = isEngage; }
	
};

