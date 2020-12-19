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
	// 해당 파일에서 읽어온다 (FileSource는 FileSource 함수를 사용 할 것)
	fopen_s(&fp, FileSource.c_str(), "r");
	if (fp == nullptr) return;													//파일이 존재하지 않으면 반환

	char name[256];																//타일 이름 변수
	int x, y, type;																//IDX , IDY, 속성 값 변수
	int fx, fy;																	//FrameX , FrameY 값 변수
	int sizeX, sizeY;															//MapSizeX , MapSizeY 값 변수

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);									//파일내의 string 데이형 값을 변수에 입력
		if (string(name).find("MapSizeY", 0) != string::npos)					//마지막 데이터 종류 구분 값 찾음
			break;
	}
	
	while (true)
	{
		fscanf_s(fp, "%d%d", &sizeX, &sizeY, sizeof(int));						//파일내의 맵사이즈를 사이즈 변수에 입력
	
		map->SetLoadMapSize(sizeX, sizeY);										//맵의 사이즈를 재조정

		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;												//구분 토큰을 찾으면 루프문 탈출
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TYPE", 0) != string::npos)						//마지막 데이터 종류 구분 값 찾음
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);									//파일내의 string 데이형 값을 변수에 입력
		if (name[0] == '/') break;												//구분 토큰을 찾으면 루프문 탈출

		fscanf_s(fp, "%d%d%d%d%d", &x, &y, &fx, &fy, &type, sizeof(int));		//파일내의 IDX, IDY, FrameX, FrameY, 속성 값을 해당 대응 변수에 입력

		map->GetVMap()[y][x]->SetLoadObject({ x,y }, { fx,fy }, type, TILE);	//해당 IDX,IDY 값의 타일에 해당 값을 설정
		map->GetVMap()[y][x]->SetSeason(type);									//타일의 속성값에 따라 계절 속성을 부여
	}

	fclose(fp);																	//데이터 입력 완료시 파일을 닫는다.
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
