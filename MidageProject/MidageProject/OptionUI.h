#pragma once


enum Option_Btn {
	O_QUIT,
	O_CANCEL
};

class Pannel;
class Button;
class OptionUI
{
private:
	Pannel* pannel;
	Button* btn[2];

	struct MessageRc {
		D2D_SIZE_F size;
		D2D_RECT_F rc;
		bool isCull;
	};
	MessageRc message;

public:
	OptionUI();
	~OptionUI();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);
	
	void OptionMove(void);

	Button* SelectBtn(void);
	Pannel* GetMenu(void) { return pannel; }
};

