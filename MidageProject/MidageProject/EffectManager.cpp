#include "stdafx.h"
#include "EffectManager.h"
#include "Effect.h"

EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

void EffectManager::Update(void)
{
	for (UINT i = 0; i < vEffect.size(); i++)
	{
		vEffect[i]->Update();
	}
}

void EffectManager::Render(void)
{
	for (UINT i = 0; i < vEffect.size(); i++)
	{
		vEffect[i]->Render();
	}
}

void EffectManager::AddEffect(Effect * effect)
{
	vEffect.push_back(effect);
}

void EffectManager::DeleteEffect(Effect * effect)
{
	if (vEffect.empty()) return;

	for (UINT i = 0; i < vEffect.size(); i++)
	{
		if (vEffect[i] == effect) {
			vEffect.erase(vEffect.begin() + i);
		}
	}

}
