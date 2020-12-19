#include "stdafx.h"
#include "Monster.h"
#include "SearchObject.h"
#include "ObjectManager.h"
#include "AStar.h"
#include "CommandUI.h"
#include "BattleFunction.h"

void Monster::MoveMonster(void)
{
	AStar::vPath vPath = astar->GetPathResult();
	SearchObject::SearchIt(*tCol)[3] = search->GetCollisionSearch();

	moveTime -= _TIMER->GetElapsedTime();
	if (moveTime >= 0) return;

	if (vPath[pathNum].pos.x >= pos.x - 1 &&
		vPath[pathNum].pos.x <= pos.x + 1 &&
		vPath[pathNum].pos.y >= pos.y - 1 &&
		vPath[pathNum].pos.y <= pos.y + 1)
		pathNum++;

	if (pathNum >= vPath.size()) {
		astar->ClearAllPath();
		frame.x = 0;
		motion = ACTOR_IDLE;
		if (astar->GetTarget()) {
			moveTime = 0.3f;
		}
		else moveTime = 1.5f;
		pathNum = 0;
		return;
	}
	else if (moveTime < -6.0f) {
		astar->ClearAllPath();
		frame.x = 0;
		motion = ACTOR_IDLE;
		pathNum = 0;
		moveTime = 1.5f;
		return;
	}

	if (vPath[pathNum].pos.x > pos.x) {
		if (!tCol[0][2].isInISO)
		pos.x += moveSpeed * 0.5f;
	}
	else if (vPath[pathNum].pos.x < pos.x) {
		if (!tCol[2][0].isInISO)
		pos.x -= moveSpeed * 0.5f;
	}

	if (vPath[pathNum].pos.y > pos.y) {
		if (!tCol[2][2].isInISO)
		pos.y += moveSpeed * 0.27f;
	}
	else if (vPath[pathNum].pos.y < pos.y) {
		if (!tCol[0][0].isInISO)
		pos.y -= moveSpeed * 0.27f;
	}
}
