#pragma once
#include "World.h"
class World1 : public World
{
public:
	World1();
	~World1();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

