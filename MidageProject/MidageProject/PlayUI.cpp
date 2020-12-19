#include "stdafx.h"
#include "PlayUI.h"
#include "SeasonUI.h"
#include "OptionUI.h"
#include "PlayerStatus.h"
#include "ObjectManager.h"
#include "TurnParameter.h"
#include "CommandUI.h"

PlayUI::PlayUI(int type)
	:type(type)
{
	season = nullptr;
	status = nullptr;
	parameter = nullptr;
	command = nullptr;
}


PlayUI::~PlayUI()
{
}

HRESULT PlayUI::Init(MapClass* map, ObjectManager* object)
{
	if (type == UI_FIELD) {
		season = new SeasonUI(map);
		status = new PlayerStatus(object->GetPlayer());
		season->Init();
		status->Init();
	}
	else if (type == UI_BATTLE) {
		parameter = new TurnParameter(object);
		parameter->Init();
		command = new CommandUI(object->GetPlayer());
		command->Init();
	}
	
	option = new OptionUI;
	option->Init();

	return S_OK;
}

void PlayUI::Release(void)
{
	SafeRelease(season);
	SafeRelease(status);
	SafeRelease(option);
	SafeRelease(parameter);
	SafeRelease(command);
}

void PlayUI::Update(void)
{
	if (type == UI_FIELD) {
		season->Update();
		status->Update();
	}
	else if (type == UI_BATTLE) {
		command->Update();
	}
	option->Update();

}

void PlayUI::Render(void)
{
	if (type == UI_FIELD) {
		season->Render();
		status->Render();
	}
	else if (type == UI_BATTLE) {
		parameter->Render();
		command->Render();
	}

	option->Render();
}
