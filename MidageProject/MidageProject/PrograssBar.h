#pragma once
class PrograssBar
{
protected:
	struct Bar {
		D2D_RECT_F rc;
		D2D_POINT_2F pos;
		D2D_SIZE_F size;
		int progress;
	};

private:
	Bar total;
	Bar progress;

	bool isComplete;

public:
	PrograssBar();
	~PrograssBar();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	bool GetIsComplete(void) { return isComplete; }
	void SetProgress(int progress) { this->progress.progress = progress; }
};

