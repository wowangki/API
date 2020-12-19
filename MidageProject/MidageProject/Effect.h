#pragma once
class Effect
{
private:
	class Actor* actor;
private:
	string imgKey;
	string preImgKey;
	ImageModule* img;
	D2D_POINT_2F pos;
	D2D_SIZE_F size;
	D2D_POINT_2L frame;
	int frameTime;
	int elapsedTime;
	bool isEffect;

public:
	Effect(class Actor* actor);
	~Effect();

	HRESULT Init(string effectImgKey);
	void Update(void);
	void Render(void);

	void SetPos(class Actor* target);
	void PlayEffectSound(void);
};

