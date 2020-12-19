#include "stdafx.h"
#include "Monster.h"
#include "SearchObject.h"
#include "Effect.h"

void Monster::StatusInit(void)
{
	int level = 0;
	switch (type) {
	case MON_BAT:
		level = GetRandomInt(1, 5);
		GrowStatusInit({ 4, 6 }, { 0, 1 }, { 0, 1 }, { 0, 2 });
		effect->Init("Effect_Claw");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 1, 0, 2);
			StatusSet(level);
			SetProperty(6, 4, 0, 0);
			break;
		case MON_WATER:
			StatusInit(0, 0, 0, 2);
			StatusSet(level);
			SetProperty(5, 5, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 0, 1, 3);
			StatusSet(level);
			SetProperty(0, 0, 7, 3);
			break;
		case MON_WIND:
			StatusInit(0, 0, 1, 4);
			StatusSet(level);
			SetProperty(0, 0, 0, 10);
			break;
		}
		break;
	case MON_BEAR:
		level = GetRandomInt(2, 8);
		GrowStatusInit({ 5, 6 }, { 0, 2 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Claw");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 3, 4, 0);
			StatusSet(level);
			SetProperty(6, 4, 0, 0);
			break;
		case MON_WATER:
			StatusInit(0, 3, 3, 1);
			StatusSet(level);
			SetProperty(0, 3, 7, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 5, 1, 2);
			StatusSet(level);
			SetProperty(0, 4, 6, 0);
			break;
		case MON_WIND:
			break;
		}
		break;
	case MON_MYSTIC:
		level = GetRandomInt(15, 20);
		GrowStatusInit({ 6, 9 }, { 0, 2 }, { 0, 1 }, { 0, 2 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 5, 1, 4);
			StatusSet(level);
			SetProperty(6, 4, 0, 0);
			break;
		case MON_WATER:
			StatusInit(1, 5, 0, 5);
			StatusSet(level);
			SetProperty(8, 2, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 7, 0, 5);
			StatusSet(level);
			SetProperty(0, 3, 7, 0);
			break;
		case MON_WIND:
			StatusInit(0, 5, 0, 6);
			StatusSet(level);
			SetProperty(0, 0, 2, 8);
			break;
		}
		break;
	case MON_WHALE:
		level = GetRandomInt(10, 16);
		GrowStatusInit({ 6, 10 }, { 0, 1 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 4, 5, 0);
			StatusSet(level);
			SetProperty(6, 4, 0, 0);
			break;
		case MON_WATER:
			StatusInit(0, 3, 4, 0);
			StatusSet(level);
			SetProperty(0, 10, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 5, 3, 0);
			StatusSet(level);
			SetProperty(0, 2, 8, 0);
			break;
		case MON_WIND:
			StatusInit(0, 3, 4, 0);
			StatusSet(level);
			SetProperty(6, 0, 0, 4);
			break;
		}
		break;
	case MON_AQUADEMON:
		level = GetRandomInt(15, 22);
		GrowStatusInit({ 6, 9 }, { 0, 2 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(2, 4, 6, 0);
			StatusSet(level);
			SetProperty(7, 3, 0, 0);
			break;
		case MON_WATER:
			StatusInit(2, 6, 5, 0);
			StatusSet(level);
			SetProperty(0, 8, 2, 0);
			break;
		case MON_FIRE:
			StatusInit(1, 5, 4, 1);
			StatusSet(level);
			SetProperty(0, 3, 7, 0);
			break;
		case MON_WIND:
			StatusInit(1, 5, 4, 3);
			StatusSet(level);
			SetProperty(0, 0, 4, 6);
			break;
		}
		break;
	case MON_GARGOYLE:
		level = GetRandomInt(10, 14);
		GrowStatusInit({ 5, 7 }, { 0, 1 }, { 0, 2 }, { 0, 2 });
		effect->Init("Effect_Claw");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 5, 3);
			StatusSet(level);
			SetProperty(8, 0, 0, 2);
			break;
		case MON_WATER:
			StatusInit(1, 1, 5, 3);
			StatusSet(level);
			SetProperty(3, 7, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 3, 3, 4);
			StatusSet(level);
			SetProperty(0, 0, 6, 4);
			break;
		case MON_WIND:
			StatusInit(0, 2, 3, 5);
			StatusSet(level);
			SetProperty(2, 0, 0, 8);
			break;
		}
		break;
	case MON_SERPENT:
		level = GetRandomInt(20, 24);
		GrowStatusInit({ 6, 10 }, { 0, 2 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Claw");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(2, 5, 5, 2);
			StatusSet(level);
			SetProperty(9, 1, 0, 0);
			break;
		case MON_WATER:
			StatusInit(3, 4, 5, 2);
			StatusSet(level);
			SetProperty(0, 8, 2, 0);
			break;
		case MON_FIRE:
			StatusInit(3, 5, 4, 2);
			StatusSet(level);
			SetProperty(0, 4, 6, 0);
			break;
		case MON_WIND:
			StatusInit(2, 4, 4, 4);
			StatusSet(level);
			SetProperty(0, 0, 3, 7);
			break;
		}
		break;
	case MON_SUCCUBUS:
		level = GetRandomInt(18, 22);
		GrowStatusInit({ 5, 7 }, { 0, 2 }, { 0, 1 }, { 0, 3 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 2, 5);
			StatusSet(level);
			SetProperty(7, 3, 0, 0);
			break;
		case MON_WATER:
			StatusInit(0, 2, 1, 5);
			StatusSet(level);
			SetProperty(4, 6, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 4, 0, 6);
			StatusSet(level);
			SetProperty(0, 0, 10, 0);
			break;
		case MON_WIND:
			StatusInit(0, 3, 0, 7);
			StatusSet(level);
			SetProperty(0, 0, 5, 5);
			break;
		}
		break;
	case MON_DRAGON:
		level = GetRandomInt(29, 35);
		GrowStatusInit({ 8, 11 }, { 0, 3 }, { 0, 3 }, { 0, 3 });
		effect->Init("Effect_Claw");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(3, 4, 7, 4);
			StatusSet(level);
			SetProperty(5, 0, 0, 5);
			break;
		case MON_WATER:
			StatusInit(4, 5, 5, 4);
			StatusSet(level);
			SetProperty(0, 8, 2, 0);
			break;
		case MON_FIRE:
			StatusInit(3, 8, 2, 5);
			StatusSet(level);
			SetProperty(0, 0, 7, 3);
			break;
		case MON_WIND:
			StatusInit(3, 4, 3, 8);
			StatusSet(level);
			SetProperty(0, 0, 0, 10);
			break;
		}
		break;
	case MON_WYRM:
		level = GetRandomInt(25, 30);
		GrowStatusInit({ 6, 10 }, { 0, 2 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(3, 3, 6, 3);
			StatusSet(level);
			SetProperty(10, 0, 0, 0);
			break;
		case MON_WATER:
			StatusInit(3, 4, 5, 3);
			StatusSet(level);
			SetProperty(2, 8, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(2, 6, 3, 4);
			StatusSet(level);
			SetProperty(0, 0, 10, 0);
			break;
		case MON_WIND:
			StatusInit(3, 4, 3, 6);
			StatusSet(level);
			SetProperty(0, 0, 3, 7);
			break;
		}
		break;
	case MON_KNIGHT:
		level = GetRandomInt(22, 28);
		GrowStatusInit({ 6, 10 }, { 0, 2 }, { 0, 3 }, { 0, 1 });
		effect->Init("Effect_Slash");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 4, 8, 0);
			StatusSet(level);
			SetProperty(10, 0, 0, 0);
			break;
		case MON_WATER:
			StatusInit(1, 1, 11, 0);
			StatusSet(level);
			SetProperty(0, 8, 2, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 7, 7, 0);
			StatusSet(level);
			SetProperty(0, 0, 10, 0);
			break;
		case MON_WIND:
			StatusInit(0, 5, 6, 2);
			StatusSet(level);
			SetProperty(0, 0, 3, 7);
			break;
		}
		break;
	case MON_HOBIT:
		level = GetRandomInt(8, 15);
		GrowStatusInit({ 5, 7 }, { 0, 1 }, { 0, 2 }, { 0, 1 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 2, 1);
			StatusSet(level);
			SetProperty(8, 2, 0, 0);
			break;
		case MON_WATER:
			StatusInit(0, 2, 1, 1);
			StatusSet(level);
			SetProperty(0, 6, 4, 0);
			break;
		case MON_FIRE:
			StatusInit(0, 2, 1, 2);
			StatusSet(level);
			SetProperty(0, 0, 5, 5);
			break;
		case MON_WIND:
			StatusInit(0, 1, 2, 2);
			StatusSet(level);
			SetProperty(4, 0, 0, 6);
			break;
		}
		break;
	case MON_KITCAT:
		level = GetRandomInt(13, 20);
		GrowStatusInit({ 5, 8 }, { 0, 3 }, { 0, 2 }, { 0, 3 });
		effect->Init("Effect_Hit");
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 3, 1, 5);
			StatusSet(level);
			SetProperty(7, 0, 0, 3);
			break;
		case MON_WATER:
			StatusInit(2, 4, 0, 4);
			StatusSet(level);
			SetProperty(4, 6, 0, 0);
			break;
		case MON_FIRE:
			StatusInit(1, 5, 0, 5);
			StatusSet(level);
			SetProperty(0, 0, 7, 3);
			break;
		case MON_WIND:
			StatusInit(1, 4, 0, 6);
			StatusSet(level);
			SetProperty(0, 0, 1, 9);
			break;
		}
		break;
	}
}

void Monster::StatusInit(int level)
{
	int lv = GetRandomInt(level - 6, level);
	if (lv <= 0) lv = 1;

	switch (type) {
	case MON_BAT:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 1, 0, 2);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(0, 0, 0, 2);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 0, 1, 3);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 0, 1, 4);
			StatusSet(lv);
			break;
		}
		break;
	case MON_BEAR:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 3, 4, 0);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(0, 3, 3, 1);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 5, 1, 2);
			StatusSet(lv);
			break;
		case MON_WIND:
			break;
		}
		break;
	case MON_MYSTIC:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 5, 1, 4);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(1, 5, 0, 5);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 7, 0, 5);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 5, 0, 6);
			StatusSet(lv);
			break;
		}
		break;
	case MON_WHALE:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 4, 5, 0);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(0, 3, 4, 0);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 5, 3, 0);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 3, 4, 0);
			StatusSet(lv);
			break;
		}
		break;
	case MON_AQUADEMON:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(2, 4, 6, 0);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(2, 6, 5, 0);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(1, 5, 4, 1);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(1, 5, 4, 3);
			StatusSet(lv);
			break;
		}
		break;
	case MON_GARGOYLE:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 5, 3);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(1, 1, 5, 3);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 3, 3, 4);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 2, 3, 5);
			StatusSet(lv);
			break;
		}
		break;
	case MON_SERPENT:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(2, 5, 5, 2);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(3, 4, 5, 2);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(3, 5, 4, 2);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(2, 4, 4, 4);
			StatusSet(lv);
			break;
		}
		break;
	case MON_SUCCUBUS:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 2, 5);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(0, 2, 1, 5);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 4, 0, 6);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 3, 0, 7);
			StatusSet(lv);
			break;
		}
		break;
	case MON_DRAGON:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(3, 4, 7, 4);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(4, 5, 5, 4);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(3, 8, 2, 5);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(3, 4, 3, 8);
			StatusSet(lv);
			break;
		}
		break;
	case MON_WYRM:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(3, 3, 6, 3);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(3, 4, 5, 3);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(2, 6, 3, 4);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(3, 4, 3, 6);
			StatusSet(lv);
			break;
		}
		break;
	case MON_KNIGHT:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 4, 8, 0);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(1, 1, 11, 0);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 7, 7, 0);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 5, 6, 2);
			StatusSet(lv);
			break;
		}
		break;
	case MON_HOBIT:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(0, 2, 2, 1);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(0, 2, 1, 1);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(0, 2, 1, 2);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(0, 1, 2, 2);
			StatusSet(lv);
			break;
		}
		break;
	case MON_KITCAT:
		switch (monProperties) {
		case MON_EARTH:
			StatusInit(1, 3, 1, 5);
			StatusSet(lv);
			break;
		case MON_WATER:
			StatusInit(2, 4, 0, 4);
			StatusSet(lv);
			break;
		case MON_FIRE:
			StatusInit(1, 5, 0, 5);
			StatusSet(lv);
			break;
		case MON_WIND:
			StatusInit(1, 4, 0, 6);
			StatusSet(lv);
			break;
		}
		break;
	}
}

void Monster::StatusInit(int vital, int strength, int stamin, int dexterity)
{
	Actor::StatusInit(vital, strength, stamin, dexterity);
	statPoint = 0;
	propertyPoint = 0;
}

void Monster::StatusSet(int level)
{
	while (true)
	{
		if (this->lv == level) break;
		StatusUp();
		hp = maxHp;
		lv++;
		this->maxExp = 2 * (lv * 4);
	}

}

void Monster::StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint)
{
	Actor::StatusSet(level, exp, hp, mp, vital, strength, stamin, dexterity, statPoint);
}

void Monster::GrowStatusInit(D2D_POINT_2U hpGrow, D2D_POINT_2U strength, D2D_POINT_2U stamin, D2D_POINT_2U dexterity)
{
	this->hpGrow = hpGrow;
	this->strengthGrow = strength;
	this->staminGrow = stamin;
	this->dexGrow = dexterity;
}

void Monster::StatusUp(void)
{
	this->vital++;
	gHp = GetRandomInt(hpGrow.x, hpGrow.y);
	this->strength += GetRandomInt(strengthGrow.x, strengthGrow.y);
	this->stamin += GetRandomInt(staminGrow.x, staminGrow.y);
	this->dexterity += GetRandomInt(dexGrow.x, dexGrow.y);

	SetMaxHp();
	SetAtk();
	SetDef();
	SetSpd();
}

