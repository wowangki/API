#include "stdafx.h"
#include "AStar.h"
#include "Actor.h"
#include "Tile.h"
#include "MapClass.h"
#include "SearchObject.h"

AStar::AStar()
{
}

AStar::AStar(Actor * actor, MapClass * map, int size)
{
	this->actor = actor;
	this->map = map;
	this->target = nullptr;
	this->fieldMoveSize = size;
	start = end = current = nullptr;
	manager = this->actor->GetObjectManager();
}


AStar::~AStar()
{
	SafeDelete(start);
	SafeDelete(end);
	SafeDelete(current);
}

void AStar::Update(void)
{
	if (vTotalPath.empty()) {
		FindTotalMovePath();
		FindFieldEnd();
		PathFinder(current);
	}
}

void AStar::BattleUpdate(void)
{
	if (end) return;
	FindBattleEnd();
	PathFinder(current);
}

void AStar::Render(void)
{
#pragma region  test
	//for (UINT y = 0; y < vTotalPath.size(); y++)
	//{
	//	for (UINT x = 0; x < vTotalPath[y].size(); x++)
	//	{
	//		if (vTotalPath[y][x].isOpen) {
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[0].x + _CAM->x, vTotalPath[y][x].rymPos[0].y + _CAM->y }, { vTotalPath[y][x].rymPos[1].x + _CAM->x, vTotalPath[y][x].rymPos[1].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[0].x + _CAM->x, vTotalPath[y][x].rymPos[0].y + _CAM->y }, { vTotalPath[y][x].rymPos[3].x + _CAM->x, vTotalPath[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[1].x + _CAM->x, vTotalPath[y][x].rymPos[1].y + _CAM->y }, { vTotalPath[y][x].rymPos[2].x + _CAM->x, vTotalPath[y][x].rymPos[2].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[2].x + _CAM->x, vTotalPath[y][x].rymPos[2].y + _CAM->y }, { vTotalPath[y][x].rymPos[3].x + _CAM->x, vTotalPath[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("MAGENTA"));
	//		}
	//		else {
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[0].x + _CAM->x, vTotalPath[y][x].rymPos[0].y + _CAM->y }, { vTotalPath[y][x].rymPos[1].x + _CAM->x, vTotalPath[y][x].rymPos[1].y + _CAM->y }, _BRUSH->GetBrush("BLACK"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[0].x + _CAM->x, vTotalPath[y][x].rymPos[0].y + _CAM->y }, { vTotalPath[y][x].rymPos[3].x + _CAM->x, vTotalPath[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLACK"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[1].x + _CAM->x, vTotalPath[y][x].rymPos[1].y + _CAM->y }, { vTotalPath[y][x].rymPos[2].x + _CAM->x, vTotalPath[y][x].rymPos[2].y + _CAM->y }, _BRUSH->GetBrush("BLACK"));
	//			_RenderTarget->DrawLine({ vTotalPath[y][x].rymPos[2].x + _CAM->x, vTotalPath[y][x].rymPos[2].y + _CAM->y }, { vTotalPath[y][x].rymPos[3].x + _CAM->x, vTotalPath[y][x].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLACK"));
	//		}
	//
	//		if (vTotalPath[y][x].astarType == MOVE_END) {
	//			DrawISO(vTotalPath[y][x].rymPos, "RED");
	//		}
	//		
	//
	//
	//		//WCHAR idString[256];
	//		//static TCHAR idText[] = L"%d %d";
	//		//_stprintf_s(idString, idText, vTotalPath[y][x].tId.x, vTotalPath[y][x].tId.y);
	//		//_FONT->Render(idString, FRectMakeCenter(vTotalPath[y][x].pos.x + _CAM->x, vTotalPath[y][x].pos.y + _CAM->y, 30,10), _BRUSH->GetBrush("BLACK"));
	//	}
	//}
	
	for (UINT i = 0; i < vPathResult.size(); i++)
	{
		if (vPathResult[i].isOpen) {
			_RenderTarget->DrawLine({ vPathResult[i].rymPos[0].x + _CAM->x, vPathResult[i].rymPos[0].y + _CAM->y }, { vPathResult[i].rymPos[1].x + _CAM->x, vPathResult[i].rymPos[1].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
			_RenderTarget->DrawLine({ vPathResult[i].rymPos[0].x + _CAM->x, vPathResult[i].rymPos[0].y + _CAM->y }, { vPathResult[i].rymPos[3].x + _CAM->x, vPathResult[i].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
			_RenderTarget->DrawLine({ vPathResult[i].rymPos[1].x + _CAM->x, vPathResult[i].rymPos[1].y + _CAM->y }, { vPathResult[i].rymPos[2].x + _CAM->x, vPathResult[i].rymPos[2].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
			_RenderTarget->DrawLine({ vPathResult[i].rymPos[2].x + _CAM->x, vPathResult[i].rymPos[2].y + _CAM->y }, { vPathResult[i].rymPos[3].x + _CAM->x, vPathResult[i].rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
		}
		else {
			DrawISO(vPathResult[i].rymPos, "RED");
		}		
	}

	//_RenderTarget->DrawLine({start.rymPos[0].x +_CAM->x, start.rymPos[0].y + _CAM->y}, {start.rymPos[1].x +_CAM->x, start.rymPos[1].y + _CAM->y}, _BRUSH->GetBrush("RED"));
	//_RenderTarget->DrawLine({start.rymPos[0].x +_CAM->x, start.rymPos[0].y + _CAM->y}, {start.rymPos[3].x +_CAM->x, start.rymPos[3].y + _CAM->y}, _BRUSH->GetBrush("RED"));
	//_RenderTarget->DrawLine({start.rymPos[1].x +_CAM->x, start.rymPos[1].y + _CAM->y}, {start.rymPos[2].x +_CAM->x, start.rymPos[2].y + _CAM->y}, _BRUSH->GetBrush("RED"));
	//_RenderTarget->DrawLine({start.rymPos[2].x +_CAM->x, start.rymPos[2].y + _CAM->y}, {start.rymPos[3].x +_CAM->x, start.rymPos[3].y + _CAM->y}, _BRUSH->GetBrush("RED"));

	//_RenderTarget->DrawLine({ end.rymPos[0].x + _CAM->x, end.rymPos[0].y + _CAM->y }, { end.rymPos[1].x + _CAM->x, end.rymPos[1].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
	//_RenderTarget->DrawLine({ end.rymPos[0].x + _CAM->x, end.rymPos[0].y + _CAM->y }, { end.rymPos[3].x + _CAM->x, end.rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
	//_RenderTarget->DrawLine({ end.rymPos[1].x + _CAM->x, end.rymPos[1].y + _CAM->y }, { end.rymPos[2].x + _CAM->x, end.rymPos[2].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
	//_RenderTarget->DrawLine({ end.rymPos[2].x + _CAM->x, end.rymPos[2].y + _CAM->y }, { end.rymPos[3].x + _CAM->x, end.rymPos[3].y + _CAM->y }, _BRUSH->GetBrush("BLUE"));
#pragma endregion

	//if(start)
	//DrawISO(start->rymPos, "BLACK");
	
	for (UINT i = 0; i < vTarget.size(); i++)
	{
		DrawISO(vTarget[i]->GetRymPos(), "BLUE");
	}
	
	if (target)
	DrawISO(target->GetRymPos(), "BLACK");

	if(end)
	DrawISO(end->rymPos, "RED");
}

void AStar::FindTotalMovePath(void)
{
	MapClass::_vMap mTemp = map->GetVMap();									// 맵 참조
	D2D_POINT_2L id = actor->GetId();										// 오브젝트 ID
	D2D_SIZE_F offset = actor->GetOffset();									// 이동 ISO Metric 크기
	vector<GameObject*> oTemp = actor->GetSearch()->GetVObjectSearch();		// 탐색된 오브젝트 목록 참조

	D2D_POINT_2L tId;														// 이동 ISO Metric의 좌표에 사용할 임시 ID 값

	for (int y = 0; y < fieldMoveSize; y++)
	{	
		vector<MoveSearch> vTemp;											// 이중 vector 사용을 위한 임시 vector
		for (int x = 0; x < fieldMoveSize; x++)
		{
			tId.x = id.x + x - (int)(fieldMoveSize * 0.5f) + 1;				//사용자의 위치 기준으로 이동 범위의 크기 만큼의 IDX 값 부여
			tId.y = id.y + y - (int)(fieldMoveSize * 0.5f) + 1;				//사용자의 위치 기준으로 이동 범위의 크기 만큼의 IDY 값 부여

			MoveSearch* temp = new MoveSearch;								//경로 탐색을 위한 구조체 포인터 선언
			temp->id.x = x;													//구조체 포인터의 INDEX IDX 값
			temp->id.y = y;													//구조체 포인터의 INDEX IDY 값
			temp->pos = ISOPointMake(tId, offset);							//구조체 포인터의 좌표 값 설정
			RymBusPointMake(temp->pos, temp->rymPos, offset);				//구조체 포인터의 ISO Metric 설정
			temp->astarType = MOVE_DEFAULT;									//구조체 포인터의 타입 설정
			temp->isOpen = true;											//해당 ISO Metric 이동 가능 여부 설정

			//맵 범위를 벗어나면 이동 ISO Metric을 이동 불가로 설정
			if (tId.x < 0 ||
				tId.y < 0 ||
				tId.x >= mTemp.size() ||
				tId.y >= mTemp.size()) {
				temp->isOpen = false;
				vTemp.push_back(*temp);
				continue;
			}
			
			// 맵 타일 중 이동 불가 타일이 있을 경우 ISO Metric을 이동 불가로 설정
			if (ISOInISO(temp->pos, temp->rymPos, mTemp[tId.y][tId.x]->GetRymPos())) {
				if (mTemp[tId.y][tId.x]->GetType() == TILE_LIQUDE ||
					mTemp[tId.y][tId.x]->GetType() == TILE_DEFAULT) {
					temp->isOpen = false;
				}
			}

			// 탐색 오브젝트 목록 중 맵 오브젝트 또는 탐색 오브젝트가 몬스터일 경우 이동 불가로 설정
			// 플레이어의 경우 A* 알고리즘을 사용하지 않고 목적지의 좌표만으로 이동
			for (UINT i = 0; i < oTemp.size(); i++)
			{
				if (ISOInPoint(temp->pos, oTemp[i]->GetRymPos())) {
					if (oTemp[i]->GetKind() == MATTER) {
						temp->isOpen = false;
					}
					else if (oTemp[i]->GetKind() == ACTOR) {
						if (dynamic_cast<Actor*>(oTemp[i])->GetActorKind() == MONSTER) {
							temp->isOpen = false;
						}
					}
				}
			}

			// 오브젝트의 현재 위치의 id와 생성된 이동 ISO Metric의 id가 같으면 시작 타일로 설정
			if (tId.y == id.y && tId.x == id.x) {
				temp->astarType = MOVE_START;
				start = current = temp;
			}
			
			vTemp.push_back(*temp);
		}
		vTotalPath.push_back(vTemp);
		vTemp.clear();
	}
}

void AStar::FindFieldEnd(void)
{
	D2D_POINT_2L destId;													//도착지 설정을 위한 도착지 ID 지역 변수
	if (FindObject()) {														
		destId.y = start->id.y + (target->GetId().y - actor->GetId().y);	//시작 이동 ISO Metric으로 부터 타겟까지의 idY를 계산
		destId.x = start->id.x + (target->GetId().x - actor->GetId().x);	//시작 이동 ISO Metric으로 부터 타겟까지의 idX를 계산

		// 도착지 ID가 이동 범위를 벗어날 경우 이동 할 수 있는 최대치로 계산하여 이동
		if (destId.y < 0) {
			destId.y = 0;
		}
		else if (destId.y >= vTotalPath.size()) {
			destId.y = vTotalPath.size() - 1;
		}

		if (destId.x < 0) {
			destId.x = 0;
		}
		else if (destId.x >= vTotalPath.size()) {
			destId.y = vTotalPath.size() - 1;
		}
	}
	else
	{
		while (true) {
			destId.y = GetRandomInt(0, vTotalPath.size() - 1);						// 이동 범위 중 랜덤하게 도착지의 IDX를 지정
			destId.x = GetRandomInt(0, vTotalPath[destId.y].size() - 1);			// 이동 범위 중 랜덤하게 도착지의 IDY를 지정

			if (destId.y == start->id.y && destId.x == start->id.x) continue;		// 도착지 ID와 출발지 ID가 같으면 계속한다.
			if (vTotalPath[destId.y][destId.x].isOpen) break;						// 도착지 ID의 이동경로가 열려 있으면 루프문을 빠져 나온다.
		}
	}

	vTotalPath[destId.y][destId.x].astarType = MOVE_END;							//해당 ISO Metric을 도착지로 지정
	end = &vTotalPath[destId.y][destId.x];
}

AStar::vPath AStar::addPathList(MoveSearch* current)
{
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			// 이동할 경로가 이동 범위를 벗어나면 넘어간다.
			if (current->id.y + y < 0 ||
				current->id.x + x < 0 ||
				current->id.y + y >= vTotalPath.size() ||
				current->id.x + x >= vTotalPath.size())
				continue;

			// 이동할 경로가 닫혀 있거나 출발지면 넘어간다.
			if (!(vTotalPath[current->id.y + y][current->id.x + x].isOpen) ||
				vTotalPath[current->id.y + y][current->id.x + x].astarType == MOVE_START)
				continue;

			// 열려있는 경로의 값을 받는다.
			MoveSearch node = vTotalPath[current->id.y + y][current->id.x + x];

			// 중복 여부 체크
			bool addObj = true;
			for (UINT i = 0; i < vOpenPath.size(); i++)
			{
				if (vOpenPath[i].id.x == node.id.x && vOpenPath[i].id.y == node.id.y) {
					addObj = false;
					break;
				}
			}
			// 중복이 아니면 넘어간다.
			if (!addObj) continue;

			// 열려 있는경로의 도착지 까지의 거리를 계산하여 넣어준다.
			node.distance = GetDistance(node.id.x, node.id.y, end->id.x, end->id.y) * 10;

			// 갈 수 있는 경로에 넣어준다.
			vOpenPath.push_back(node);
		}
	}

	// 갈 수 있는 경로들을 반환한다.
	return vOpenPath;
}

void AStar::PathFinder(MoveSearch* current)
{
	float totalDistance = 50000.0f; // 총 경로 비용
	MoveSearch temp;

	for (UINT i = 0; i < addPathList(current).size(); i++)
	{
		// 총 경로 비용 보다 갈 수 있는 경로의 비용이 작으면
		if (totalDistance > vOpenPath[i].distance) {
			totalDistance = vOpenPath[i].distance;				// 해당 경로 비용을 넣고
			temp = vOpenPath[i];								// 해당 경로를 선택
		}

		// 중복 체크
		bool addObj = true;
		for (UINT i = 0; i < vOpenPath.size(); i++)
		{
			if (vOpenPath[i].id.x == temp.id.x && vOpenPath[i].id.y == temp.id.y) {
				addObj = false;
				break;
			}
		}
		// 해당 경로를 닫고
		vOpenPath[i].isOpen = false;
		// 중복이면 넘긴다.
		if (!addObj) continue;
		
		vOpenPath.push_back(temp);
	}

	// 설정된 경로를 이동할 경로에 넣는다.
	vPathResult.push_back(temp);

	// 설정된 경로가 더이상 진행할 수 없거나 도착지이면 끝
	if (temp.astarType == MOVE_END || !temp.isOpen) return;

	// 설정된 경로를 현재 경로에 넣는다.
	this->current = &temp;
	PathFinder(this->current);
	
}

void AStar::CheckEnd(void)
{
	for (UINT y = 0; y < vTotalPath.size(); y++)
	{
		for (UINT x = 0; x < vTotalPath[y].size(); x++)
		{
			if (MouseInISO(vTotalPath[y][x].rymPos)) {
				if (&vTotalPath[y][x] != end) {
					end->astarType = MOVE_DEFAULT;
					end = nullptr;
					current = start;
					vOpenPath.clear();
					vPathResult.clear();
					return;
				}
			}
		}
	}
}

bool AStar::FindObject(void)
{
	vector<GameObject*> vObject = actor->GetSearch()->GetVObjectSearch();		// 탐색 오브젝트 목록

	for (UINT i = 0; i < vObject.size(); i++)
	{
		if (vObject[i]->GetKind() == ACTOR) {
			if (dynamic_cast<Actor*>(vObject[i])->GetActorKind() == PLAYER) {	// 탐색 오브젝트 목록 중 플레이어가 있으면
				target = dynamic_cast<Actor*>(vObject[i]);						// 타겟으로 설정
				return true;
			}
		}
	}

	target = nullptr;
	return false;
}