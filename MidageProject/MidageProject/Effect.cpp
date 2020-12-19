#include "stdafx.h"
#include "Effect.h"
#include "Actor.h"
#include "BattleFunction.h"
#include "CommandUI.h"

Effect::Effect(Actor* actor)
	:actor(actor)
{
}


Effect::~Effect()
{
}

HRESULT Effect::Init(string effectImgKey)
{
	imgKey = effectImgKey;
	preImgKey = imgKey;
	img = _IMAGE->FindImage(imgKey);
	frame = { 0,0 };
	frameTime = actor->GetFrameTime();
	elapsedTime = actor->GetElapsedTime() * 50;
	isEffect = false;

	return S_OK;
}

void Effect::Update(void)
{
	if (!isEffect) {
		if (actor->GetMotion() == ACTOR_ATTACK &&
			actor->GetFrame().x == actor->GetImg()->GetMaxFrameX() - 1) {
			isEffect = true;
		}
	}

	if (isEffect) {
		frameTime++;
		if (frameTime % elapsedTime == 0) {
			frame.x++;
			frameTime = 0;

			if (frame.x == (int)(img->GetMaxFrameX() * 0.5f)) {
				PlayEffectSound();
			}

			if (frame.x >= img->GetMaxFrameX()) {
				frame.x = 0;
				isEffect = false;
				if (imgKey == "Effect_Guard") {
					_SOUND->Stop("Sound_Guard");
				}
				imgKey = preImgKey;
				img = _IMAGE->FindImage(imgKey);
			}
		}
	}
}

void Effect::Render(void)
{
	if(isEffect)
	img->CFrameRender(pos.x, pos.y, frame.x, frame.y, size.width, size.height);
}

void Effect::SetPos(Actor * target)
{
	pos = target->GetRymPos()[0];
	size = target->GetSize();

	if (target->GetComType() == COM_GUARD) {
		imgKey = "Effect_Guard";
		img = _IMAGE->FindImage(imgKey);
	}
}

void Effect::PlayEffectSound(void)
{
	string tImgKey[5] = { "Effect_Hit", "Effect_Slash", "Effect_Guard", "Effect_Claw", "Effect_Avoid" };
	string tSoundKey[5] = { "Sound_Hit", "Sound_Slash", "Sound_Guard", "Sound_Claw", "Effect_Avoid" };
	for (int i = 0; i < 5; i++)
	{
		if (tImgKey[i] == imgKey) {
			_SOUND->Play(tSoundKey[i]);
			return;
		}
	}
}
