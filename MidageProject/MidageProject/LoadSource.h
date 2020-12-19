#pragma once
#include "cApplication.h"

enum Load_Kind {
	LOAD_GRAPHIC,
	LOAD_SOUND
};

enum GraphicLoad {
	GRAPHIC_FONT,
	GRAPHIC_COLOR,
	GRAPHIC_TITLE,
	GRAPHIC_TILE,
	GRAPHIC_MONSTER,
	GRAPHIC_ITEM,
	GRAPHIC_PLAYER,
	GRAPHIC_MATTER,
	GRAPHIC_EFFECT,
	GRAPHIC_UI
};

enum SoundLoad {
	SOUND_TITLE,
	SOUND_WORLD,
	SOUND_ACTOR
};


class ImageSource;
class SoundSource;
class SourceHouse;
class PrograssBar;
class LoadSource : public cApplication
{
private:
	PrograssBar * prograss;

private:
	ImageModule * img;
	int kind;
	int totalLoadProgress;
	int graphicProgress;
	int soundProgress;
	int progressPersent;

private:
	ImageSource * imgSource;

private:
	SoundSource * soundSource;

public:
	LoadSource();
	~LoadSource();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void FontInit(void);
	void BrushInit(void);
	bool LoadDone(void);

	void GraphicLoad(void);
	void SoundLoad(void);

	ImageSource* GetImageSource() { return imgSource; }
};

