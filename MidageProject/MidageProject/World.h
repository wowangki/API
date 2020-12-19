#pragma once

class MapClass;
class ObjectManager;
class Data;
class PlayController;
class PlayUI;
class World : public cApplication
{
protected:
	MapClass * map;
	ObjectManager* object;
	Data* data;
	PlayUI* ui;
	PlayController* controller;

public:
	World();
	~World();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetCam(void);
	void ChangeMap(void);
};

