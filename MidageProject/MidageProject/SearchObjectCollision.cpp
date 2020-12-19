#include "stdafx.h"
#include "SearchObject.h"
#include "Actor.h"
#include "ObjectManager.h"
#include "MapClass.h"
#include "Tile.h"

void SearchObject::CreateCollisionSearch(void)
{
	/*
	�÷��̾��� ��ġ�� �������� �浹�� ISO Metric�� ������ ��
	�� �浹�� ISO Metric�� INDEX�� Index�� ���� ID ���� ���� (scale�� 1�� ���)
	
	Index(0,0) ID delta(X: -1, Y: -1) / Index(0,1) ID delta(X: -1, Y: 0) / Index(0,2) ID delta (X: -1, Y: 1)
	Index(1,0) ID delta(X:  0, Y: -1) / Index(1,1) ID delta(X: 0 , Y: 0) / Index(1,2) ID delta (X:  0, Y: 1)
	Index(2,0) ID delta(X:  1, Y: -1) / Index(2,1) ID delta(X: 1 , Y: 0) / Index(2,2) ID delta (X:  1, Y: 1)
	*/

	D2D_POINT_2F pos = actor->GetPos();		//������Ʈ�� ��ġ
	D2D_SIZE_F offset = actor->GetOffset();	//ISO Metric ���� ũ��

	int _x = 0;								//�浹�� ISO IDX ��ǥ ��ġ ��������
	int _y = 0;								//�浹�� ISO IDY ��ǥ ��ġ �������� 
	float scale = 0.25f;					//�浹�� ISO Metric ���� ���� ���� ( 1�� �������� ���� ���� ���� ������ ���� Ŭ���� ���� ������ ũ��)

	for (int y = 0; y < COLLISIONSIZE; y++)
	{
		_x = - y;								// 0 , -1, -2 ���� �� ��ȭ
		_y = (y + 1) - COLLISIONSIZE + 1;		// -2, -1, 0 ���� �� ��ȭ

		for (int x = 0; x < COLLISIONSIZE; x++)
		{
			collisionSearch[y][x].id = { NULL, NULL };												// �浹�� ISO Metric���� ������Ʈ���� �浹�� �ش� ID���� ������
			collisionSearch[y][x].pos.x = pos.x + ((offset.width * 0.5f * scale) * _x);				// �浹�� ISO Metric X ��ǥ ������ ����
			collisionSearch[y][x].pos.y = pos.y + ((offset.height * 0.27f * scale) * _y);			// �浹�� ISO Metric Y ��ǥ ������ ����
			collisionSearch[y][x].pos = ISOPointMake(collisionSearch[y][x].id, offset);				// �浹�� ISO Metric ����
			_x++;
			_y++;
			/*
			�� ���� ����
			ISO POINT�� ����
			X��ǥ�� ((id.x - id.y) * offset.width * 0.5f)
			Y��ǥ�� ((id.x + id.y) * offset.hight * 0.27f)
			���⼭ (id.x - id.y)�� A�� (id.x + id.y)�� B�� ġȯ�ϸ�
			X��ǥ�� (A * offset.width * 0.5f)
			Y��ǥ�� (B * offset.hight * 0.27f)�� ���ȴ�.
			�̸� �ٰŷ� ��ǥ�� offset.width * 0.5f�� offset.hight * 0.27f�� ��� �������°��� ���� �������� Ȯ�� �� �� �ִ�.
			���� �� Object�� pos���� offset.width * 0.5f�� offset.hight * 0.27f�� �󸶳� ���ϰ� ���°��� ����
			A�� B�� ���� ��ȭ�ϰ� �̿� ���� �浹 ISO Metric�� ��ǥ�� �����ȴ�.

			�� ������� ID�� �����Ͽ� ID�� �������� �ʰ� �ٸ� ������� ����ϴ°�?
			������� ID�� �����Ͽ� ����� �� ID�� ���������� �Ǿ� ���� ��ġ�� �ƴ� �� �ʺ� ID�� ���� �浹 ISO Metric�� ����ǹǷ�
			�浹 ���� ������ �̵� �Ұ� Ÿ�� �̵����� ������ �߻��Ѵ�.

			�� ID�� ���� �������� -1, 0, 1�� ���� �ʴ°�?
			ID�� �������� -1, 0, 1 �̳� ���� ��ǥ�ν��� �������� offset.width * 0.5f �� offset.hight * 0.27f ��ŭ�� �������� ���� ������
			�̸� �����ϱ� ���ؼ� �� ���� ���� X��ǥ�� 0, -1, -2�� Y��ǥ�� -2, -1, 0 �� ���̸� �����Ѵ�.

			�� ISOPoint �Լ��� ����ؼ� ���� �� ����?
			����� �� ������ scale�� ������ �� ����.
			A�� B�� ���� id���� �����ؾ��ϳ� ID ���� LONG�� �ڷ����̱� ������ �Ҽ����� �ݿ����� �ʱ⿡
			�̼��ϰ� ������ �� ���� ������ float ���� offset.width�� offset.hight�� �����Ͽ� �̼��ϰ� �����Ѵ�.
			*/

			RymBusPointMake(collisionSearch[y][x].pos, collisionSearch[y][x].rymPos, offset);	// Ž�� ISO Metric ����
			collisionSearch[y][x].isInISO = false;												// �浹 ���� ����
		}
	}
}

void SearchObject::CollisionSearch(void)
{
	MapClass::_vMap temp = map->GetVMap();			//Ÿ�� �� ����
	D2D_POINT_2L id = actor->GetId();				//������Ʈ�� ID
	D2D_POINT_2F pos = actor->GetPos();				//������Ʈ�� POS
	D2D_SIZE_F offset = actor->GetOffset();			//ISO Metric ���� ũ��

	int tX = 0;										//�浹�� ISO IDX ��ǥ ��ġ ��������
	int tY = 0;										//�浹�� ISO IDY ��ǥ ��ġ �������� 
	float scale = 0.25f;							//�浹�� ISO Metric ���� ���� ���� ( 1�� �������� ���� ���� ���� ������ ���� Ŭ���� ���� ������ ũ��)
	
	for (int y = -1; y < COLLISIONSIZE - 1; y++)
	{
		tX = -y - 1;								// 0 , -1, -2 ���� �� ��ȭ
		tY = (y + 1) - COLLISIONSIZE + 1;			// -2, -1, 0 ���� �� ��ȭ
		for (int x = -1; x < COLLISIONSIZE - 1; x++)
		{
			collisionSearch[y + 1][x + 1].pos.x = pos.x + ((offset.width * 0.5f * scale) * tX);
			collisionSearch[y + 1][x + 1].pos.y = pos.y + ((offset.height * 0.27f * scale) * tY);
			RymBusPointMake(collisionSearch[y + 1][x + 1].pos, collisionSearch[y + 1][x + 1].rymPos, offset);
			tX++;
			tY++;

			// ���� �������� ����� �� �� ���� ������ ǥ��
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
					// �̵� �Ұ� Ÿ���� �浹 ���� ������ ���� �浹
					if (ISOInPoint(collisionSearch[_y][_x].pos, temp[id.y + y][id.x + x]->GetRymPos())) {
						if (temp[id.y + y][id.x + x]->GetType() != TILE_LIQUDE &&
							temp[id.y + y][id.x + x]->GetType() != TILE_DEFAULT) {
							collisionSearch[_y][_x].isInISO = false;
						}
						else collisionSearch[_y][_x].isInISO = true;
					}

					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						// ������Ʈ�� Ž�� �������� �ٸ� ������Ʈ�� �浹 ���� ������ ������ �浹
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
	vector<vector<GameObject*>> vObject = manager->GetVObject();			// ������Ʈ �Ŵ��� ����
	bool overlab = false;													// �ߺ� �˻�

	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] == actor) continue;							// �ڽſ� ���ؼ��� ���� ���� �ʴ´�.

			// Ž�� ������ ��� ������ �ߺ�üũ �� �߰�
			if (ISOInPoint(vObject[y][x]->GetPos(), rymPos)) {

				if (!vObjectSearch.empty()) {
					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						if (vObject[y][x] == vObjectSearch[i]) {			// ������ �ִ� Ž�� ������Ʈ ��ϰ� �����ϸ�
							overlab = true;									// �ߺ�ó�� �Ѵ�.
							break;
						}
					}
				}

				if (!overlab) {
					vObjectSearch.push_back(vObject[y][x]);					// �ߺ�ó���� ���� ���� ������Ʈ�� Ž�� ������Ʈ�� �ִ´�.
				}
				overlab = false;
			}
			// Ž�� ������ �ȵ�� ������ ����
			else {
				if (!vObjectSearch.empty()) {								// Ž�� ������Ʈ�� ������ ������
					for (UINT i = 0; i < vObjectSearch.size(); i++)
					{
						if (vObject[y][x] == vObjectSearch[i]) {			// ������ �ִ� ������Ʈ�� ã�Ƴ���
							vObjectSearch.erase(vObjectSearch.begin() + i);	// Ž�� ������Ʈ���� �����Ѵ�.
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
