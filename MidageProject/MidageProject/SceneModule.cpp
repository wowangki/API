#include "stdafx.h"
#include "SceneModule.h"

cApplication* SceneModule::currentScene = nullptr;

SceneModule::SceneModule()
{
}


SceneModule::~SceneModule()
{
}

void SceneModule::Update(void)
{
	if (currentScene)
		currentScene->Update();
}

void SceneModule::Render(void)
{
	if (currentScene)
		currentScene->Render();
}

cApplication * SceneModule::CreateScene(string SceneName, cApplication * curScene)
{
	if (!curScene) return nullptr;

	mScene.insert(make_pair(SceneName, curScene));

	return curScene;
}

HRESULT SceneModule::ChangeScene(string SceneName)
{
	mIter iter = mScene.find(SceneName);

	if (iter == mScene.end()) return E_FAIL;
	if (iter->second == currentScene) return S_OK;

	if (SUCCEEDED(iter->second->Init())) {
		if (currentScene) currentScene->Release();

		currentScene = iter->second;
		return S_OK;
	}

	return E_FAIL;
}