#pragma once

enum Ui_Kind {
	UI_MENU,
	UI_BUTTON
};

class Sound;
class UIClass
{
protected:

// bool
protected:
	bool			isActive;		//��ü Ȱ��ȭ ����
	bool			isCull;			//�׸��� ����

// ���� ��
protected:
	string			name;			//��ü �̸�
	D2D_POINT_2F	pos;			//��ġ ��
	D2D_RECT_F		rc;				//��ü RECT
	D2D_SIZE_F		size;			//��ü ũ��
	int				kind;			//��ü ����
	int				type;			//��ü Ÿ��
									// �̹���
protected:
	string			imgKey;			//�̹��� Ű
	ImageModule*	img;			//�̹���
	D2D_POINT_2L	frame;			//�̹��� �����Ӱ�
	float			opacity;		//����

public:
	UIClass();
	~UIClass();

	virtual HRESULT Init(string imgKey, D2D_POINT_2F pos, D2D_POINT_2L frame, int type, int kind, D2D_SIZE_F scale = { 1,1 });
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	string GetName() { return name; }
	ImageModule* GetImg() { return img; }
	D2D_POINT_2F GetPos() { return pos; }
	D2D_SIZE_F GetSize() { return size; }
	D2D_RECT_F GetRc() { return rc; }
	int GetKind() { return kind; }
	int GetType() { return type; }
	bool GetIsCull() { return isCull; }
	
	void SetName(string name) { this->name = name; }
	void SetImgKey(string imgKey) { this->imgKey = imgKey; }
	void SetPos(D2D_POINT_2F pos) { this->pos = pos; }
	void SetSize(D2D_SIZE_F size) { this->size = size; }
	void SetMovePos(float x = 0, float y = 0) { this->pos.x += x; this->pos.y += y; }
	void SetFrame(D2D_POINT_2L frame) { this->frame = frame; }
	
};

