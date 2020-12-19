#pragma once
#include "World.h"

class World8 :public World
{
public:
	World8();
	~World8();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

