#include "stdafx.h"
#include "PlayerStatus.h"
#include "Pannel.h"
#include "Button.h"
#include "Player.h"

PlayerStatus::PlayerStatus(Player* player)
{
	this->player = player;
}


PlayerStatus::~PlayerStatus()
{
}

HRESULT PlayerStatus::Init(void)
{
	CreateMenu();
	CreateNamePannel();
	CreatePlayButton();
	CreatePointBar();
	SetPointBar();
	return S_OK;
}

HRESULT PlayerStatus::CreateInit(void)
{
	CreateSlotMenu();
	CreateNamePannel();
	CreateEditButton();
	CreateFunButton();
	CreatePointBar();

	return S_OK;
}

void PlayerStatus::Release(void)
{
	for (UINT i = 0; i < vPannel.size(); i++)
	{
		SafeRelease(vPannel[i]);
	}
	vPannel.clear();

	for (UINT y = 0; y < vBtn.size(); y++)
	{
		for (UINT x = 0; x < vBtn[y].size(); x++)
		{
			SafeRelease(vBtn[y][x]);
		}
	}
	vBtn.clear();
}

void PlayerStatus::Update(void)
{
	for (UINT i = 0; i < vPannel.size(); i++)
	{
		vPannel[i]->Update();
	}

	for (UINT y = 0; y < vBtn.size(); y++)
	{
		for (UINT x = 0; x < vBtn[y].size(); x++)
		{
			vBtn[y][x]->Update();
		}
	}

	for (UINT j = 0; j < vName.size(); j++)
	{
		vName[j].isCull = UIIsWindowOut(vName[j].rc);
		vName[j].rc = FRectMake(vPannel[j + 1]->GetPos().x + vPannel[j + 1]->GetSize().width * 0.5f + 10,
			vPannel[j + 1]->GetPos().y - (vPannel[j + 1]->GetSize().height * 0.5f), 120, 18);

	}

	for (UINT y = 0; y < vPointBar.size(); y++)
	{
		D2D_POINT_2F pos;
		pos.x = vName[y + 9].rc.left + 20;
		pos.y = vName[y + 9].rc.top;
		D2D_SIZE_F size;
		size.width = (vName[y + 9].rc.right - vName[y + 9].rc.left - 40) / 10;
		size.height = vName[y + 9].rc.bottom - vName[y + 9].rc.top;

		for (UINT x = 0; x < vPointBar[y].size(); x++)
		{
			vPointBar[y][x].isCull = UIIsWindowOut(vPointBar[y][x].rc);
			vPointBar[y][x].rc = FRectMake(pos.x, pos.y, size.width, size.height);
			pos.x += size.width;
		}
	}
}

void PlayerStatus::Render(void)
{
	for (UINT i = 0; i < vPannel.size(); i++)
	{
		vPannel[i]->Render();
	}

	for (UINT y = 0; y < vBtn.size(); y++)
	{
		for (UINT x = 0; x < vBtn[y].size(); x++)
		{
			vBtn[y][x]->UnNameRender();
			if (vBtn[y][x]->GetType() == SBTN_OK || vBtn[y][x]->GetType() == SBTN_INIT)
				_FONT->Render(vBtn[y][x]->GetName(), vBtn[y][x]->GetRc(), _BRUSH->GetBrush("BLACK"), "SELECT");
		}
	}

	for (UINT j = 0; j < vName.size(); j++)
	{
		if (vName[j].isCull) continue;
		_FONT->Render(vName[j].name, vName[j].rc, _BRUSH->GetBrush("BLACK"), "PANNEL");
	}

	for (UINT y = 0; y < vPointBar.size(); y++)
	{
		for (UINT x = 0; x < vPointBar[y].size(); x++)
		{
			switch (y) {
			case S_EARTH:
				if (vPointBar[y][x].isSelect) {
					_RenderTarget->FillRectangle(vPointBar[y][x].rc, _BRUSH->GetBrush("GREEN"));
				}
				else _RenderTarget->FillRectangle(vPointBar[y][x].rc, _Device->pDefaultBrush);
				break;
			case S_WATER:
				if (vPointBar[y][x].isSelect) {
					_RenderTarget->FillRectangle(vPointBar[y][x].rc, _BRUSH->GetBrush("BLUE"));
				}
				else _RenderTarget->FillRectangle(vPointBar[y][x].rc, _Device->pDefaultBrush);
				break;
			case S_FIRE:
				if (vPointBar[y][x].isSelect) {
					_RenderTarget->FillRectangle(vPointBar[y][x].rc, _BRUSH->GetBrush("RED"));
				}
				else _RenderTarget->FillRectangle(vPointBar[y][x].rc, _Device->pDefaultBrush);
				break;
			case S_WIND:
				if (vPointBar[y][x].isSelect) {
					_RenderTarget->FillRectangle(vPointBar[y][x].rc, _BRUSH->GetBrush("YELLOW"));
				}
				else _RenderTarget->FillRectangle(vPointBar[y][x].rc, _Device->pDefaultBrush);
				break;
			}
			_RenderTarget->DrawRectangle(vPointBar[y][x].rc, _BRUSH->GetBrush("GRAY"));
		}
	}
}

void PlayerStatus::StatusMove(void)
{
	float moveQuantity = vPannel[0]->GetSize().width + 1;

	if (vPannel[0]->GetIsCull()) {
		for (UINT i = 0; i < vPannel.size(); i++)
		{
			vPannel[i]->SetMovePos(moveQuantity, 0);
		}

		for (UINT y = 0; y < vBtn.size(); y++)
		{
			for (UINT x = 0; x < vBtn[y].size(); x++)
			{
				vBtn[y][x]->SetMovePos(moveQuantity, 0);
			}
		}
	}
	else {
		for (UINT i = 0; i < vPannel.size(); i++)
		{
			vPannel[i]->SetMovePos(-moveQuantity, 0);
		}

		for (UINT y = 0; y < vBtn.size(); y++)
		{
			for (UINT x = 0; x < vBtn[y].size(); x++)
			{
				vBtn[y][x]->SetMovePos(-moveQuantity, 0);
			}
		}
	}
}

Button * PlayerStatus::SelectButton(void)
{
	for (UINT y = 0; y < vBtn.size(); y++)
	{
		for (UINT x = 0; x < vBtn[y].size(); x++)
		{
			if (MouseInRect(vBtn[y][x]->GetRc())) {
				return vBtn[y][x];
			}
		}
	}

	return nullptr;
}

int PlayerStatus::SelectNameRc(void)
{
	for (UINT i = 0; i < vName.size(); i++)
	{
		if (MouseInRect(vName[i].rc)) {
			return i;
		}
	}

	return NULL;
}
