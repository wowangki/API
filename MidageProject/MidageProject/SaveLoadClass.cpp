#include "stdafx.h"
#include "SaveLoadClass.h"

SaveLoadClass::SaveLoadClass()
{
}

SaveLoadClass::SaveLoadClass(MapClass * map)
	:map(map)
{
	DefineOpenFile();
}


SaveLoadClass::~SaveLoadClass()
{
}

void SaveLoadClass::SaveMap(void)
{
	if (GetSaveFileName(&openFile)) {
		wstring sTemp = L"D:\\Programming\\00.포트폴리오\\MidageProject\\MidageProject\\";
		string sTemp_2 = "Resource\\SaveData\\";
		int tSize = sTemp.size();
		fileName = str;
		fileName.erase(fileName.begin(), fileName.begin() + tSize);
		ofileName = WstringToString(fileName);
		tSize = sTemp_2.size();
		ofileName.erase(ofileName.begin(), ofileName.begin() + tSize);
	}
	else return;
	
	HANDLE file = nullptr;
	file = CreateFile(fileName.c_str(), GENERIC_WRITE, FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(file);


	FILE* fp = nullptr;
	fopen_s(&fp, ofileName.c_str(), "w+t");

	char token = '\t';
	char next = '\n';
	char endToken = '/';

	string temp;
	temp = "TileSizeX\tTileSizeY\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);
	temp = "TileSize:\t" + to_string(map->GetTileSizeX()) +
		token + to_string(map->GetTileSizeY()) + next;
	fwrite(temp.c_str(), temp.size(), 1, fp);
	fwrite(&endToken, sizeof endToken, 1, fp);
	fwrite(&next, sizeof next, 1, fp);

	temp = "tileName\t\tIdX\tIdY\tFrameX\tFrameY\tTileStyle\tTileType\n";
	fwrite(temp.c_str(), temp.size(), 1, fp);

	for (UINT y = 0; y < map->GetMap().size(); y++)
	{
		for (UINT x = 0; x < map->GetMap()[y].size(); x++)
		{
			if (map->GetMap()[y][x]->GetTileName() == "") continue;

			temp = map->GetMap()[y][x]->GetTileName() +
				token + to_string(map->GetMap()[y][x]->GetId().x) +
				token + to_string(map->GetMap()[y][x]->GetId().y) +
				token + to_string(map->GetMap()[y][x]->GetGraphic()->GetFrame().x) +
				token + to_string(map->GetMap()[y][x]->GetGraphic()->GetFrame().y) +
				token + to_string(map->GetMap()[y][x]->GetTileStyle()) +
				token + to_string(map->GetMap()[y][x]->GetTileType()) + next;
			
			fwrite(temp.c_str(), temp.size(), 1, fp);
		}
	}
	fwrite(&endToken, sizeof endToken, 1, fp);
	fclose(fp);
}

void SaveLoadClass::LoadMap(void)
{
	if (GetOpenFileName(&openFile)) {
		wstring sTemp = L"D:\\Programming\\00.포트폴리오\\MidageProject\\MidageProject\\";
		string sTemp_2 = "Resource\\SaveData\\";
		int tSize = sTemp.size();
		fileName = str;
		fileName.erase(fileName.begin(), fileName.begin() + tSize);
		ofileName = WstringToString(fileName);
		tSize = sTemp_2.size();
		ofileName.erase(ofileName.begin(), ofileName.begin() + tSize);
	}
	else return;

	FILE* fp = nullptr;
	fopen_s(&fp, ofileName.c_str(), "r");

	char name[256];
	int idX, idY, fX, fY, tileStyle, tileType;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TileType", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d%d%d%d%d", &idX, &idY, &fX, &fY, &tileStyle, &tileType, sizeof(int));

		map->GetMap()[idY][idX]->SetLoadTile(name, { idX, idY }, { fX, fY }, tileStyle, tileType);
	}

	fclose(fp);
}

void SaveLoadClass::LoadEditMap(void)
{
	if (GetOpenFileName(&openFile)) {
		wstring sTemp = L"D:\\Programming\\00.포트폴리오\\MidageProject\\MidageProject\\";
		string sTemp_2 = "Resource\\SaveData\\";
		int tSize = sTemp.size();
		fileName = str;
		fileName.erase(fileName.begin(), fileName.begin() + tSize);
		ofileName = WstringToString(fileName);
		tSize = sTemp_2.size();
		ofileName.erase(ofileName.begin(), ofileName.begin() + tSize);
	}
	else return;

	FILE* fp = nullptr;
	fopen_s(&fp, ofileName.c_str(), "r");

	char name[256];
	int tileSizeX = 0, tileSizeY = 0;
	int idX, idY, fX, fY, tileStyle, tileType;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TileSizeY", 0) != string::npos)
			break;
	}

	while (true) {
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d", &tileSizeX, &tileSizeY, sizeof(int));

		if(tileSizeX != 0 && tileSizeY != 0)
		map->Resize(tileSizeX, tileSizeY);
	}


	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (string(name).find("TileType", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof name);
		if (name[0] == '/') break;

		fscanf_s(fp, "%d%d%d%d%d%d", &idX, &idY, &fX, &fY, &tileStyle, &tileType, sizeof(int));

		if (tileSizeX <= idX && tileSizeY <= idY) continue;
		map->GetMap()[idY][idX]->SetLoadTile(name, { idX, idY }, { fX, fY }, tileStyle, tileType);

	}

	fclose(fp);
}

void SaveLoadClass::DefineOpenFile(void)
{
	swprintf_s(str, L"");
	memset(&openFile, 0, sizeof(OPENFILENAME));
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.hwndOwner = AppDesc._hWnd;
	openFile.lpstrFilter = L"Text File\0*.txt;x.doc\0";
	openFile.lpstrFile = str;
	openFile.lpstrDefExt = L"txt";
	openFile.lpstrTitle = L"저장";
	openFile.nMaxFile = 256;
	openFile.lpstrInitialDir = L"Resource/SaveData";

}


