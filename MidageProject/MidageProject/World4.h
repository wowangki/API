#pragma once
#include "World.h"

class World4 : public World
{
public:
	World4();
	~World4();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

