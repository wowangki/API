#include "stdafx.h"
#include "Monster.h"
#include "ObjectManager.h"
#include "SearchObject.h"
#include "AStar.h"
#include "CommandUI.h"
#include "BattleFunction.h"

Monster::Monster()
{
	map = nullptr;
	manager = nullptr;
}

Monster::Monster(MapClass * map, ObjectManager* manager)
{
	this->map = map;
	this->manager = manager;
}


Monster::~Monster()
{
}

HRESULT Monster::Init(D2D_POINT_2L id, D2D_POINT_2L frame, Monster_Properties monProperties, int type, GameObject_Kind kind)
{
	this->monProperties = monProperties;
	Actor::Init(id, frame, type, kind);
	actorKind = MONSTER;

	search = new SearchObject(searchSize);
	search->Init(this, manager, map);
	astar = new AStar(this, map, searchSize);
	pathNum = 0;
	moveTime = 1.5f;
	gHp = 10;
	hpGrow = { 0,0 };
	strengthGrow = { 0,0 };
	staminGrow = { 0,0 };
	dexGrow = { 0,0 };
	StatusInit();

	return S_OK;
}

void Monster::Release(void)
{
	Actor::Release();
}

void Monster::Update(void)
{
	Actor::Update();

	if (map == nullptr) return;
	
	if (!isCull) {
		search->Update();
		astar->Update();
		MoveMonster();
	}
}

void Monster::BattleUpdate(void)
{
	Actor::Update();
	search->Update();

	if (!isAlive) return;

	if (FindIsTurnObject()) return;
	else {
		if (parameter && turnBoard) {
			MoveTimeBoard();
			CheckTurn();
		}
	}

	if (isTurn) comType = GetRandomInt(1, 1);

	switch (comType) {
	case COM_ATTACK_N: case COM_ATTACK_S:
		if (isTurn) {
			if (astar->GetTotalPath().empty()) {
				astar->FindBattleMovePath();
				astar->SeleteTarget();
			}
			if (astar->GetTarget()) {
				isTurn = false;
				delayTime = initDelayTime;
				if (comType == COM_ATTACK_N) delayTime += 100.0f;
				else if (comType == COM_ATTACK_S) delayTime += 200.0f;
			}
		}
		else {
			if (isExcute) {
				astar->BattleUpdate();
				BattleAttack();
			}
			if (!astar->GetTarget()) {
				BattleMove();
			}
		}
		break;
	case COM_GUARD:
		if (isTurn) {
			isTurn = false;
			delayTime = initDelayTime;
			delayTime -= 50.0f;
		}
		break;
	case COM_AVOID:
		if (isTurn) {
			isTurn = false;
			delayTime = initDelayTime;
			delayTime -= 50.0f;
		}
		break;
	}
	
}

void Monster::Render(void)
{
	Actor::Render();

	if (isEdit) {
		search->Render();
		astar->Render();
	}
	//search->Render();
	//astar->Render();
	//WCHAR idString[256];
	//static TCHAR idText[] = L"%d";
	//_stprintf_s(idString, idText, lv);
	//_FONT->Render(idString, rc);

	//WCHAR idString[256];
	//static TCHAR idText[] = L"%d";
	//_stprintf_s(idString, idText, pathNum);
	//_FONT->Render(idString, rc);
	//
	//if (!astar->GetPathResult().empty()) {
	//	if (pathNum >= astar->GetPathResult().size()) return;
	//	WCHAR sTemp[256];
	//	static TCHAR tText[] = L"%.2f";
	//	_stprintf_s(sTemp, tText, pos.x - astar->GetPathResult()[pathNum].pos.x);
	//	_FONT->Render(sTemp, FRectMake(rc.left, rc.top + 50, rc.right, rc.bottom));
	//	WCHAR ssTemp[256];
	//	static TCHAR ttText[] = L"%.2f";
	//	_stprintf_s(ssTemp, ttText, pos.y - astar->GetPathResult()[pathNum].pos.y);
	//	_FONT->Render(ssTemp, FRectMake(rc.left, rc.top + 100, rc.right, rc.bottom));
	//}
		
}

HRESULT Monster::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, Monster_Properties monProperties, int type, GameObject_Kind kind)
{
	this->monProperties = monProperties;
	Actor::PaletteInit(pos, frame, type);
	actorKind = MONSTER;

	return S_OK;
}
