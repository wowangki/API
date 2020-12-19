#pragma once
#include "World.h"
class World3 :public World
{

public:
	World3();
	~World3();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

