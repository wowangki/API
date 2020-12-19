#pragma once
#include "PlayerSelect.h"

class ObjectManager;
class MapClass;
class Player;
class Monster;
class Data
{
public:
	struct PlayerLoad
	{
		string pos;
		string proper;
	};

private:
	float saveTerm;
	float saveTime;

public:
	Data();
	~Data();

	void AutoSave(ObjectManager* object, MapClass* map, string worldName);

	//Check
	bool isExist(string FileSource);
	//Delete
	void DeletePlayer(int slotNum);

	//Save
	// Slot
	void SaveSlotNum(int slotNum);
	
	//FIELD
	//MAP
	void SaveMap(MapClass* map, string FileSource);
	//OBJECT
	//Player
	void SavePlayerPosition(Player* player, string FileSource);
	void SavePlayerProperty(Player* player, string FileSource);
	//Monster & Matter
	void SaveObjectPosition(ObjectManager* object, string FileSource);
	void SaveObjectProperty(ObjectManager* object, string FileSource);

	//BATTLE
	void SaveBattleMap(MapClass* map, Player* player);
	void SaveBattlePlayerPosition(Player* player);
	void SaveBattleMonsterPosition(Monster* monster);
	void SaveBattleMonsterProperty(Monster* monster);

	//Load
	//FIELD
	//Slot
	PlayerLoad LoadSlotNum(void);
	//MAP
	void LoadMap(MapClass* map, string FileSource);
	//OBJECT
	//Player
	void LoadPlayerInitPosition(Player* player);
	void LoadPlayerPosition(ObjectManager* object, string FileSource);
	void LoadPlayerProperty(Player* player, string FileSource);
	//Monster & Matter
	void LoadObjectPosition(ObjectManager* object, string FileSource);
	void LoadObjectProperty(ObjectManager* object, string FileSource);

	//BATTLE
	void LoadBattleMap(MapClass* map);
	void LoadBattlePlayerPosition(ObjectManager* object);
	void LoadBattleMonsterPosition(ObjectManager* object, int quantity);
	void LoadBattleMonsterProperty(ObjectManager* object);

	bool ChkMoveAble(class Actor* actor);
	
};

//	#include <commdlg.h> 반드시 추가해야함
//	OPENFILENAME		 하고싶으면 찾아보삼