#pragma once

class MapClass;
class SaveLoadClass
{
private:
	MapClass * map;
	OPENFILENAME openFile;
	WCHAR str[256];
	wstring fileName;
	string ofileName;


public:
	SaveLoadClass();
	SaveLoadClass(MapClass* map);
	~SaveLoadClass();

	void SaveMap(void);
	void LoadMap(void);
	void LoadEditMap(void);

	void DefineOpenFile(void);
};

