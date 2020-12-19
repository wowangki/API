#include "stdafx.h"
#include "Data.h"
#include "ObjectManager.h"
#include "MapClass.h"
#include "Tile.h"
#include "Player.h"
#include "PrograssBar.h"
#include "Monster.h"
#include "AStar.h"

Data::PlayerLoad Data::LoadSlotNum(void)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "Player", "PlayerSelectInfo.txt").c_str(), "r");

	char name[256];
	int num;
	PlayerLoad temp;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;
		fscanf_s(fp, "%d", &num, sizeof(int));
	}

	fclose(fp);
	temp.pos = FileSource("Resource", "Player", "Player_slot" + to_string(num) + "_Pos.txt");
	temp.proper = FileSource("Resource", "Player", "Player_slot" + to_string(num) + "_Property.txt");

	return temp;
}


void Data::LoadMap(MapClass* map, string FileSource)
{
	FILE* fp = nullptr;
	// �ش� ���Ͽ��� �о�´� (FileSource�� FileSource �Լ��� ��� �� ��)
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;													//������ �������� ������ ��ȯ

	char name[256];																//Ÿ�� �̸� ����
	int x, y, type;																//IDX , IDY, �Ӽ� �� ����
	int fx, fy;																	//FrameX , FrameY �� ����
	int sizeX, sizeY;															//MapSizeX , MapSizeY �� ����

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);									//���ϳ��� string ������ ���� ������ �Է�
		if (string(name).find("MapSizeY", 0) != string::npos)					//������ ������ ���� ���� �� ã��
			break;
	}
	
	while (true)
	{
		fscanf_s(fp, "%d%d", &sizeX, &sizeY, sizeof(int));						//���ϳ��� �ʻ���� ������ ������ �Է�
	
		map->SetLoadMapSize(sizeX, sizeY);										//���� ����� ������

		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;												//���� ��ū�� ã���� ������ Ż��
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TYPE", 0) != string::npos)						//������ ������ ���� ���� �� ã��
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);									//���ϳ��� string ������ ���� ������ �Է�
		if (name[0] == '/') break;												//���� ��ū�� ã���� ������ Ż��

		fscanf_s(fp, "%d%d%d%d%d", &x, &y, &fx, &fy, &type, sizeof(int));		//���ϳ��� IDX, IDY, FrameX, FrameY, �Ӽ� ���� �ش� ���� ������ �Է�

		map->GetVMap()[y][x]->SetLoadObject({ x,y }, { fx,fy }, type, TILE);	//�ش� IDX,IDY ���� Ÿ�Ͽ� �ش� ���� ����
		map->GetVMap()[y][x]->SetSeason(type);									//Ÿ���� �Ӽ����� ���� ���� �Ӽ��� �ο�
	}

	fclose(fp);																	//������ �Է� �Ϸ�� ������ �ݴ´�.
}

void Data::LoadPlayerInitPosition(Player * player)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "Player", "Player_InitPosition.txt").c_str(), "r");
	if (fp == nullptr) return;

	char name[256];
	int x, y;
	float offX, offY;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("OFFSETY", 0) != string::npos)
			break;
	}

	fscanf_s(fp, "%d%d", &x, &y, sizeof(int));
	fscanf_s(fp, "%f%f", &offX, &offY, sizeof(float));

	player->SetId({ x,y });
	player->SetOffset({ offX, offY });
	fclose(fp);
}

void Data::LoadPlayerPosition(ObjectManager * object, string FileSource)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;

	char name[256], typeName[256], tChar[256];
	int x, y, type, kind, objectKind;
	int fX, fY;
	float offX, offY;
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("OBJECTKIND", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d", &x, &y, sizeof(int));
		fscanf_s(fp, "%f%f", &offX, &offY, sizeof(float));
		fscanf_s(fp, "%d%d%d%d", &fX, &fY, &type, &kind, sizeof(int));
		while (true) {
			fscanf_s(fp, "%s", &typeName, sizeof typeName);
			if (string(typeName).find("class", 0) == string::npos) break;
		}
		fscanf_s(fp, "%s", &tChar, sizeof tChar);

		fscanf_s(fp, "%d", &objectKind, sizeof(int));


		object->SetObject(name, { x,y }, { offX, offY }, { fX, fY }, objectKind, typeName, type, kind, 0);
	}

	fclose(fp);
}

void Data::LoadPlayerProperty(Player * player, string FileSource)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;

	char name[256];
	int worldNum, lv, exp, maxExp, hp, mp;
	int eaPoint, waPoint, fiPoint, wiPoint;
	int vital, strength, stamin, dexterity, statPoint;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("POINT", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;
		fscanf_s(fp, "%d%d%d%d%d%d", &worldNum, &lv, &exp, &maxExp, &hp, &mp, sizeof(int));
		fscanf_s(fp, "%d%d%d%d", &eaPoint, &waPoint, &fiPoint, &wiPoint, sizeof(int));
		fscanf_s(fp, "%d%d%d%d%d", &vital, &strength, &stamin, &dexterity, &statPoint, sizeof(int));

		player->SetWorldInfoName(name);
		player->SetWorldInfoNum(worldNum);
		player->StatusSet(lv, exp, hp, mp, vital, strength, stamin, dexterity, statPoint);
		player->SetProperty(eaPoint, waPoint, fiPoint, wiPoint);
	}

	fclose(fp);
}

void Data::LoadObjectPosition(ObjectManager * object, string FileSource)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;

	char name[256], typeName[256], tChar[256];
	int x, y, type, kind, objectKind, monProperties;
	int fX, fY;
	float offX, offY;
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("MONPROPERTIES", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d", &x, &y, sizeof(int));
		fscanf_s(fp, "%f%f", &offX, &offY, sizeof(float));
		fscanf_s(fp, "%d%d%d%d", &fX, &fY, &type, &kind, sizeof(int));
		while (true) {
			fscanf_s(fp, "%s", &typeName, sizeof typeName);
			if (string(typeName).find("class", 0) == string::npos) break;
		}
		fscanf_s(fp, "%s", &tChar, sizeof tChar);
		fscanf_s(fp, "%d", &objectKind, sizeof(int));
		fscanf_s(fp, "%d", &monProperties, sizeof(int));


		object->SetObject(name, { x,y }, { offX, offY }, { fX, fY }, objectKind, typeName, type, kind, monProperties);
	}

	fclose(fp);
}

void Data::LoadObjectProperty(ObjectManager * object, string FileSource)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;
	int x = 0;

	char name[256];
	int type, lv, exp, maxExp, hp, mp;
	int eaPoint, waPoint, fiPoint, wiPoint;
	int vital, strength, stamin, dexterity;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("POINT", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;
		fscanf_s(fp, "%d%d%d%d%d%d", &type, &lv, &exp, &maxExp, &hp, &mp, sizeof(int));
		fscanf_s(fp, "%d%d%d%d", &eaPoint, &waPoint, &fiPoint, &wiPoint, sizeof(int));
		fscanf_s(fp, "%d%d%d%d", &vital, &strength, &stamin, &dexterity, sizeof(int));

		dynamic_cast<Monster*>(object->GetVObject()[ACTOR][x])->StatusSet(lv, exp, hp, mp, vital, strength, stamin, dexterity, 0);
		dynamic_cast<Monster*>(object->GetVObject()[ACTOR][x])->SetProperty(eaPoint, waPoint, fiPoint, wiPoint);
	}

}

void Data::LoadBattleMap(MapClass * map)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Map_Battle.txt").c_str(), "r");
	if (fp == nullptr) return;

	char name[256];
	int x, y, type;
	int fx, fy;
	int sizeX, sizeY;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("MapSizeY", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d", &sizeX, &sizeY, sizeof(int));

		map->SetLoadMapSize(sizeX, sizeY);
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TYPE", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d%d%d%d", &x, &y, &fx, &fy, &type, sizeof(int));

		map->GetVMap()[y][x]->SetLoadObject({ x,y }, { fx,fy }, type, TILE);
		map->GetVMap()[y][x]->SetSeason(type);
	}

	fclose(fp);
}

void Data::LoadBattlePlayerPosition(ObjectManager * object)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Player_Pos_Battle.txt").c_str(), "r");
	if (fp == nullptr) return;

	char name[256], typeName[256], tChar[256];
	int x, y, type, kind, objectKind;
	int fX, fY;
	float offX, offY;
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("OBJECTKIND", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d", &x, &y, sizeof(int));
		fscanf_s(fp, "%f%f", &offX, &offY, sizeof(float));
		fscanf_s(fp, "%d%d%d%d", &fX, &fY, &type, &kind, sizeof(int));
		while (true) {
			fscanf_s(fp, "%s", &typeName, sizeof typeName);
			if (string(typeName).find("class", 0) == string::npos) break;
		}
		fscanf_s(fp, "%s", &tChar, sizeof tChar);

		fscanf_s(fp, "%d", &objectKind, sizeof(int));

		object->SetObject(name, { x,y }, { offX, offY }, { fX, fY }, objectKind, typeName, type, kind, 0);
	}

	fclose(fp);
}

void Data::LoadBattleMonsterPosition(ObjectManager * object, int quantity)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Monster_Pos_Battle.txt").c_str(), "r");
	if (fp == nullptr) return;

	char name[256], typeName[256], tChar[256];
	D2D_POINT_2L id;
	int type, kind, objectKind, monProperties;
	int fX, fY;
	float offX, offY;
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("OBJECTKIND", 0) != string::npos)
			break;
	}

	fscanf_s(fp, "%f%f", &offX, &offY, sizeof(float));
	fscanf_s(fp, "%d%d%d%d", &fX, &fY, &type, &kind, sizeof(int));
	while (true) {
		fscanf_s(fp, "%s", &typeName, sizeof typeName);
		if (string(typeName).find("class", 0) == string::npos) break;
	}
	fscanf_s(fp, "%s", &tChar, sizeof tChar);
	fscanf_s(fp, "%d", &objectKind, sizeof(int));

	for (int i = 0; i < quantity; i++)
	{
		id = object->ChkIDOverLab(object->GetPlayer()->GetId());
		if(type != MON_BEAR) monProperties = GetRandomInt(0, 3);
		else monProperties = GetRandomInt(0, 2);
		object->SetObject("", id, { offX, offY }, { fX, fY }, objectKind, typeName, type, kind, monProperties);
		
		if (!ChkMoveAble((Actor*)(object->GetVObject()[ACTOR][i + 1]))) {
			i--;
			object->GetVObject().pop_back();
		}

	}

	fclose(fp);
}

void Data::LoadBattleMonsterProperty(ObjectManager * object)
{
	FILE * fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Monster_Proper_Battle.txt").c_str(), "r");
	if (fp == nullptr) return;
	int x = 0;

	char name[256];
	int lv;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("LEVEL", 0) != string::npos)
			break;
	}

	fscanf_s(fp, "%d", &lv, sizeof(int));
	
	for (UINT i = 0; i < object->GetVObject()[ACTOR].size(); i++)
	{
		if (dynamic_cast<Actor*>(object->GetVObject()[ACTOR][i])->GetActorKind() == MONSTER) {
			dynamic_cast<Monster*>(object->GetVObject()[ACTOR][i])->StatusInit(lv);
		}
	}
}

bool Data::ChkMoveAble(Actor* actor)
{
	actor->GetAstar()->FindBattleMovePath();
	actor->GetAstar()->SeleteTarget();
	actor->GetAstar()->BattleUpdate();

	for (UINT i = 0; i < actor->GetAstar()->GetPathResult().size(); i++)
	{
		if (!actor->GetAstar()->GetPathResult()[i].isOpen) {
			actor->GetAstar()->ClearBattlePath();
			actor->GetAstar()->SetEnd(nullptr);
			return false;
		}
	}

	actor->GetAstar()->ClearBattlePath();
	actor->GetAstar()->SetEnd(nullptr);
	return true;
}
