#pragma once
#include "PrograssBar.h"
class PropertyBar : public PrograssBar
{
private:
	class Actor* actor;

private:
	Bar totalHpBar;
	Bar hpBar;

	float totalHp;
	float presentHp;
	float hpPersent;
	float moveSpeed;

public:
	PropertyBar(class Actor* actor);
	~PropertyBar();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void HpBarMove(void);
};

