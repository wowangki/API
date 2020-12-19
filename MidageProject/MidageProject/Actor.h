#pragma once
#include "GameObject.h"

enum Actor_Kind {
	PLAYER,
	MONSTER
};

enum Actor_Motion {
	ACTOR_IDLE,
	ACTOR_MOVE,
	ACTOR_ATTACK,
	ACTOR_DAMAGE,
	ACTOR_GUARD
};

class Actor : public GameObject
{
protected:
	class MapClass * map;
	class ObjectManager* manager;
	class SearchObject* search;
	class AStar* astar;
	class BattleFunction* bFunction;
	class TurnParameter* parameter;
	class Observer* observer;
	class Effect* effect;
	class PropertyBar* statusBar;

protected:
	int lv;
	int exp;
	int maxExp;
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int atk;
	int def;
	int spd;

protected:
	int statPoint;
	int vital;
	int strength;
	int stamin;
	int dexterity;
protected:
	int earthPoint;
	int waterPoint;
	int firePoint;
	int windPoint;
	int propertyPoint;

protected:
	int motion;
	bool isRight;
	Actor_Kind actorKind;
	bool isInBattle;

protected:
	D2D_POINT_2F prePos;
	float moveSpeed;
	int searchSize;

protected:
	float initDelayTime;
	float delayTime;
	float excuteTime;
	int pathNum;
	int comType;
	bool isTurn;
	bool isReady;
	bool isExcute;

protected:
	struct TurnBoard
	{
		D2D_POINT_2F pos;
		D2D_SIZE_F size;
		D2D_SIZE_F arrowSize;
		ImageModule* actorImg;
		ImageModule* boardImg;
		ImageModule* arrowImg;
		float moveSpeed;
	};
	TurnBoard* turnBoard;

public:
	Actor();
	~Actor();

	virtual HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind = ACTOR) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void BattleUpdate(void) = 0;
	virtual void Render(void) override;

	virtual HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind = ACTOR) override;
	virtual void PaletteUpdate(void) override;
	virtual void PaletteRender(void) override;

	//속성 설정
	//1레벨 설정
	virtual void StatusInit(int vital, int strength, int stamin, int dexterity);
	//로드용
	virtual void StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint);
	virtual void SetProperty(int earth, int water, int fire, int wind);
	virtual void LevelUp(void);
	virtual void StatusUp(string statName);
	virtual void StatusDown(string statNam);

	//행동 설정
	virtual void FrameUpdate(void);
	virtual void SetMotion(void);
	virtual void ChangeImage(void) = 0;
	virtual void ExcuteTimeUpdate(void);
	virtual void BattleMove(void);
	virtual void BattleAttack(void);

	void ChangeId(void);

	//Battle Turn 설정
	virtual void CreateTimeBoard(class TurnParameter* parameter);
	virtual void MoveTimeBoard(void);
	virtual void CheckTurn(void);
	bool FindIsTurnObject(void);

	Actor_Kind GetActorKind(void) { return actorKind; }
	SearchObject * GetSearch(void) { return search; }
	int GetLv(void) { return lv; }
	int GetExp(void) { return exp; }
	int GetMaxExp(void) { return maxExp; }
	int GetHp(void) { return hp; }
	int GetMaxHp(void) { return maxHp; }
	int GetMp(void) { return mp; }
	int GetMaxMp(void) { return maxMp; }
	int GetAtk(void) { return atk; }
	int GetDef(void) { return def; }
	int GetSpd(void) { return spd; }
	int GetStatPoint(void) { return statPoint; }
	int GetVital(void) { return vital; }
	int GetStrength(void) { return strength; }
	int GetStamin(void) { return stamin; }
	int GetDexterity(void) { return dexterity; }
	int GetEarthPoint(void) { return earthPoint; }
	int GetWaterPoint(void) { return waterPoint; }
	int GetFirePoint(void) { return firePoint; }
	int GetWindPoint(void) { return windPoint; }
	int GetPropertyPoint(void) { return propertyPoint; }
	bool GetIsRight(void) { return isRight; }
	float GetMoveSpeed(void) { return moveSpeed; }
	float GetDelayTime(void) { return delayTime; }
	int GetComType(void) { return comType; }
	int GetMotion(void) { return motion; }
	bool GetIsInBattle(void) { return isInBattle; }
	bool GetIsTurn(void) { return isTurn; }
	bool GetIsReady(void) { return isReady; }
	bool GetIsExcute(void) { return isExcute; }
	AStar* GetAstar(void) { return astar; }
	ObjectManager* GetObjectManager(void) { return manager; }
	BattleFunction* GetBattleBox(void) { return bFunction; }
	TurnBoard* GetTurnBoard(void) { return turnBoard; }
	TurnParameter* GetParameter(void) { return parameter; }
	Effect* GetEffect(void) { return effect; }

	void SetExp(int exp) { this->exp = exp; }
	void SetHp(int hp, int dmg) { this->hp = hp - dmg; }
	void SetMp(int mp) { this->mp = mp; }
	void SetVital(int vital) { this->vital = vital; }
	void SetStrength(int strength) { this->strength = strength; }
	void SetStamin(int stmin) { this->stamin = stamin; }
	void SetDex(int dexterity) { this->dexterity = dexterity; }
	void SetIsRight(bool isRight) { this->isRight = isRight; }
	virtual void SetMaxHp(void) = 0;
	virtual void SetAtk(void) = 0;
	virtual void SetDef(void) = 0;
	virtual void SetSpd(void) = 0;
	void SetComType(int comType) { this->comType = comType; }
	void SetIsInBattle(bool isInBattle) { this->isInBattle = isInBattle; }
	void SetIsTurn(bool isTurn) { this->isTurn = isTurn; }
	void SetIsReady(bool isReady) { this->isReady = isReady; }
	void SetIsExcute(bool isExcute) { this->isExcute = isExcute; }
	void SetMotion(int motion) { this->motion = motion; }
	
};

