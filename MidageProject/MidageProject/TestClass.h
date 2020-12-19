#pragma once

class MapClass;
class ObjectManager;
class Data;
class PlayController;
class PlayUI;
class TestClass : public cApplication
{
private:
	MapClass * map;
	ObjectManager* object;
	Data* testData;
	PlayUI* ui;
	PlayController* controller;

public:
	TestClass();
	~TestClass();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;

	void ChangeMap(void);
};

