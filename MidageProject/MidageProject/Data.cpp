#include "stdafx.h"
#include "Data.h"
#include "ObjectManager.h"
#include "MapClass.h"
#include "Tile.h"
#include "Matter.h"

Data::Data()
	:saveTerm(0.0f), saveTime(10.0f)
{
}


Data::~Data()
{
}

void Data::AutoSave(ObjectManager * object, MapClass * map, string worldName)
{
	saveTerm += _TIMER->GetElapsedTime();

	if (saveTerm >= saveTime) {
		saveTerm = 0.0f;
	
		string name = "Object_Progress_" + worldName + ".txt";
		//SaveObjectLoca_Motion(object, FileSource("Resource", "World/" + worldName, name));
		//SavePlayerProperty(object->GetPlayer(), LoadSlotNum());
	}
}

bool Data::isExist(string FileSource)
{
	FILE* fp = nullptr;
	fopen_s(&fp, FileSource.c_str(), "r");

	if (fp != nullptr) {
		fclose(fp);
		return true;
	}
	else return false;
}

void Data::DeletePlayer(int slotNum)
{
	DeleteFile(StringToWstring(FileSource("Resource", "Player", "Player_slot" + to_string(slotNum) + "_Pos.txt")).c_str());
	DeleteFile(StringToWstring(FileSource("Resource", "Player", "Player_slot" + to_string(slotNum) + "_Property.txt")).c_str());
}
