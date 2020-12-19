#pragma once
enum Box_Direction {
	BOX_LTOP,
	BOX_RTOP,
	BOX_LBOTTOM,
	BOX_RBOTTOM
};

class BattleFunction
{
private:
	class Actor* actor;
	class Actor* target;

private:
	struct InteractionBox {
		D2D_POINT_2L id;
		D2D_POINT_2F pos;
		D2D_POINT_2F rymPos[4];
		D2D_SIZE_F offset;
		int direction;
		bool isActive;
	};
	
	InteractionBox* attackBox;


public:
	BattleFunction(class Actor* actor);
	~BattleFunction();
	
	void CreateBoxPos(void);
	void IsInTarget(void);
	void Render(void);

	void Attacking(void);
	void DamageFunction(void);
	void PropertiesBonus(int* dmg);
	bool ChkAvoid(void);
	void GetExp(void);

	InteractionBox* GetAttackBox(void) { return attackBox; }
	Actor* GetTarget(void) { return target; }
	void SetAttackBox(InteractionBox* box) { this->attackBox = box; }
	void SetTarget(Actor* target) { this->target = target; }
};

