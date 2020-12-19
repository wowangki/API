#include "stdafx.h"
#include "Season.h"


Season::Season()
{
	seasonKind = SEASON_SPRING;
	elapsedTime = 0;
	changeTime = 20;
}


Season::~Season()
{
}

void Season::Update(void)
{
	elapsedTime += _TIMER->GetElapsedTime();

	if (elapsedTime - changeTime > 0.0f) {
		elapsedTime = 0;
		seasonKind++;

		if (seasonKind > SEASON_WINTER)
		{
			seasonKind = SEASON_SPRING;
		}
	}

}