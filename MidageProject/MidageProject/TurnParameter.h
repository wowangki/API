#pragma once
#include <vector>


class ObjectManager;
class Actor;
class TurnParameter
{
private:
	ObjectManager* manager;

private:
	struct TimePrameter
	{
		D2D_POINT_2F pos;
		D2D_SIZE_F size;
		ImageModule* img;
		D2D_RECT_F rc;
	};

	TimePrameter parameter[2];

public:
	TurnParameter(ObjectManager* manager);
	~TurnParameter();

	HRESULT Init(void);
	void Release(void);
	void Render(void);

	void CreateParameter(void);

	TimePrameter* GetParmeter(void) { return parameter; }
};

