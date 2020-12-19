#pragma once

class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	HRESULT CreateTitleSound(void);
	HRESULT CreateWorldSound(void);
	HRESULT CreateActorSound(void);
};

