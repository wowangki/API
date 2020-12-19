#pragma once
class ImageSource
{
public:
	ImageSource();
	~ImageSource();

	HRESULT CreateTitleImage(void);
	HRESULT CreateTileImage(void);
	HRESULT CreateMatterImage(void);
	HRESULT CreateItemImage(void);
	HRESULT CreatePlayerImage(void);
	HRESULT CreateMonsterImage(void);
	HRESULT CreateUIImage(void);
	HRESULT CreateEffectImage(void);
};

