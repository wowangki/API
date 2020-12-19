#pragma once
#include "UIClass.h"
class Pannel : public UIClass
{
public:
	Pannel();
	~Pannel();

	HRESULT Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale = { 1,1 }) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

