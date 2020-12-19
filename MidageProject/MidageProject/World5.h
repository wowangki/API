#pragma once
#include "World.h"

class World5 : public World
{
public:
	World5();
	~World5();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

