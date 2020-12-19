#include "stdafx.h"
#include "SearchObject.h"
#include "Actor.h"
#include "ObjectManager.h"
#include "MapClass.h"
#include "Tile.h"

void SearchObject::CreateCollisionSearch(void)
{
	/*
	플레이어의 위치를 기준으로 충돌용 ISO Metric을 생성할 때
	각 충돌용 ISO Metric의 INDEX와 Index에 따른 ID 값의 차이 (scale이 1일 경우)
	
	Index(0,0) ID delta(X: -1, Y: -1) / Index(0,1) ID delta(X: -1, Y: 0) / Index(0,2) ID delta (X: -1, Y: 1)
	Index(1,0) ID delta(X:  0, Y: -1) / Index(1,1) ID delta(X: 0 , Y: 0) / Index(1,2) ID delta (X:  0, Y: 1)
	Index(2,0) ID delta(X:  1, Y: -1) / Index(2,1) ID delta(X: 1 , Y: 0) / Index(2,2) ID delta (X:  1, Y: 1)
	*/

	D2D_POINT_2F pos = actor->GetPos();		//오브젝트의 위치
	D2D_SIZE_F offset = actor->GetOffset();	//ISO Metric 생성 크기

	int _x = 0;								//충돌용 ISO IDX 좌표 위치 지역변수
	int _y = 0;								//충돌용 ISO IDY 좌표 위치 지역변수 
	float scale = 0.25f;					//충돌용 ISO Metric 분포 범위 비율 ( 1을 기준으로 작을 수록 분포 범위를 좁게 클수록 분포 범위를 크게)

	for (int y = 0; y < COLLISIONSIZE; y++)
	{
		_x = - y;								// 0 , -1, -2 으로 값 변화
		_y = (y + 1) - COLLISIONSIZE + 1;		// -2, -1, 0 으로 값 변화

		for (int x = 0; x < COLLISIONSIZE; x++)
		{
			collisionSearch[y][x].id = { NULL, NULL };												// 충돌용 ISO Metric에서 오브젝트간의 충돌시 해당 ID값을 사용안함
			collisionSearch[y][x].pos.x = pos.x + ((offset.width * 0.5f * scale) * _x);				// 충돌용 ISO Metric X 좌표 기준점 생성
			collisionSearch[y][x].pos.y = pos.y + ((offset.height * 0.27f * scale) * _y);			// 충돌용 ISO Metric Y 좌표 기준점 생성
			collisionSearch[y][x].pos = ISOPointMake(collisionSearch[y][x].id, offset);				// 충돌용 ISO Metric 생성
			_x++;
			_y++;
			/*
			위 술식 내용
			ISO POINT를 계산시
			X좌표는 ((id.x - id.y) * offset.width * 0.5f)
			Y좌표는 ((id.x + id.y) * offset.hight * 0.27f)
			여기서 (id.x - id.y)를 A로 (id.x + id.y)를 B로 치환하면
			X좌표는 (A * offset.width * 0.5f)
			Y좌표는 (B * offset.hight * 0.27f)로 계산된다.
			이를 근거로 좌표는 offset.width * 0.5f와 offset.hight * 0.27f가 몇번 곱해졌는가에 대한 내용으로 확인 할 수 있다.
			따라서 위 Object의 pos에서 offset.width * 0.5f와 offset.hight * 0.27f를 얼마나 더하고 빼는가에 따라
			A와 B의 값이 변화하고 이에 따라 충돌 ISO Metric의 좌표가 결정된다.

			왜 사용자의 ID를 참조하여 ID를 설정하지 않고 다른 방식으로 계산하는가?
			사용자의 ID를 참조하여 계산할 시 ID에 의존적으로 되어 실제 위치가 아닌 각 맵별 ID에 따라 충돌 ISO Metric이 변경되므로
			충돌 감지 지연과 이동 불가 타일 이동등의 문제가 발생한다.

			왜 ID의 실제 위상차인 -1, 0, 1로 하지 않는가?
			ID의 위상차는 -1, 0, 1 이나 실제 좌표로써의 위상차는 offset.width * 0.5f 와 offset.hight * 0.27f 만큼의 위상차가 나기 때문에
			이를 보정하기 위해서 각 위상 별로 X좌표는 0, -1, -2로 Y좌표는 -2, -1, 0 의 차이를 적용한다.

			왜 ISOPoint 함수를 사용해서 만들 수 없나?
			사용할 수 있으나 scale을 적용할 수 없다.
			A와 B의 값인 id값을 조정해야하나 ID 값이 LONG형 자료형이기 때문에 소수점이 반영되지 않기에
			미세하게 조정할 수 없기 때문에 float 값인 offset.width와 offset.hight에 적용하여 미세하게 조정한다.
			*/

			RymBusPointMake(collisionSearch[y][x].pos, collisionSearch[y][x].rymPos, offset);	// 탐색 ISO Metric 생성
			collisionSearch[y][x].isInISO = false;												// 충돌 여부 판정
		}
	}
}

void SearchObject::CollisionSearch(void)
{
	MapClass::_vMap temp = map->GetVMap();			//타일 맵 참조
	D2D_POINT_2L id = actor->GetId();				//오브젝트의 ID
	D2D_POINT_2F pos = actor->GetPos();				//오브젝트의 POS
	D2D_SIZE_F offset = actor->GetOffset();			//ISO Metric 생성 크기

	int tX = 0;										//충돌용 ISO IDX 좌표 위치 지역변수
	int tY = 0;										//충돌용 ISO IDY 좌표 위치 지역변수 
	float scale = 0.25f;							//충돌용 ISO Metric 분포 범위 비율 ( 1을 기준으로 작을 수록 분포 범위를 좁게 클수록 분포 범위를 크게)
	
	for (int y = -1; y < COLLISIONSIZE - 1; y++)
	{
		tX = -y - 1;								// 0 , -1, -2 으로 값 변화
		tY = (y + 1) - COLLISIONSIZE + 1;			// -2, -1, 0 으로 값 변화
		for (int x = -1; x < COLLISIONSIZE - 1; x++)
		{
			collisionSearch[y + 1][x + 1].pos.x = pos.x + ((offset.width * 0.5f * scale) * tX);
			collisionSearch[y + 1][x + 1].pos.y = pos.y + ((offset.height * 0.27f * scale) * tY);
			RymBusPointMake(collisionSearch[y + 1][x + 1].pos, collisionSearch[y + 1][x + 1].rymPos, offset);
			tX++;
			tY++;

			// 맵의 범위에서 벗어나면 갈 수 없는 곳으로 표시
			if (id.x + x < 0 || 
				id.y + y < 0 ||
				id.x + x >= (int)temp.size() ||
				id.y + y >= (int)temp.size())
			{
				collisionSearch[y + 1][x + 1].isInISO = true;
				continue;
			}
	
			for (int _y = 0; _y < COLLISIONSIZE; _y++)
			{
				for (int _x = 0; _x < COLLISIONSIZE; _x++)
				{
					// 이동 불가 타일이 충돌 감지 범위에 들어가면 충돌
					if (ISOInPoint(collisionSearch[_y][_x].pos, temp[id.y + y][id.x + x]->GetRymPos())) {
						if (temp[id.y + y][id.x + x]->GetType() != TILE_LIQUDE &&
							temp[id.y + y][id.x + x]->GetType() != TILE_DEFAULT) {
							collisionSearch[_y][_x].isInISO = false;
						}
						else collisionSearch[_y][_x].isInISO = true;
					}

					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						// 오브젝트의 탐색 범위내의 다른 오브젝트가 충돌 감지 범위에 들어오면 충돌
						if (ISOInPoint(collisionSearch[_y][_x].pos, vObjectSearch[i]->GetRymPos())) {
							if (vObjectSearch[i]->GetKind() != MATTER) {
								collisionSearch[_y][_x].isInISO = false;
							}
							else collisionSearch[_y][_x].isInISO = true;
						}
					}

				}
			}
		}
	}
}

void SearchObject::ObjectSearch(void)
{
	vector<vector<GameObject*>> vObject = manager->GetVObject();			// 오브젝트 매니저 참조
	bool overlab = false;													// 중복 검사

	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] == actor) continue;							// 자신에 대해서는 연산 하지 않는다.

			// 탐색 범위에 들어 있으면 중복체크 후 추가
			if (ISOInPoint(vObject[y][x]->GetPos(), rymPos)) {

				if (!vObjectSearch.empty()) {
					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						if (vObject[y][x] == vObjectSearch[i]) {			// 가지고 있는 탐색 오브젝트 목록과 동일하면
							overlab = true;									// 중복처리 한다.
							break;
						}
					}
				}

				if (!overlab) {
					vObjectSearch.push_back(vObject[y][x]);					// 중복처리가 되지 않은 오브젝트만 탐색 오브젝트에 넣는다.
				}
				overlab = false;
			}
			// 탐색 범위에 안들어 있으면 빼기
			else {
				if (!vObjectSearch.empty()) {								// 탐색 오브젝트를 가지고 있으면
					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						if (vObject[y][x] == vObjectSearch[i]) {			// 가지고 있는 오브젝트를 찾아내어
							vObjectSearch.erase(vObjectSearch.begin() + i);	// 탐색 오브젝트에서 제외한다.
							break;
						}
					}
				}
			}
		}
	}
}

void SearchObject::AttackSearch(void)
{	
	if (actor->GetIsRight())
	{
		if (actor->GetFrame().y == 0)
		{
			attackSearch.id.x = actor->GetId().x + 1;
			attackSearch.id.y = actor->GetId().y;
		}
		else if (actor->GetFrame().y == 1)
		{
			attackSearch.id.x = actor->GetId().x;
			attackSearch.id.y = actor->GetId().y - 1;
		}
	}
	else {
		if (actor->GetFrame().y == 0)
		{
			attackSearch.id.x = actor->GetId().x;
			attackSearch.id.y = actor->GetId().y + 1;
		}
		else if (actor->GetFrame().y == 1)
		{
			attackSearch.id.x = actor->GetId().x - 1;
			attackSearch.id.y = actor->GetId().y;
		}
	}

	ISOPointMake(attackSearch.id, actor->GetOffset());
	RymBusPointMake(attackSearch.pos, attackSearch.rymPos, actor->GetOffset());

	for (UINT i = 0; i < vObjectSearch.size(); i++)
	{
		if (ISOInPoint(vObjectSearch[i]->GetPos(), attackSearch.rymPos)) {
			attackSearch.isInISO = true;
			return;
		}
	}
}
