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
			this->paletteName = paletteName;					// 매개변수와 key값이 동일하면
			vector<vector<GameObject*>> vTemp(iter->second);	// swap할 팔레트를 복사 생성
			vPalette.swap(vTemp);								// 복사 생성한 팔레트의 메모리값을 실사용 팔레트와 교체
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
