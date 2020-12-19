#pragma once
#include "World.h"

class World9 : public World
{
public:
	World9();
	~World9();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

