#include "stdafx.h"
#include "BattleFunction.h"
#include "Actor.h"
#include "CommandUI.h"
#include "TurnParameter.h"
#include "AStar.h"
#include "Effect.h"

BattleFunction::BattleFunction(Actor * actor)
{
	this->actor = actor;
	attackBox = nullptr;
}

BattleFunction::~BattleFunction()
{
}


void BattleFunction::CreateBoxPos(void)
{
	attackBox = new InteractionBox;
	attackBox->id = actor->GetId();
	attackBox->offset = actor->GetOffset();
	bool isRight = actor->GetIsRight();
	bool isBottom = actor->GetFrame().y;


	if (isRight) {
		if (!isBottom) {
			attackBox->direction = BOX_RBOTTOM;
			attackBox->id.x++;
			attackBox->pos = ISOPointMake(attackBox->id, attackBox->offset);
			RymBusPointMake(attackBox->pos, attackBox->rymPos, attackBox->offset);
		}
		else {
			attackBox->direction = BOX_RTOP;
			attackBox->id.y--;
			attackBox->pos = ISOPointMake(attackBox->id, attackBox->offset);
			RymBusPointMake(attackBox->pos, attackBox->rymPos, attackBox->offset);
		}
	}
	else {
		if (!isBottom) {
			attackBox->direction = BOX_LBOTTOM;
			attackBox->id.y++;
			attackBox->pos = ISOPointMake(attackBox->id, attackBox->offset);
			RymBusPointMake(attackBox->pos, attackBox->rymPos, attackBox->offset);
		}
		else {
			attackBox->direction = BOX_LTOP;
			attackBox->id.x--;
			attackBox->pos = ISOPointMake(attackBox->id, attackBox->offset);
			RymBusPointMake(attackBox->pos, attackBox->rymPos, attackBox->offset);
		}
	}
}

void BattleFunction::IsInTarget(void)
{
	if (target == nullptr) return;

	if (ISOInPoint(target->GetPos(), attackBox->rymPos)) {
		actor->SetIsInBattle(true);
		actor->GetEffect()->SetPos(target);
		if (target->GetComType() == COM_GUARD || target->GetComType() == COM_AVOID) {
			target->SetIsInBattle(true);
			if (actor->GetPos().x > target->GetPos().x) target->SetIsRight(true);
			else if (actor->GetPos().x < target->GetPos().x) target->SetIsRight(false);

			if (actor->GetPos().y > target->GetPos().y) target->SetFrame({ 0, 0 });
			else if (actor->GetPos().y < target->GetPos().y) target->SetFrame({ 0, 1 });
		}
		return;
	}
	else {
		target = nullptr;
		return;
	}
}

void BattleFunction::Render(void)
{
	if(attackBox)
	DrawISO(attackBox->rymPos, "BLACK");
}

void BattleFunction::Attacking(void)
{
	if (target == nullptr) return;
	if (actor->GetComType() == COM_ATTACK_N) {
		if (!target->GetIsInBattle()) {
			target->SetIsInBattle(true);
			
			if (actor->GetPos().x > target->GetPos().x) target->SetIsRight(true);
			else if (actor->GetPos().x < target->GetPos().x) target->SetIsRight(false);
			
			if (actor->GetPos().y > target->GetPos().y) target->SetFrame({ 0, 0 });
			else if (actor->GetPos().y < target->GetPos().y) target->SetFrame({ 0, 1 });
		}
		else {
			target->SetIsInBattle(false);
		}
	}
	else if (actor->GetComType() == COM_ATTACK_S) {
		if (!target->GetIsInBattle()) {
			target->SetIsInBattle(true);
			
			if (actor->GetPos().x > target->GetPos().x) target->SetIsRight(true);
			else if (actor->GetPos().x < target->GetPos().x) target->SetIsRight(false);

			if (actor->GetPos().y > target->GetPos().y) target->SetFrame({ 0, 0 });
			else if (actor->GetPos().y < target->GetPos().y) target->SetFrame({ 0, 1 });
		}
		else {
			target->SetIsInBattle(false);
		}

		if (target->GetComType() != COM_GUARD) {
			target->GetTurnBoard()->pos.x -= 100.0f;
			if (target->GetTurnBoard()->pos.x < target->GetParameter()->GetParmeter()[0].pos.x)
				target->GetTurnBoard()->pos.x = target->GetParameter()->GetParmeter()[0].pos.x;

			target->GetBattleBox()->target = nullptr;
			target->GetAstar()->ClearBattlePath();
			target->GetAstar()->SetTarget(nullptr);
			target->GetAstar()->SetEnd(nullptr);
			target->SetComType(COM_DEFAULT);

			target->SetIsTurn(false);
			target->SetIsReady(false);
			target->SetIsExcute(false);
		}
	}

	DamageFunction();
}

void BattleFunction::DamageFunction(void)
{
	if (target->GetComType() == COM_AVOID) return;

	int dmg = GetRandomInt(actor->GetAtk(), actor->GetAtk() + 3);
	int def = target->GetDef() * 0.25f;

	if (actor->GetComType() == COM_ATTACK_S) dmg *= 1.2f;
	if (target->GetComType() == COM_GUARD) def *= 3.0f;

	int totalDmg = dmg - def;

	PropertiesBonus(&totalDmg);

	if (totalDmg < 0) totalDmg = 1;

	if (ChkAvoid()) target->SetHp(target->GetHp(), totalDmg);
	
	if (target->GetHp() <= 0) target->SetIsAlive(false);
	GetExp();
}

void BattleFunction::PropertiesBonus(int* dmg)
{
	float dmgBonus = 0;
	int aEarthP = actor->GetEarthPoint();
	int aWaterP = actor->GetWaterPoint();
	int aFireP = actor->GetFirePoint();
	int aWindP = actor->GetWindPoint();
	int tEarthP = target->GetEarthPoint();
	int tWaterP = target->GetWaterPoint();
	int tFireP = target->GetFirePoint();
	int tWindP = target->GetWindPoint();

	if (aEarthP != 0 && tWaterP != 0) {
		if (aEarthP >= tWaterP) dmgBonus += 0.25f;
		else dmgBonus += 0.125f;
	}
	if (aWaterP != 0 && tFireP != 0) {
		if (aWaterP >= tFireP) dmgBonus += 0.25f;
		else dmgBonus += 0.125f;
	}
	if (aFireP != 0 && tWindP != 0) {
		if (aFireP >= tWindP) dmgBonus += 0.25f;
		else dmgBonus += 0.125f;
	}
	if (aWindP != 0 && tEarthP != 0) {
		if (aWindP >= tEarthP) dmgBonus += 0.25f;
		else dmgBonus += 0.125f;
	}

	if (aEarthP != 0 && tWindP != 0) {
		if (aEarthP < tWindP) dmgBonus -= 0.25f;
		else dmgBonus -= 0.125f;
	}
	if (aWaterP != 0 && tEarthP != 0) {
		if (aWaterP < tEarthP) dmgBonus -= 0.25f;
		else dmgBonus -= 0.125f;
	}
	if (aFireP != 0 && tWaterP != 0) {
		if (aFireP < tWaterP) dmgBonus -= 0.25f;
		else dmgBonus -= 0.125f;
	}
	if (aWindP != 0 && tEarthP != 0) {
		if (aWindP < tEarthP) dmgBonus -= 0.25f;
		else dmgBonus -= 0.125f;
	}


	*dmg *= 1 + dmgBonus;
}

bool BattleFunction::ChkAvoid(void)
{
	int avoid = abs(target->GetSpd() - actor->GetSpd());

	int rand = GetRandomInt(0, 100);

	if (rand > avoid) return true;
	else return false;
}

void BattleFunction::GetExp(void)
{
	if (target->GetIsAlive()) return;
	actor->SetExp(target->GetMaxExp());
}

