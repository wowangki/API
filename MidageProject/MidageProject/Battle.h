#pragma once
#include "World.h"
#include <vector>

class Battle : public World
{
private:
	bool isGameOver;
	bool isEndBattle;

public:
	Battle();
	~Battle();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;

	void IsEnd(void);
	void ChkIsBattleEnd(vector<vector<class GameObject*>> vObject);
	void ChkGameOver(vector<vector<class GameObject*>> vObject);
};

