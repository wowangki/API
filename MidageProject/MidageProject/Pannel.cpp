#include "stdafx.h"
#include "Pannel.h"


Pannel::Pannel()
{
}


Pannel::~Pannel()
{
}

HRESULT Pannel::Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale)
{
	UIClass::Init(imgKey, pos, frame, type, kind, scale);
	
	return S_OK;
}

void Pannel::Release(void)
{
	UIClass::Release();
}

void Pannel::Update(void)
{
	UIClass::Update();
}

void Pannel::Render(void)
{
	UIClass::Render();
	if (name != imgKey)
		_FONT->Render(name, rc, nullptr, "PANNEL");
}
