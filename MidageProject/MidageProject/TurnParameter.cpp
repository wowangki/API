#include "stdafx.h"
#include "TurnParameter.h"
#include "Actor.h"
#include "ObjectManager.h"
#include "CommandUI.h"


TurnParameter::TurnParameter(ObjectManager* manager)
{
	this->manager = manager;
}


TurnParameter::~TurnParameter()
{
}

HRESULT TurnParameter::Init(void)
{	
	CreateParameter();

	return S_OK;
}

void TurnParameter::Release(void)
{
	SafeRelease(manager);
}

void TurnParameter::Render(void)
{
	for (int i = 0; i < 2; i++)
	{
		parameter[i].img->UiFrameRender(parameter[i].pos.x, parameter[i].pos.y, 0, 0,
			parameter[i].size.width, parameter[i].size.height);
	}
}

void TurnParameter::CreateParameter(void)
{
	parameter[0].img = _IMAGE->FindImage("TimeParameter_Ready");
	parameter[0].size.width = parameter[0].img->GetFrameWidth() * 1.2f;
	parameter[0].size.height = parameter[0].img->GetFrameHeight() * 0.6f;
	parameter[0].pos.x = WINSIZEX * 0.5f - parameter[0].size.width * 0.5f;
	parameter[0].pos.y = WINSIZEY - parameter[0].size.height;
	
	parameter[0].rc = FRectMake(parameter[0].pos.x, parameter[0].pos.y, parameter[0].size.width, parameter[0].size.height);

	parameter[1].img = _IMAGE->FindImage("TimeParameter_Active");
	parameter[1].size.width = parameter[1].img->GetFrameWidth() * 0.5f;
	parameter[1].size.height = parameter[1].img->GetFrameHeight() * 0.6f;
	parameter[1].pos.x = parameter[0].pos.x + parameter[0].size.width;
	parameter[1].pos.y = parameter[0].pos.y;
	parameter[1].rc = FRectMake(parameter[1].pos.x, parameter[1].pos.y, parameter[1].size.width, parameter[1].size.height);
}