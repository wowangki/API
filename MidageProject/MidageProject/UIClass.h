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
	bool			isActive;		//객체 활성화 여부
	bool			isCull;			//그리기 여부

// 고유 값
protected:
	string			name;			//객체 이름
	D2D_POINT_2F	pos;			//위치 값
	D2D_RECT_F		rc;				//객체 RECT
	D2D_SIZE_F		size;			//객체 크기
	int				kind;			//객체 종류
	int				type;			//객체 타입
									// 이미지
protected:
	string			imgKey;			//이미지 키
	ImageModule*	img;			//이미지
	D2D_POINT_2L	frame;			//이미지 프레임값
	float			opacity;		//투명도

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

