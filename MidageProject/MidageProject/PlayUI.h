#pragma once

enum PlayUI_Type {
	UI_FIELD,
	UI_BATTLE
};

class SeasonUI;
class PlayerStatus;
class OptionUI;
class TurnParameter;
class CommandUI;
class MapClass;
class ObjectManager;
class PlayUI
{
private:
	SeasonUI* season;
	PlayerStatus* status;
	OptionUI* option;
	TurnParameter* parameter;
	CommandUI* command;

private:
	int type;

public:
	PlayUI(int type);
	~PlayUI();

	HRESULT Init(MapClass* map, ObjectManager* object);
	void Release(void);
	void Update(void);
	void Render(void);
	
	int GetType(void) { return type; }
	SeasonUI* GetSeason(void) { return season; }
	PlayerStatus* GetStatus(void) { return status; }
	OptionUI* GetOption(void) { return option; }
	CommandUI* GetCommand(void) { return command; }
	TurnParameter* GetParameter(void) { return parameter; }
};

