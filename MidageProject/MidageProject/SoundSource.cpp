#include "stdafx.h"
#include "SoundSource.h"


SoundSource::SoundSource()
{
}


SoundSource::~SoundSource()
{
}

HRESULT SoundSource::CreateTitleSound(void)
{
	_SOUND->CreateSound("TitleBackground", FileSource("Sound", "Title/Background", "Background.mp3"));
	_SOUND->CreateSound("TitleButtonMove", FileSource("Sound", "Title/Effect", "MoveButton.wav"), false, false);
	return S_OK;
}

HRESULT SoundSource::CreateWorldSound(void)
{
	_SOUND->CreateSound("WorldSpring", FileSource("Sound", "World", "World_Spring.mp3"));
	_SOUND->CreateSound("WorldSummer", FileSource("Sound", "World", "World_Summer.mp3"));
	_SOUND->CreateSound("WorldAutumn", FileSource("Sound", "World", "World_Autumn.mp3"));
	_SOUND->CreateSound("WorldWinter", FileSource("Sound", "World", "World_Winter.mp3"));
	_SOUND->CreateSound("WorldBattle", FileSource("Sound", "World", "World_Battle.mp3"));
	return S_OK;
}

HRESULT SoundSource::CreateActorSound(void)
{
	_SOUND->CreateSound("Sound_Avoid", FileSource("Sound", "Actor/Effect", "Sound_Avoid.wav"), false, false);
	_SOUND->CreateSound("Sound_Claw", FileSource("Sound", "Actor/Effect", "Sound_Claw.wav"), false, false);
	_SOUND->CreateSound("Sound_Hit", FileSource("Sound", "Actor/Effect", "Sound_Hit.wav"), false, false);
	_SOUND->CreateSound("Sound_Slash", FileSource("Sound", "Actor/Effect", "Sound_Slash.wav"), false, false);	
	_SOUND->CreateSound("Sound_Guard", FileSource("Sound", "Actor/Effect", "Sound_Guard.wav"), false);
	return S_OK;
}
