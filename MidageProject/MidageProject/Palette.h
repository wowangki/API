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

	_mPalette mPalette;								//�ȷ�Ʈ ����

private:
	vector<vector<GameObject*>> vPalette;			//�� ��� �ȷ�Ʈ
	vector<vector<GameObject*>> vSeasonTile;		//���� Ÿ�Ͽ� �ȷ�Ʈ
	vector<vector<GameObject*>> vNonSeasonTile;		//�� ���� Ÿ�Ͽ� �ȷ�Ʈ
	vector<vector<GameObject*>> vMatter;			//�� ������Ʈ�� �ȷ�Ʈ
	vector<vector<GameObject*>> vPlayer;			//�÷��̾�� �ȷ�Ʈ
	vector<vector<GameObject*>> vBeast;				//����(�߼�)�� �ȷ�Ʈ
	vector<vector<GameObject*>> vDemon;				//����(�Ǹ�)�� �ȷ�Ʈ
	vector<vector<GameObject*>> vHuman;				//����(�ΰ�)�� �ȷ�Ʈ
	vector<vector<GameObject*>> vDragon;			//����(����)�� �ȷ�Ʈ

private:
	string paletteName;

public:
	Palette();
	~Palette();

	HRESULT Init(Pannel* menu);
	HRESULT CreateSeasonTile(Pannel* menu);			//���� Ÿ�� �ȷ�Ʈ ����
	HRESULT CreateNonSeasonTile(Pannel* menu);		//�� ���� Ÿ�� �ȷ�Ʈ ����
	HRESULT CreateMatter(Pannel* menu);				//�� ������Ʈ �ȷ�Ʈ ����
	HRESULT CreatePlayer(Pannel* menu);				//�÷��̾� �ȷ�Ʈ ����
	HRESULT CreateBeast(Pannel* menu);				//����(�߼�) �ȷ�Ʈ ����
	HRESULT CreateDemon(Pannel* menu);				//����(�Ǹ�) �ȷ�Ʈ ����
	HRESULT CreateHuman(Pannel* menu);				//����(�ΰ�) �ȷ�Ʈ ����
	HRESULT CreateDragon(Pannel* menu);				//����(����) �ȷ�Ʈ ����

	void Release(void);
	void Update(Button* btn);
	void Render(void);

	GameObject* SelectPalette(void);
	void ChangePalette(string paletteName);
	void SetMovePos(float moveX = 0, float moveY = 0);

	string GetPaletteName(void) { return paletteName; }
};

