#include "stdafx.h"
#include "Player.h"
#include "MapClass.h"
#include "Tile.h"
#include "SearchObject.h"
#include "AStar.h"
#include "Monster.h"
#include "CommandUI.h"
#include "BattleFunction.h"
#include "Effect.h"

Player::Player()
{
	map = nullptr;
	manager = nullptr;
	search = nullptr;
}

Player::Player(MapClass * map, ObjectManager* manager)
{
	this->map = map;
	this->manager = manager;
}


Player::~Player()
{
}

HRESULT Player::Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	Actor::Init(id, frame, type, kind);
	actorKind = PLAYER;
	worldInfo.worldName = "";
	worldInfo.worldNum = 0;
	isMapMove = false;
	isEngage = false;
	comType = 0;
	searchSize = 7;
	pathNum = 0;
	search = new SearchObject(searchSize);
	search->Init(this, manager, map);
	astar = new AStar(this, map, searchSize);
	initDelayTime = delayTime = 250.0f;
	effect->Init("Effect_Hit");

	return S_OK;
}

void Player::Release(void)
{
	Actor::Release();
}

void Player::Update(void)
{
	Actor::Update();

	search->Update();

	if (!map) return;
	MoveMap();
	Engage();
}

void Player::BattleUpdate(void)
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

	switch (comType)
	{
	case COM_ATTACK_N: case COM_ATTACK_S:
		if (isTurn) {
			if (astar->GetTotalPath().empty()) astar->FindBattleMovePath();
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

void Player::Render(void)
{
	Actor::Render();
	if (isTurn && comType != COM_DEFAULT) astar->Render();
#pragma region test

	if (isEdit) {
		search->Render();
		//astar->Render();
	}
	
	//_RenderTarget->DrawLine(rymPos[0], rymPos[1], _Device->pDefaultBrush);
	//_RenderTarget->DrawLine(rymPos[0], rymPos[3], _Device->pDefaultBrush);
	//WCHAR idString[256];
	//static TCHAR idText[] = L"%d %d";
	//_stprintf_s(idString, idText, id.x, id.y);
	//_FONT->Render(idString, FRectMakeCenter(pos.x + _CAM->x, pos.y + _CAM->y, 30, 20));
	
	//for (int y = 0; y < 3; y++)
	//{
	//	for (int x = 0; x < 3; x++)
	//	{
	//		WCHAR tString[256];
	//		static TCHAR tText[] = L"%d %d";
	//		_stprintf_s(tString, tText, y, x);
	//		_FONT->Render(tString, FRectMakeCenter(searchIt[y][x].pos.x, searchIt[y][x].pos.y,
	//			offset.width, offset.height));
	//	}
	//}
#pragma endregion
}

HRESULT Player::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	Actor::PaletteInit(pos, frame, type, kind);
	actorKind = PLAYER;
	worldInfo.worldName = "";
	worldInfo.worldNum = 0;
	isMapMove = false;
	return S_OK;
}

void Player::SetName(int type)
{
	switch (type) {
	case PLAYER_MALE:
		name = "LAHARL";
		imgKey = "Laharl_IDLE";
		break;
	case PLAYER_FEMALE:
		name = "FLONNE";
		imgKey = "Flonne_IDLE";
		break;
	}

}

void Player::ChangeImage(void)
{
	switch (motion) {
	case ACTOR_IDLE:
		img = _IMAGE->FindImage("Laharl_IDLE");
		break;
	case ACTOR_MOVE:
		img = _IMAGE->FindImage("Laharl_MOVE");
		break;
	case ACTOR_ATTACK:
		img = _IMAGE->FindImage("Laharl_ATTACK_NORMAL");
		break;
	case ACTOR_DAMAGE:
		img = _IMAGE->FindImage("Laharl_DAMAGE");
		break;
	case ACTOR_GUARD:
		img = _IMAGE->FindImage("Laharl_GUARD");
		break;
	}
}

void Player::MoveMap(void)
{
	MapClass::_vMap temp = map->GetVMap();
	SearchObject::SearchIt (*tCol)[3] = search->GetCollisionSearch();

	for (int y = 0; y < COLLISIONSIZE; y++)
	{
		for (int x = 0; x < COLLISIONSIZE; x++)
		{
			if (id.x + (x - 1) < 0 ||
				id.y + (y - 1) < 0 ||
				id.x + (x - 1) > (int)temp.size() - 1 ||
				id.y + (y - 1) > (int)temp.size() - 1)
				continue;

			if (ISOInPoint(tCol[y][x].pos, temp[id.y + (y - 1)][id.x + (x - 1)]->GetRymPos())) {
				if (temp[id.y + (y - 1)][id.x + (x - 1)]->GetType() == TILE_ENTERANCE) {

					if (id.y + (y - 1) > 0 && id.x + (x - 1) < 2) {
						worldInfo.worldNum--;
						worldInfo.worldName = "World" + to_string(worldInfo.worldNum);
						id.x = map->GetMapSizeX() - id.x - 3;
						isMapMove = true;
						return;
					}
					else if (id.y + (y - 1) > 0 && id.x + (x - 1) > (int)temp.size() - 3) {
						worldInfo.worldNum++;
						worldInfo.worldName = "World" + to_string(worldInfo.worldNum);
						id.x = map->GetMapSizeX() - id.x;
						isMapMove = true;
						return;
					}
					else if (id.y + (y - 1) < 2 && id.x + (x - 1) > 0) {
						worldInfo.worldNum -= 3;
						worldInfo.worldName = "World" + to_string(worldInfo.worldNum);
						id.y = map->GetMapSizeY() - id.y - 3;
						isMapMove = true;
						return;
					}
					else if (id.y + (y - 1) > (int)temp.size() - 3 && id.x + (x - 1) > 0) {
						worldInfo.worldNum += 3;
						worldInfo.worldName = "World" + to_string(worldInfo.worldNum);
						id.y = map->GetMapSizeY() - id.y;
						isMapMove = true;
						return;
					}
				}
			}
		}
	}
}

void Player::Engage(void)
{
	SearchObject::SearchIt(*tCol)[3] = search->GetCollisionSearch();
	vector<GameObject*> temp = search->GetVObjectSearch();

	for (int y = 0; y < COLLISIONSIZE; y++)
	{
		for (int x = 0; x < COLLISIONSIZE; x++)
		{
			if (tCol[y][x].isInISO) continue;

			for (UINT i = 0; i < temp.size(); i++)
			{
				if (temp[i]->GetKind() != ACTOR) continue;
				if (ISOInISO(tCol[y][x].pos, tCol[y][x].rymPos, temp[i]->GetRymPos())) {
					isEngage = true;
					engageMonster = dynamic_cast<Monster*>(temp[i]);
					return;
				}
			}
		}
	}

}

void Player::StatusInit(int vital, int strength, int stamin, int dexterity)
{
	Actor::StatusInit(vital, strength, stamin, dexterity);
	statPoint = 20;
	propertyPoint = 10;
}

void Player::StatusSet(int level, int exp, int hp, int mp, int vital, int strength, int stamin, int dexterity, int statPoint)
{
	Actor::StatusSet(level, exp, hp, mp, vital, strength, stamin, dexterity, statPoint);
}
