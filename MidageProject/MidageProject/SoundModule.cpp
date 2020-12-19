#include "stdafx.h"
#include "SoundModule.h"


SoundModule::SoundModule()
	:pSystem(nullptr), ppSound(nullptr), ppChannel(nullptr),
	SoundIndexNumber(0),
	fEffectVolume(1.0f),
	fBgmVolume(1.0f)
{
	System_Create(&pSystem);

	pSystem->init(TOTAL_SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	ppSound = new Sound*[TOTAL_SOUNDBUFFER];
	ppChannel = new Channel*[TOTAL_SOUNDBUFFER];

	memset(ppSound, 0, sizeof(Sound*) * TOTAL_SOUNDBUFFER);
	memset(ppChannel, 0, sizeof(Channel*) * TOTAL_SOUNDBUFFER);
}


SoundModule::~SoundModule()
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		DeleteSound(iter->first);
	}

	SafeDeleteArray(ppSound);
	SafeDeleteArray(ppChannel);
}

void SoundModule::Update(void)
{
}

void SoundModule::CreateSound(string NickName, string SoundFile, bool bgm, bool loop)
{
	if (loop) {
		if (bgm) {
			pSystem->createStream(SoundFile.c_str(),
				FMOD_LOOP_NORMAL, 0,
				&ppSound[mSound.size()]);
		}
		else {
			pSystem->createStream(SoundFile.c_str(),
				FMOD_LOOP_NORMAL, 0,
				&ppSound[mSound.size()]);
		}
	}
	else {
		if (bgm) {
			pSystem->createStream(SoundFile.c_str(),
				FMOD_DEFAULT, 0,
				&ppSound[mSound.size()]);
		}
		else {
			pSystem->createStream(SoundFile.c_str(),
				FMOD_DEFAULT, 0,
				&ppSound[mSound.size()]);
		}
	}

	mSound.insert(make_pair(NickName, SoundIndexNumber));
	SoundIndexNumber++;
}

void SoundModule::Play(string NickName)
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			pSystem->playSound(FMOD_CHANNEL_FREE,
				ppSound[temp],
				false,
				&ppChannel[temp]);
			
			ppChannel[temp]->setVolume(fEffectVolume);
			break;
		}
	}
}

void SoundModule::Stop(string NickName)
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			ppChannel[temp]->stop();
			break;
		}
	}
}

void SoundModule::Pause(string NickName)
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			ppChannel[temp]->setPaused(true);
			break;
		}
	}
}

void SoundModule::Resume(string NickName)
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			ppChannel[temp]->setPaused(false);
			break;
		}
	}
}

void SoundModule::DeleteSound(string NickName)
{
	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			if (isPlay(NickName)) Stop(NickName);

			int temp = iter->second;
			ppSound[temp]->release();
			break;
		}
	}

	SoundIndexNumber--;
}

bool SoundModule::isPlay(string NickName)
{
	bool isPlay = false;

	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			ppChannel[temp]->isPlaying(&isPlay);

			break;
		}
	}

	return isPlay;
}

bool SoundModule::isPause(string NickName)
{
	bool isPlay = false;

	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		if (iter->first == NickName) {
			int temp = iter->second;
			ppChannel[temp]->getPaused(&isPlay);

			break;
		}
	}
	return isPlay;
}

void SoundModule::SetEffectVolume(float value)
{
	fEffectVolume = value;

	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		int temp = iter->second;
		ppChannel[temp]->setVolume(fEffectVolume);
	}
}

void SoundModule::SetBgmVolume(float value)
{
	fBgmVolume = value;

	for (mIter iter = mSound.begin(); iter != mSound.end(); iter++) {
		int temp = iter->second;
		ppChannel[temp]->setVolume(fBgmVolume);
	}
}
