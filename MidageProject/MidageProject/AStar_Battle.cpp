#include "stdafx.h"
#include "AStar.h"
#include "Actor.h"
#include "Tile.h"
#include "MapClass.h"
#include "SearchObject.h"
#include "CommandUI.h"
#include "ObjectManager.h"
#include "BattleFunction.h"

void AStar::FindBattleMovePath(void)
{
	MapClass::_vMap mTemp = map->GetVMap();
	D2D_POINT_2L id = actor->GetId();
	D2D_SIZE_F offset = actor->GetOffset();
	vector<vector<GameObject*>> oTemp = actor->GetObjectManager()->GetVObject();

	for (int y = 0; y < mTemp.size(); y++)
	{
		vector<MoveSearch> vTemp;
		for (int x = 0; x < mTemp[y].size(); x++)
		{

			MoveSearch* temp = new MoveSearch;
			temp->id.x = x;
			temp->id.y = y;
			temp->pos = ISOPointMake(temp->id, offset);
			RymBusPointMake(temp->pos, temp->rymPos, offset);
			temp->astarType = MOVE_DEFAULT;
			temp->isOpen = true;

			if (ISOInISO(temp->pos, temp->rymPos, mTemp[y][x]->GetRymPos())) {
				if (mTemp[y][x]->GetType() == TILE_LIQUDE ||
					mTemp[y][x]->GetType() == TILE_DEFAULT) {
					temp->isOpen = false;
				}
			}

			for (UINT i = 0; i < oTemp[ACTOR].size(); i++)
			{
				if (ISOInPoint(temp->pos, oTemp[ACTOR][i]->GetRymPos())) {
					if (oTemp[ACTOR][i]->GetKind() == ACTOR) {
						temp->isOpen = false;
						if (actor->GetActorKind() == PLAYER) {
							if (dynamic_cast<Actor*>(oTemp[ACTOR][i])->GetActorKind() == MONSTER) {
								vTarget.push_back((dynamic_cast<Actor*>(oTemp[ACTOR][i])));
							}
						}
						else if (actor->GetActorKind() == MONSTER) {
							if (dynamic_cast<Actor*>(oTemp[ACTOR][i])->GetActorKind() == PLAYER) {
								vTarget.push_back((dynamic_cast<Actor*>(oTemp[ACTOR][i])));
							}
						}
					}
				}
			}

			if (y == id.y && x == id.x) {
				temp->astarType = MOVE_START;
				temp->isOpen = true;
				start = current = temp;
				vPathResult.push_back(*start);
			}


			vTemp.push_back(*temp);
		}
		vTotalPath.push_back(vTemp);
		vTemp.clear();
	}
}

void AStar::SeleteTarget(void)
{
	if (actor->GetActorKind() == MONSTER) {
		if (vTarget.size() == 1) {
			target = vTarget[0];
			actor->GetBattleBox()->SetTarget(target);
		}
		return;
	}
	
	for (UINT i = 0; i < vTarget.size(); i++)
	{
		if (MouseInISO(vTarget[i]->GetRymPos())) {
			target = vTarget[i];
			actor->GetBattleBox()->SetTarget(target);
			return;
		}
	}
}

void AStar::FindBattleEnd(void)
{
	if (!target) return;
	
	for (int i = 0; i < 4; i++)
	{
		int x = target->GetId().x;
		int y = target->GetId().y;
		switch (i) {
		case 0:
			x--;
			break;
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		}
		if (x >= vTotalPath.size() || y >= vTotalPath.size()) continue;
		MoveSearch* temp = &vTotalPath[y][x];
		if (!temp->isOpen) continue;
		temp->distance = GetDistance(start->id.x, start->id.y, temp->id.x, temp->id.y);
		endResult.push_back(*temp);
	}

	for (UINT i = 0; i < endResult.size(); i++)
	{
		for (UINT j = 0; j < endResult.size() -1; j++)
		{
			if (endResult[j].distance > endResult[j + 1].distance) {
				MoveSearch temp = endResult[j];
				endResult[j] = endResult[j + 1];
				endResult[j + 1] = temp;
			}
		}
	}

	end = &vTotalPath[endResult[0].id.y][endResult[0].id.x];
	end->astarType = MOVE_END;
	endResult.clear();
}