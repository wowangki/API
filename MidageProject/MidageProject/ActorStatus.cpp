#include "stdafx.h"
#include "Actor.h"
#include "PropertyBar.h"

void Actor::StatusInit(int vital, int strength, int stamin, int dexterity)
{
	this->lv = 1;
	this->exp = 0;
	this->maxExp = 2 * (lv * 4);
	this->vital = vital;
	this->strength = strength;
	this->stamin = stamin;
	this->dexterity = dexterity;
	SetMaxHp();
	this->hp = maxHp;
	mp = maxMp = 100;
	SetAtk();
	SetDef();
	SetSpd();
	statusBar = new PropertyBar(this);
	statusBar->Init();
}

void Actor::StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint)
{
	this->lv = level;
	this->exp = exp;
	this->maxExp = 2 * (lv * 4);
	this->vital = vital;
	this->strength = strength;
	this->stamin = stamin;
	this->dexterity = dexterity;
	this->hp = hp;
	this->mp = maxMp = mp;
	SetMaxHp();
	SetAtk();
	SetDef();
	SetSpd();
	this->statPoint = statPoint;
	LevelUp();
	statusBar = new PropertyBar(this);
	statusBar->Init();
}

void Actor::SetProperty(int earth, int water, int fire, int wind)
{
	this->earthPoint = earth;
	this->waterPoint = water;
	this->firePoint = fire;
	this->windPoint = wind;
}

void Actor::LevelUp(void)
{
	while (true) {
		if (exp < maxExp) break;
		this->lv++;
		this->exp -= maxExp;
		this->maxExp = 2 * (lv * 4);
		this->statPoint += 4;
		this->hp = maxHp;
	}
}


void Actor::StatusUp(string statName)
{
	if (this->propertyPoint > 0) {
		if (statName == "EARTH") {
			this->propertyPoint--;
			this->earthPoint++;
		}
		else if (statName == "WATER") {
			this->propertyPoint--;
			this->waterPoint++;
		}
		else if (statName == "FIRE") {
			this->propertyPoint--;
			this->firePoint++;
		}
		else if (statName == "WIND") {
			this->propertyPoint--;
			this->windPoint++;
		}
	}
	
	if (this->statPoint > 0) {
		if (statName == "VIT") {
			this->statPoint--;
			this->vital++;
			SetMaxHp();
			this->hp = this->maxHp;
		}
		else if (statName == "STR") {
			this->statPoint--;
			this->strength++;
			SetAtk();
		}
		else if (statName == "STA") {
			this->statPoint--;
			this->stamin++;
			SetDef();
		}
		else if (statName == "DEX") {
			this->statPoint--;
			this->dexterity++;
			SetSpd();
		}
	}
}

void Actor::StatusDown(string statName)
{
	if (this->propertyPoint <= 10) {
		if (statName == "EARTH") {
			if (earthPoint <= 0) return;
			this->propertyPoint++;
			this->earthPoint--;
		}
		else if (statName == "WATER") {
			if (waterPoint <= 0) return;
			this->propertyPoint++;
			this->waterPoint--;
		}
		else if (statName == "FIRE") {
			if (firePoint <= 0) return;
			this->propertyPoint++;
			this->firePoint--;
		}
		else if (statName == "WIND") {
			if (windPoint <= 0) return;
			this->propertyPoint++;
			this->windPoint--;
		}
	}

	if (statName == "VIT") {
		if (this->vital <= 0) return;
		this->statPoint++;
		this->vital--;
		SetMaxHp();
		this->hp = this->maxHp;
	}
	else if (statName == "STR") {
		if (this->strength <= 0) return;
		this->statPoint++;
		this->strength--;
		SetAtk();
	}
	else if (statName == "STA") {
		if (this->stamin <= 0) return;
		this->statPoint++;
		this->stamin--;
		SetDef();
	}
	else if (statName == "DEX") {
		if (this->dexterity <= 0) return;
		this->statPoint++;
		this->dexterity--;
		SetSpd();
	}
}