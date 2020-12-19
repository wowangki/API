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
	MapClass::_vMap mTemp = map->GetVMap();									// �� ����
	D2D_POINT_2L id = actor->GetId();										// ������Ʈ ID
	D2D_SIZE_F offset = actor->GetOffset();									// �̵� ISO Metric ũ��
	vector<GameObject*> oTemp = actor->GetSearch()->GetVObjectSearch();		// Ž���� ������Ʈ ��� ����

	D2D_POINT_2L tId;														// �̵� ISO Metric�� ��ǥ�� ����� �ӽ� ID ��

	for (int y = 0; y < fieldMoveSize; y++)
	{	
		vector<MoveSearch> vTemp;											// ���� vector ����� ���� �ӽ� vector
		for (int x = 0; x < fieldMoveSize; x++)
		{
			tId.x = id.x + x - (int)(fieldMoveSize * 0.5f) + 1;				//������� ��ġ �������� �̵� ������ ũ�� ��ŭ�� IDX �� �ο�
			tId.y = id.y + y - (int)(fieldMoveSize * 0.5f) + 1;				//������� ��ġ �������� �̵� ������ ũ�� ��ŭ�� IDY �� �ο�

			MoveSearch* temp = new MoveSearch;								//��� Ž���� ���� ����ü ������ ����
			temp->id.x = x;													//����ü �������� INDEX IDX ��
			temp->id.y = y;													//����ü �������� INDEX IDY ��
			temp->pos = ISOPointMake(tId, offset);							//����ü �������� ��ǥ �� ����
			RymBusPointMake(temp->pos, temp->rymPos, offset);				//����ü �������� ISO Metric ����
			temp->astarType = MOVE_DEFAULT;									//����ü �������� Ÿ�� ����
			temp->isOpen = true;											//�ش� ISO Metric �̵� ���� ���� ����

			//�� ������ ����� �̵� ISO Metric�� �̵� �Ұ��� ����
			if (tId.x < 0 ||
				tId.y < 0 ||
				tId.x >= mTemp.size() ||
				tId.y >= mTemp.size()) {
				temp->isOpen = false;
				vTemp.push_back(*temp);
				continue;
			}
			
			// �� Ÿ�� �� �̵� �Ұ� Ÿ���� ���� ��� ISO Metric�� �̵� �Ұ��� ����
			if (ISOInISO(temp->pos, temp->rymPos, mTemp[tId.y][tId.x]->GetRymPos())) {
				if (mTemp[tId.y][tId.x]->GetType() == TILE_LIQUDE ||
					mTemp[tId.y][tId.x]->GetType() == TILE_DEFAULT) {
					temp->isOpen = false;
				}
			}

			// Ž�� ������Ʈ ��� �� �� ������Ʈ �Ǵ� Ž�� ������Ʈ�� ������ ��� �̵� �Ұ��� ����
			// �÷��̾��� ��� A* �˰����� ������� �ʰ� �������� ��ǥ������ �̵�
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

			// ������Ʈ�� ���� ��ġ�� id�� ������ �̵� ISO Metric�� id�� ������ ���� Ÿ�Ϸ� ����
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
	D2D_POINT_2L destId;													//������ ������ ���� ������ ID ���� ����
	if (FindObject()) {														
		destId.y = start->id.y + (target->GetId().y - actor->GetId().y);	//���� �̵� ISO Metric���� ���� Ÿ�ٱ����� idY�� ���
		destId.x = start->id.x + (target->GetId().x - actor->GetId().x);	//���� �̵� ISO Metric���� ���� Ÿ�ٱ����� idX�� ���

		// ������ ID�� �̵� ������ ��� ��� �̵� �� �� �ִ� �ִ�ġ�� ����Ͽ� �̵�
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
			destId.y = GetRandomInt(0, vTotalPath.size() - 1);						// �̵� ���� �� �����ϰ� �������� IDX�� ����
			destId.x = GetRandomInt(0, vTotalPath[destId.y].size() - 1);			// �̵� ���� �� �����ϰ� �������� IDY�� ����

			if (destId.y == start->id.y && destId.x == start->id.x) continue;		// ������ ID�� ����� ID�� ������ ����Ѵ�.
			if (vTotalPath[destId.y][destId.x].isOpen) break;						// ������ ID�� �̵���ΰ� ���� ������ �������� ���� ���´�.
		}
	}

	vTotalPath[destId.y][destId.x].astarType = MOVE_END;							//�ش� ISO Metric�� �������� ����
	end = &vTotalPath[destId.y][destId.x];
}

AStar::vPath AStar::addPathList(MoveSearch* current)
{
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			// �̵��� ��ΰ� �̵� ������ ����� �Ѿ��.
			if (current->id.y + y < 0 ||
				current->id.x + x < 0 ||
				current->id.y + y >= vTotalPath.size() ||
				current->id.x + x >= vTotalPath.size())
				continue;

			// �̵��� ��ΰ� ���� �ְų� ������� �Ѿ��.
			if (!(vTotalPath[current->id.y + y][current->id.x + x].isOpen) ||
				vTotalPath[current->id.y + y][current->id.x + x].astarType == MOVE_START)
				continue;

			// �����ִ� ����� ���� �޴´�.
			MoveSearch node = vTotalPath[current->id.y + y][current->id.x + x];

			// �ߺ� ���� üũ
			bool addObj = true;
			for (UINT i = 0; i < vOpenPath.size(); i++)
			{
				if (vOpenPath[i].id.x == node.id.x && vOpenPath[i].id.y == node.id.y) {
					addObj = false;
					break;
				}
			}
			// �ߺ��� �ƴϸ� �Ѿ��.
			if (!addObj) continue;

			// ���� �ִ°���� ������ ������ �Ÿ��� ����Ͽ� �־��ش�.
			node.distance = GetDistance(node.id.x, node.id.y, end->id.x, end->id.y) * 10;

			// �� �� �ִ� ��ο� �־��ش�.
			vOpenPath.push_back(node);
		}
	}

	// �� �� �ִ� ��ε��� ��ȯ�Ѵ�.
	return vOpenPath;
}

void AStar::PathFinder(MoveSearch* current)
{
	float totalDistance = 50000.0f; // �� ��� ���
	MoveSearch temp;

	for (UINT i = 0; i < addPathList(current).size(); i++)
	{
		// �� ��� ��� ���� �� �� �ִ� ����� ����� ������
		if (totalDistance > vOpenPath[i].distance) {
			totalDistance = vOpenPath[i].distance;				// �ش� ��� ����� �ְ�
			temp = vOpenPath[i];								// �ش� ��θ� ����
		}

		// �ߺ� üũ
		bool addObj = true;
		for (UINT i = 0; i < vOpenPath.size(); i++)
		{
			if (vOpenPath[i].id.x == temp.id.x && vOpenPath[i].id.y == temp.id.y) {
				addObj = false;
				break;
			}
		}
		// �ش� ��θ� �ݰ�
		vOpenPath[i].isOpen = false;
		// �ߺ��̸� �ѱ��.
		if (!addObj) continue;
		
		vOpenPath.push_back(temp);
	}

	// ������ ��θ� �̵��� ��ο� �ִ´�.
	vPathResult.push_back(temp);

	// ������ ��ΰ� ���̻� ������ �� ���ų� �������̸� ��
	if (temp.astarType == MOVE_END || !temp.isOpen) return;

	// ������ ��θ� ���� ��ο� �ִ´�.
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
	vector<GameObject*> vObject = actor->GetSearch()->GetVObjectSearch();		// Ž�� ������Ʈ ���

	for (UINT i = 0; i < vObject.size(); i++)
	{
		if (vObject[i]->GetKind() == ACTOR) {
			if (dynamic_cast<Actor*>(vObject[i])->GetActorKind() == PLAYER) {	// Ž�� ������Ʈ ��� �� �÷��̾ ������
				target = dynamic_cast<Actor*>(vObject[i]);						// Ÿ������ ����
				return true;
			}
		}
	}

	target = nullptr;
	return false;
}