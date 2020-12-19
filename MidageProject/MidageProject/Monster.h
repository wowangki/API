#pragma once
#include <map>
#include "Actor.h"

enum Monster_Type {
	MON_BAT,
	MON_BEAR,
	MON_MYSTIC,
	MON_WHALE,
	MON_AQUADEMON,
	MON_GARGOYLE,
	MON_SERPENT,
	MON_SUCCUBUS,
	MON_DRAGON,
	MON_WYRM,
	MON_KNIGHT,
	MON_HOBIT,
	MON_KITCAT
};

enum Monster_Properties {
	MON_EARTH,
	MON_WATER,
	MON_FIRE,
	MON_WIND
};


class Monster : public Actor
{
private:
	Monster_Properties monProperties;

private:
	typedef std::map<int, string> _mMImgKey;
	typedef _mMImgKey::iterator _mIter;
	_mMImgKey mImgKey;

private:
	float moveTime;

private:
	UINT gHp;
	D2D_POINT_2U hpGrow;
	D2D_POINT_2U strengthGrow;
	D2D_POINT_2U staminGrow;
	D2D_POINT_2U dexGrow;

public:
	Monster();
	Monster(MapClass* map, ObjectManager* manager);
	~Monster();

	HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, Monster_Properties monProperties, int type, GameObject_Kind kind = ACTOR);
	void Release(void) override;
	void Update(void) override;
	void BattleUpdate(void) override;
	void Render(void) override;

	HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, Monster_Properties monProperties, int type, GameObject_Kind kind = ACTOR);

	void SetName(int type) override;
	void ChangeImage(void) override;
	void CreateMImg(string name);
	string FindMImg(void);

	void MoveMonster(void);

	Monster_Properties GetProperties(void) { return monProperties; }

	void StatusInit(void);
	void StatusInit(int level);
	void StatusInit(int vital, int strength, int stamin, int dexterity) override;
	void StatusSet(int level);
	void StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint) override;
	void GrowStatusInit(D2D_POINT_2U hpGrow, D2D_POINT_2U strength, D2D_POINT_2U stamin, D2D_POINT_2U dexterity);
	void StatusUp(void);

	void SetMaxHp(void) override { maxHp = 10 + (vital * gHp); }
	void SetAtk(void) override { atk = 1 + strength; }
	void SetDef(void) override { def = 1 + stamin; }
	void SetSpd(void) override { spd = 1 + dexterity; }
};

