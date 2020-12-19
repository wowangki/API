#pragma once
#include "SingletonBase.h"
#include <map>

#pragma comment (lib, "fmod/fmodex_vc.lib")
#include "fmod/fmod.hpp"

using namespace FMOD;

#define EXTRA_CHANNELBUFFER 5
#define SOUNDBUFFER 10
#define TOTAL_SOUNDBUFFER EXTRA_CHANNELBUFFER + SOUNDBUFFER

class SoundModule : public SingletonBase<SoundModule>
{
private:
	typedef map<string, int> _mSoundIndex;
	_mSoundIndex mSound;
	typedef _mSoundIndex::iterator mIter;

	int SoundIndexNumber;
	System* pSystem;
	Sound** ppSound;
	Channel** ppChannel;

	float fEffectVolume;
	float fBgmVolume;

public:
	SoundModule();
	~SoundModule();

	void Update(void);

	void CreateSound(string NickName, string SoundFile, bool bgm = true, bool loop = true);

	void Play(string NickName);
	void Stop(string NickName);
	void Pause(string NickName);
	void Resume(string NickName);
	void DeleteSound(string NickName);

	bool isPlay(string NickName);
	bool isPause(string NickName);

	float GetEffectVolume() { return fEffectVolume; }
	void SetEffectVolume(float value);

	float GetBgmVolume() { return fBgmVolume; }
	void SetBgmVolume(float value);
};

