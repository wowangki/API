#pragma once
#include "SingletonBase.h"
class CameraModule : public SingletonBase<CameraModule>
{

public:
	CameraModule();
	~CameraModule();

	float x, y;
};

