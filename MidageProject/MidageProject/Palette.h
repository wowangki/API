#pragma once
#include <map>
#include <vector>
#define PALETTESIZEX 5
#define PALETTESIZEY 4

class GameObject;
class Pannel;
class Button;
class Palette
{
private:
	typedef map<string, vector<vector<GameObject*>>> _mPalette;
	typedef _mPalette::iterator mIter;

	_mPalette mPalette;								//팔레트 관리

private:
	vector<vector<GameObject*>> vPalette;			//실 사용 팔레트
	vector<vector<GameObject*>> vSeasonTile;		//계절 타일용 팔레트
	vector<vector<GameObject*>> vNonSeasonTile;		//비 계절 타일용 팔레트
	vector<vector<GameObject*>> vMatter;			//맵 오브젝트용 팔레트
	vector<vector<GameObject*>> vPlayer;			//플레이어용 팔레트
	vector<vector<GameObject*>> vBeast;				//몬스터(야수)용 팔레트
	vector<vector<GameObject*>> vDemon;				//몬스터(악마)용 팔레트
	vector<vector<GameObject*>> vHuman;				//몬스터(인간)용 팔레트
	vector<vector<GameObject*>> vDragon;			//몬스터(용족)용 팔레트

private:
	string paletteName;

public:
	Palette();
	~Palette();

	HRESULT Init(Pannel* menu);
	HRESULT CreateSeasonTile(Pannel* menu);			//계절 타일 팔레트 생성
	HRESULT CreateNonSeasonTile(Pannel* menu);		//비 계절 타일 팔레트 생성
	HRESULT CreateMatter(Pannel* menu);				//맵 오브젝트 팔레트 생성
	HRESULT CreatePlayer(Pannel* menu);				//플레이어 팔레트 생성
	HRESULT CreateBeast(Pannel* menu);				//몬스터(야수) 팔레트 생성
	HRESULT CreateDemon(Pannel* menu);				//몬스터(악마) 팔레트 생성
	HRESULT CreateHuman(Pannel* menu);				//몬스터(인간) 팔레트 생성
	HRESULT CreateDragon(Pannel* menu);				//몬스터(용족) 팔레트 생성

	void Release(void);
	void Update(Button* btn);
	void Render(void);

	GameObject* SelectPalette(void);
	void ChangePalette(string paletteName);
	void SetMovePos(float moveX = 0, float moveY = 0);

	string GetPaletteName(void) { return paletteName; }
};

