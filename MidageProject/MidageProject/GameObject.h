#pragma once

enum GameObject_Kind {
	ACTOR, MATTER, TILE
};

class Sound;
class Light;
class GameObject
{
// bool
protected:
	bool isAlive;			//��ü ���� ����
// ���� ��
protected:
	string			name;			//��ü �̸�
	D2D_POINT_2L	id;				//ID �� (ISO ��ü��)
	D2D_POINT_2F	pos;			//��ġ ��
	D2D_POINT_2F	rymPos[4];		//ISO ��ġ ��
	D2D_RECT_F		rc;				//��ü RECT
	D2D_SIZE_F		size;			//��ü ũ��
	D2D_SIZE_F		offset;			//ISO ��ü OFFSET
	GameObject_Kind kind;			//��ü ����
	int				type;			//��ü Ÿ��

// �̹���
protected:
	string			imgKey;			//�̹��� Ű
	ImageModule*	img;			//�̹���
	D2D_POINT_2L	frame;			//�̹��� �����Ӱ�
	float			opacity;		//����
	int				frameTime;		//������ �̵��ð�
	int				elapsedTime;	//������ �̵�����
	bool			isCull;

	// Edit MODE
protected:
	bool isEdit;

public:
	GameObject();
	~GameObject();

	virtual HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void SetName(int type) {};
	virtual void ISOMake(void);

	virtual HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind);
	virtual void PaletteUpdate(void);
	virtual void PaletteRender(void);

	void ChangeObject(D2D_POINT_2L frame, int type);
	virtual void SetLoadObject(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind);

	string GetName() { return name; }
	string GetImgKey() { return imgKey; }
	D2D_POINT_2L GetId() { return id; }
	D2D_POINT_2F GetPos() { return pos; }
	D2D_POINT_2F * GetRymPos() { return rymPos; }
	D2D_SIZE_F GetSize() { return size; }
	D2D_SIZE_F GetOffset() { return offset; }
	int GetType() { return type; }
	GameObject_Kind GetKind() { return kind; }
	D2D_RECT_F GetRc() { return rc; }
	D2D_POINT_2L GetFrame() { return frame; }
	ImageModule* GetImg() { return img; }
	bool GetIsAlive() { return isAlive; }
	int GetFrameTime() { return frameTime; }
	int GetElapsedTime() { return elapsedTime; }
	float GetOpacity() { return opacity; }
	

	void SetId(D2D_POINT_2L id) { this->id = id; }
	void SetPos(D2D_POINT_2F pos) { this->pos = pos; }
	void SetMovePos(float x, float y) { this->pos.x += x; this->pos.y += y; }
	void SetOffset(D2D_SIZE_F offset) { this->offset = offset; }
	void SetRc(D2D_RECT_F rc) { this->rc = rc; }
	void SetFrame(D2D_POINT_2L frame) { this->frame = frame; }
	void SetImg(string imgkey) { this->img = _IMAGE->FindImage(imgkey); }
	void SetSize(D2D_SIZE_F size) { this->size = size; }
	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	void SetIsEdit(bool isEdit) { this->isEdit = isEdit; }
};

