#pragma once
#include "MenuClass.h"

class ButtonModule;
class MapEditMenu : public MenuClass
{
private:

public:
	MapEditMenu();
	MapEditMenu(D2D_POINT_2F pos, string FileName);
	~MapEditMenu();

	void Update() override;

	D2D_POINT_2F GetPos() override { return pos; }
	D2D_SIZE_F GetSize() override { return size; }
	bool GetIsMove() { return isMove; }
	bool GetIsOpen() { return isOpen; }
	float GetMoveSpeed() { return moveSpeed; }

	void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	void SetIsMove(bool isMove) { this->isMove = isMove; }
	void SetIsOpen(bool isOpen) { this->isOpen = isOpen; }
};

