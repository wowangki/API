#pragma once
#include "SingletonBase.h"
#include "cApplication.h"
#include <map>

class SourceHouse;
class SceneModule : public SingletonBase<SceneModule>
{
private:
	typedef map<string, cApplication*> _mScene;
	typedef map<string, cApplication*>::iterator mIter;

	static cApplication* currentScene;
	_mScene mScene;
	DWORD loadingThreadID;

public:
	SceneModule();
	~SceneModule();

	void Update(void);
	void Render(void);

public:
	cApplication * CreateScene(string SceneName, cApplication* curScene);
	HRESULT ChangeScene(string SceneName);
};

