#pragma once
#include "World.h"

class World2 : public World
{
public:
	World2();
	~World2();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

