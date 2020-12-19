#pragma once

namespace randomFunction {
	inline float GetRandomFloat(float min, float max) {
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (max - min) + min);
	}

	inline int GetRandomInt(int min, int max)
	{
		// CASE : MAX > 0
		if (max > 0)
		{
			int rnd = rand() % ((max - min) + 1);

			return (min + rnd);
		}

		// CASE : MAX < 0
		else
		{
			int rnd = rand() % (max - min);

			return (min + rnd);
		}
	}
}