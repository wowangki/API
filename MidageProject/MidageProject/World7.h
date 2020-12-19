#pragma once
#include "World.h"

class World7 : public World
{
public:
	World7();
	~World7();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

