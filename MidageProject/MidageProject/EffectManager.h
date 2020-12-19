#pragma once
#include <vector>
class EffectManager
{
private:
	vector<class Effect*> vEffect;

public:
	EffectManager();
	~EffectManager();

	void Update(void);
	void Render(void);

	void AddEffect(Effect* effect);
	void DeleteEffect(Effect* effect);
};

