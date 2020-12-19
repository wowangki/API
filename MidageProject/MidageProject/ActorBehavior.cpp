#include "stdafx.h"
#include "Actor.h"
#include "MapClass.h"
#include "Tile.h"
#include "SearchObject.h"
#include "ObjectManager.h"
#include "TurnParameter.h"
#include "CommandUI.h"
#include "BattleFunction.h"
#include "AStar.h"

void Actor::ChangeId(void)
{
	MapClass::_vMap temp = map->GetVMap();

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			if (id.x + x < 0 || id.y + y < 0 ||
				id.x + x > (int)temp.size() - 1 ||
				id.y + y > (int)temp.size() - 1)
			{
				continue;
			}

			if (ISOInPoint(pos, temp[id.y + y][id.x + x]->GetRymPos()))
			{
				if (temp[id.y + y][id.x + x]->GetType() != TILE_LIQUDE) {
					id = temp[id.y + y][id.x + x]->GetId();
					return;
				}
			}
		}
	}


}

void Actor::CreateTimeBoard(TurnParameter * parameter)
{
	this->parameter = parameter;

	float rand = GetRandomFloat(0, 100);
	turnBoard = new TurnBoard;
	turnBoard->actorImg = img;
	turnBoard->boardImg = _IMAGE->FindImage("TimeBoard");
	turnBoard->arrowImg = _IMAGE->FindImage("TimeArrow");
	turnBoard->pos.x = this->parameter->GetParmeter()[0].pos.x + rand;
	turnBoard->pos.y = this->parameter->GetParmeter()[0].pos.y - 25;
	turnBoard->size.width = turnBoard->actorImg->GetFrameWidth() * 0.75f;
	turnBoard->size.height = turnBoard->actorImg->GetFrameHeight() * 0.75f;
	turnBoard->arrowSize.width = turnBoard->arrowImg->GetFrameWidth() * 0.3f;
	turnBoard->arrowSize.height = turnBoard->arrowImg->GetFrameHeight() * 0.5f;
}

void Actor::MoveTimeBoard(void)
{
	if (isTurn || isExcute) return;

	if (isReady && (comType == COM_DEFAULT)) {
		isReady = false;
		turnBoard->pos.x = parameter->GetParmeter()[0].pos.x;
	}

	turnBoard->moveSpeed = (parameter->GetParmeter()[0].size.width + parameter->GetParmeter()[1].size.width) / delayTime;
	
	turnBoard->pos.x += turnBoard->moveSpeed;
}

void Actor::CheckTurn(void)
{
	if (!isTurn && !isReady) {
		if (turnBoard->pos.x >=
			parameter->GetParmeter()[0].pos.x + parameter->GetParmeter()->size.width) {
			isTurn = true;
			isReady = true;
		}
	}
	else if (!isExcute) {
		if (turnBoard->pos.x >=
			parameter->GetParmeter()[1].pos.x + parameter->GetParmeter()[1].size.width) {
			if (comType != COM_DEFAULT) {
				isExcute = true;
			}
		}
		else isExcute = false;
	}
}

bool Actor::FindIsTurnObject(void)
{
	vector<vector<GameObject*>> vObject = manager->GetVObject();

	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] == this) continue;

			if (vObject[y][x]->GetKind() == ACTOR) {
				if (dynamic_cast<Actor*>(vObject[y][x])->GetIsTurn() ||
					(dynamic_cast<Actor*>(vObject[y][x])->GetIsExcute() &&
					 dynamic_cast<Actor*>(vObject[y][x])->GetComType() != COM_GUARD &&
					 dynamic_cast<Actor*>(vObject[y][x])->GetComType() != COM_AVOID)) {
					return true;
				}
			}
		}
	}

	ExcuteTimeUpdate();
	return false;
}


void Actor::BattleMove(void)
{
	AStar::vPath vPath = astar->GetPathResult();

	int add;
	if (!astar->GetTarget()) add = -1;
	else add = 1;

	if (vPath.empty()) return;

	if (vPath[pathNum].pos.x >= pos.x - 1 &&
		vPath[pathNum].pos.x <= pos.x + 1 &&
		vPath[pathNum].pos.y >= pos.y - 1 &&
		vPath[pathNum].pos.y <= pos.y + 1)
		pathNum += add;

	if (!astar->GetTarget()) {
		if (pathNum < 0) {
			astar->ClearBattlePath();
			astar->SetEnd(nullptr);
			isExcute = false;
			comType = COM_DEFAULT;
			pathNum = 0;
			isRight = !isRight;
			if (frame.y == 0) frame.y = 1;
			else frame.y = 0;
			return;
		}
	}

	if (pathNum >= vPath.size()) return;

	if (vPath[pathNum].pos.x > pos.x) {
		pos.x += moveSpeed * 0.5f;
	}
	else if (vPath[pathNum].pos.x < pos.x) {
		pos.x -= moveSpeed * 0.5f;
	}

	if (vPath[pathNum].pos.y > pos.y) {
		pos.y += moveSpeed * 0.27f;
	}
	else if (vPath[pathNum].pos.y < pos.y) {
		pos.y -= moveSpeed * 0.27f;
	}
}

void Actor::BattleAttack(void)
{
	if (!astar->GetTarget()) return;
	AStar::vPath vPath = astar->GetPathResult();
	if (pathNum < vPath.size())
		BattleMove();
	else {
		Actor* end = astar->GetTarget();
		if (!bFunction->GetAttackBox()) {
			if (end->pos.x > pos.x) {
				isRight = true;
			}
			else if (end->pos.x < pos.x) {
				isRight = false;
			}

			if (end->pos.y > pos.y) {
				frame.y = 0;
			}
			else if (end->pos.y < pos.y) {
				frame.y = 1;
			}
			bFunction->CreateBoxPos();
			bFunction->IsInTarget();
		}

		if (!isInBattle) {
			bFunction->Attacking();
			astar->SetTarget(nullptr);
			bFunction->SetAttackBox(nullptr);
			bFunction->SetTarget(nullptr);
			pathNum--;
			return;
		}
	}
}
