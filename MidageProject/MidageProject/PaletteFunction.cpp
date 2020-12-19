#include "stdafx.h"
#include "Palette.h"
#include "Tile.h"
#include "Pannel.h"
#include "Button.h"

GameObject * Palette::SelectPalette(void)
{
	for (UINT y = 0; y < vPalette.size(); y++)
	{
		for (UINT x = 0; x < vPalette[y].size(); x++)
		{
			if (MouseInRect(vPalette[y][x]->GetRc()))
				return vPalette[y][x];
		}
	}
	return nullptr;
}

void Palette::ChangePalette(string paletteName)
{	
	for (mIter iter = mPalette.begin(); iter != mPalette.end(); iter++)
	{
		if (iter->first == paletteName) {
			this->paletteName = paletteName;					// �Ű������� key���� �����ϸ�
			vector<vector<GameObject*>> vTemp(iter->second);	// swap�� �ȷ�Ʈ�� ���� ����
			vPalette.swap(vTemp);								// ���� ������ �ȷ�Ʈ�� �޸𸮰��� �ǻ�� �ȷ�Ʈ�� ��ü
			return;
		}
	}

	vPalette.clear();
}

void Palette::SetMovePos(float moveX, float moveY)
{
	for (UINT y = 0; y < vPalette.size(); y++)
	{
		for (UINT x = 0; x < vPalette[y].size(); x++)
		{
			vPalette[y][x]->SetMovePos(moveX, moveY);
		}
	}
}
