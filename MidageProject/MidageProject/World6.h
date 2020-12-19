#pragma once
#include "World.h"

class World6 : public World
{
public:
	World6();
	~World6();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

