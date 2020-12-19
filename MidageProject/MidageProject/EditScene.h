#pragma once

class MapClass;
class EditUI;
class EditController;
class ObjectManager;
class EditScene :public cApplication
{
private:
	MapClass * editMap;
	EditUI * editUi;
	ObjectManager* manager;

	EditController * controller;

public:
	EditScene();
	~EditScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

