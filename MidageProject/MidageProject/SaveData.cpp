#include "stdafx.h"
#include "Data.h"
#include "ObjectManager.h"
#include "MapClass.h"
#include "Tile.h"
#include "Matter.h"
#include "Player.h"
#include "Monster.h"
#include "PrograssBar.h"

void Data::SaveSlotNum(int slotNum)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "Player", "PlayerSelectInfo.txt").c_str(), "w+t");

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;
	temp = "SLOTNUM:\t" + to_string(slotNum);

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveMap(MapClass* map, string FileSource)
{
	FILE* fp = nullptr;
	// ������ ������ ���� �����ؼ� �ش� ���Ͽ� ���� (FileSource�� FileSource �Լ��� ��� �� ��)
	fopen_s(&fp, FileSource.c_str(), "w+t");

	if (fp == nullptr) return;

	// ���� ��ū
	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;														// ���Ͽ� �Է��� string ������ ����
	temp = "MapSizeX\tMapSizeY\n";										// �ʻ�����
	fwrite(temp.c_str(), temp.size(), 1, fp);							// temp ������ ���Ͽ� ����.
	temp = to_string(map->GetMapSizeX()) +
		token + to_string(map->GetMapSizeY()) + next;					// ���� X,Y ũ��
	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);							// �ٸ� �����Ϳ� �����ϱ� ���� ��ū
	fwrite(&next, sizeof next, 1, fp);

	temp = "NAME\tIDX\tIDY\tFRAMEX\tFRAMEY\tTYPE\n";					// Ÿ���� �Ӽ��� �Է�
	fwrite(temp.c_str(), temp.size(), 1, fp);

	for (UINT y = 0; y < map->GetVMap().size(); y++)
	{
		for (UINT x = 0; x < map->GetVMap()[y].size(); x++)
		{
			if (map->GetVMap()[y][x]->GetName() == "") continue;		// Ÿ���� �Ӽ��� ������ ��������
			temp = map->GetVMap()[y][x]->GetName() +					// Ÿ�� �̸�
				token + to_string(map->GetVMap()[y][x]->GetId().x) +	// Ÿ���� ���� X ID��
				token + to_string(map->GetVMap()[y][x]->GetId().y) +	// Ÿ���� ���� Y ID��
				token + to_string(map->GetVMap()[y][x]->GetFrame().x) +	// Ÿ���� X ������ ��
				token + to_string(map->GetVMap()[y][x]->GetFrame().y) +	// Ÿ���� Y ������ ��
				token + to_string(map->GetVMap()[y][x]->GetType()) +	// Ÿ���� �Ӽ�
				next;

			fwrite(temp.c_str(), temp.size(), 1, fp);
		}
	}
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);															//������ �Է� �Ϸ�� ������ �ݴ´�.
}

void Data::SavePlayerPosition(Player * player, string FileSource)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "w+t");

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "NAME\tIDX\tIDY\tOFFSETX\tOFFSETY\tFRAMEX\tFRAMEY\tTYPE\tKIND\tTYPENAME\tOBJECTKIND\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	temp = player->GetName() +
		token + to_string(player->GetId().x) +
		token + to_string(player->GetId().y) +
		token + to_string(player->GetOffset().width) +
		token + to_string(player->GetOffset().height) +
		token + to_string(player->GetFrame().x) +
		token + to_string(player->GetFrame().y) +
		token + to_string(player->GetType()) +
		token + to_string(player->GetKind()) +
		token + typeid(reinterpret_cast<Actor*>(player)).name() +
		token + to_string(player->GetActorKind()) +
		next;

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SavePlayerProperty(Player * player, string FileSource)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "w+t");

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "WORLDINFONAME\tWORLDINFONUM\tLEVEL\tEXP\tMAXEXP\tHP\tMP\tEARTHP\tWATERP\tFIREP\tWINDP\tVITAL\tSTR\tSTA\tDEX\tPOINT\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	temp = player->GetWorldInfoName() +
		token + to_string(player->GetWorldNum()) +
		token + to_string(player->GetLv()) +
		token + to_string(player->GetExp()) +
		token + to_string(player->GetMaxExp()) +
		token + to_string(player->GetHp()) +
		token + to_string(player->GetMp()) +
		token + to_string(player->GetEarthPoint()) +
		token + to_string(player->GetWaterPoint()) +
		token + to_string(player->GetFirePoint()) +
		token + to_string(player->GetWindPoint()) +
		token + to_string(player->GetVital()) +
		token + to_string(player->GetStrength()) +
		token + to_string(player->GetStamin()) +
		token + to_string(player->GetDexterity()) +
		token + to_string(player->GetStatPoint()) +
		next;

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveObjectPosition(ObjectManager * object, string FileSource)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "w+t");

	if (fp == nullptr) return;

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "NAME\tIDX\tIDY\tOFFSETX\tOFFSETY\tFRAMEX\tFRAMEY\tTYPE\tKIND\tTYPENAME\tOBJECTKIND\tMONPROPERTIES\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	for (UINT y = 0; y < object->GetVObject().size(); y++)
	{
		for (UINT x = 0; x < object->GetVObject()[y].size(); x++)
		{
			if (object->GetVObject()[y][x] == nullptr) continue;
			if (object->GetVObject()[y][x]->GetName() == "") continue;

			if (y == ACTOR) {
				if (dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetActorKind() == MONSTER) {
					temp = object->GetVObject()[y][x]->GetName() +
						token + to_string(object->GetVObject()[y][x]->GetId().x) +
						token + to_string(object->GetVObject()[y][x]->GetId().y) +
						token + to_string(object->GetVObject()[y][x]->GetOffset().width) +
						token + to_string(object->GetVObject()[y][x]->GetOffset().height) +
						token + to_string(object->GetVObject()[y][x]->GetFrame().x) +
						token + to_string(object->GetVObject()[y][x]->GetFrame().y) +
						token + to_string(object->GetVObject()[y][x]->GetType()) +
						token + to_string(object->GetVObject()[y][x]->GetKind()) +
						token + typeid(dynamic_cast<Actor*>(object->GetVObject()[y][x])).name() +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetActorKind()) +
						token + to_string(dynamic_cast<Monster*>(object->GetVObject()[y][x])->GetProperties()) +
						next;
				}
			}
			else if (y == MATTER) {
				temp = object->GetVObject()[y][x]->GetName() +
					token + to_string(object->GetVObject()[y][x]->GetId().x) +
					token + to_string(object->GetVObject()[y][x]->GetId().y) +
					token + to_string(object->GetVObject()[y][x]->GetOffset().width) +
					token + to_string(object->GetVObject()[y][x]->GetOffset().height) +
					token + to_string(object->GetVObject()[y][x]->GetFrame().x) +
					token + to_string(object->GetVObject()[y][x]->GetFrame().y) +
					token + to_string(object->GetVObject()[y][x]->GetType()) +
					token + to_string(object->GetVObject()[y][x]->GetKind()) +
					token + typeid(dynamic_cast<Matter*>(object->GetVObject()[y][x])).name() +
					token + to_string(dynamic_cast<Matter*>(object->GetVObject()[y][x])->GetMatterKind()) +
					next;
			}

			fwrite(temp.c_str(), temp.size(), 1, fp);
		}
	}
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveObjectProperty(ObjectManager * object, string FileSource)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "w+t");

	if (fp == nullptr) return;

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "NAME\tLEVEL\tEXP\tMAXEXP\tHP\tMP\tEARTHP\tWATERP\tFIREP\tWINDP\tVITAL\tSTR\tSTA\tDEX\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	for (UINT y = 0; y < object->GetVObject().size(); y++)
	{
		for (UINT x = 0; x < object->GetVObject()[y].size(); x++)
		{
			if (object->GetVObject()[y][x] == nullptr) continue;
			if (object->GetVObject()[y][x]->GetName() == "") continue;

			if (y == ACTOR) {
				if (dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetActorKind() == MONSTER) {
					temp = object->GetVObject()[y][x]->GetName() +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetLv()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetExp()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetMaxExp()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetHp()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetMp()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetEarthPoint()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetWaterPoint()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetFirePoint()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetWindPoint()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetVital()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetStrength()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetStamin()) +
						token + to_string(dynamic_cast<Actor*>(object->GetVObject()[y][x])->GetDexterity()) +
						next;
				}

			}
			fwrite(temp.c_str(), temp.size(), 1, fp);
		}
	}
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveBattleMap(MapClass * map, Player * player)
{
	Player* tPlayer = player;
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Map_Battle.txt").c_str(), "w+t");

	if (fp == nullptr) return;

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;
	temp = "MapSizeX\tMapSizeY\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);
	temp = to_string(10) + token + to_string(10) + next;
	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);

	temp = "NAME\tIDX\tIDY\tFRAMEX\tFRAMEY\tTYPE\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	int _y = tPlayer->GetId().y - 5;
	int _x = tPlayer->GetId().x - 5;

	if (_x < 0 ) _x = 0;
	if (_y < 0)	_y = 0;
	if (_x + 10 >= map->GetVMap().size()) _x -= 11;
	if (_y + 10 >= map->GetVMap().size()) _y -= 11;

	for (UINT y = _y; y < _y + 10; y++)
	{
		for (UINT x = _x; x < _x + 10; x++)
		{
			if (map->GetVMap()[y][x]->GetName() == "") continue;
			temp = map->GetVMap()[y][x]->GetName() +
				token + to_string(map->GetVMap()[y][x]->GetId().x - _x) +
				token + to_string(map->GetVMap()[y][x]->GetId().y - _y) +
				token + to_string(map->GetVMap()[y][x]->GetFrame().x) +
				token + to_string(map->GetVMap()[y][x]->GetFrame().y) +
				token + to_string(map->GetVMap()[y][x]->GetType()) +
				next;

			fwrite(temp.c_str(), temp.size(), 1, fp);
		}
	}
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveBattlePlayerPosition(Player * player)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Player_Pos_Battle.txt").c_str(), "w+t");

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "NAME\tIDX\tIDY\tOFFSETX\tOFFSETY\tFRAMEX\tFRAMEY\tTYPE\tKIND\tTYPENAME\tOBJECTKIND\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	temp = player->GetName() +
		token + to_string(5) +
		token + to_string(5) +
		token + to_string(player->GetOffset().width) +
		token + to_string(player->GetOffset().height) +
		token + to_string(player->GetFrame().x) +
		token + to_string(player->GetFrame().y) +
		token + to_string(player->GetType()) +
		token + to_string(player->GetKind()) +
		token + typeid(reinterpret_cast<Actor*>(player)).name() +
		token + to_string(player->GetActorKind()) +
		next;

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveBattleMonsterPosition(Monster * monster)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Monster_Pos_Battle.txt").c_str(), "w+t");

	if (fp == nullptr) return;

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "OFFSETX\tOFFSETY\tFRAMEX\tFRAMEY\tTYPE\tKIND\tTYPENAME\tOBJECTKIND\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	temp = to_string(monster->GetOffset().width) +
		token + to_string(monster->GetOffset().height) +
		token + to_string(monster->GetFrame().x) +
		token + to_string(monster->GetFrame().y) +
		token + to_string(monster->GetType()) +
		token + to_string(monster->GetKind()) +
		token + typeid(reinterpret_cast<Actor*>(monster)).name() +
		token + to_string(monster->GetActorKind()) +
		next;

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void Data::SaveBattleMonsterProperty(Monster * monster)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource("Resource", "World/Battle", "Monster_Proper_Battle.txt").c_str(), "w+t");

	if (fp == nullptr) return;

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;

	temp = "LEVEL\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	temp = to_string(monster->GetLv()) +
		next;

	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}