#pragma once

enum Season_Kind {
	SEASON_SPRING,
	SEASON_SUMMER,
	SEASON_AUTUMN,
	SEASON_WINTER
};

class Season
{
private:
	int seasonKind;

	float elapsedTime;
	float changeTime;

public:
	Season();
	~Season();

	void Update(void);

	int GetSeasonKind(void) { return seasonKind; }
};

