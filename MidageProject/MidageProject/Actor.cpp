#include "stdafx.h"
#include "Actor.h"
#include "SearchObject.h"
#include "ObjectManager.h"
#include "AStar.h"
#include "CommandUI.h"
#include "BattleFunction.h"
#include "Effect.h"
#include "PropertyBar.h"

Actor::Actor()
{
	parameter = nullptr;
	turnBoard = nullptr;
	statusBar = nullptr;
}


Actor::~Actor()
{
}

HRESULT Actor::Init(D2D_POINT_2L id, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	GameObject::Init(id, frame, type, kind);
	this->type = type;
	this->offset.width = _IMAGE->FindImage("Tile_Spring")->GetFrameWidth();
	this->offset.height = _IMAGE->FindImage("Tile_Spring")->GetFrameHeight();
	isRight = false;
	isInBattle = false;
	moveSpeed = 4.0f;
	isTurn = false;
	isReady = false;
	isExcute = false;
	ISOMake();
	prePos = pos;
	excuteTime = 5.0f;
	bFunction = new BattleFunction(this);
	effect = new Effect(this);
	return S_OK;
}

void Actor::Release(void)
{
	GameObject::Release();
}

void Actor::Update(void)
{
	rc = FRectMakeCenter(pos.x, pos.y - size.height * 0.5f, size.width, size.height);
	isCull = IsWindowOut(rc);
	if (map == nullptr) {
		ISOMake();
	}
	else {
		RymBusPointMake(pos, rymPos, offset);
		if (!isCull) {
			FrameUpdate();
			SetMotion();
			ChangeId();
			statusBar->Update();

			if (!isAlive) {
				if (opacity >= 0) opacity -= 0.1f;
			}
		}
	}
}

void Actor::Render(void)
{
	if (isCull) return;
	img->CFrameRender(rymPos[2].x, rymPos[2].y, frame.x, frame.y, 0.0f, isRight, size.width, size.height, opacity);
	if(statusBar != nullptr) statusBar->Render();

	if (turnBoard)
	{
		turnBoard->boardImg->CUiFrameRender(turnBoard->pos.x, turnBoard->pos.y, 0, 0,
			turnBoard->size.width, turnBoard->size.height);
		turnBoard->arrowImg->CUiFrameRender(turnBoard->pos.x, turnBoard->pos.y + turnBoard->size.height * 0.5f,
			0, 0, turnBoard->arrowSize.width, turnBoard->arrowSize.height);
		turnBoard->actorImg->CUiFrameRender(turnBoard->pos.x, turnBoard->pos.y,
			0, 0, turnBoard->size.width, turnBoard->size.height);
	}
}

HRESULT Actor::PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, int type, GameObject_Kind kind)
{
	GameObject::PaletteInit(pos, frame, type, kind);
	this->size = { 35,35 };
	this->pos.x += size.width * 0.5f;
	this->pos.y += size.height * 0.5f;
	this->type = type;
	return S_OK;
}

void Actor::PaletteUpdate(void)
{
	GameObject::PaletteUpdate();
}

void Actor::PaletteRender(void)
{
	if (isCull) return;
	GameObject::PaletteRender();
}

void Actor::FrameUpdate(void)
{
	frameTime++;
	if (frameTime % elapsedTime == 0) {
		frame.x++;
		frameTime = 0;
		if (frame.x >= img->GetMaxFrameX()) {
			if (comType == COM_GUARD) {
				frame.x = img->GetMaxFrameX() - 1;
			}
			else {
				frame.x = 0;
				if (isInBattle) {
					isInBattle = false;
				}
			}
		}
	}
}

void Actor::SetMotion(void)
{
	if (prePos.x == pos.x &&
		prePos.y == pos.y)
	{
		if (isInBattle) {
			if (comType == COM_GUARD) {
				if (motion != ACTOR_GUARD) {
					motion = ACTOR_GUARD;
					frame.x = 0;
				}
			}
			else if (comType == COM_AVOID) {

			}
			else {
				if (isExcute) {
					if (motion != ACTOR_ATTACK) {
						motion = ACTOR_ATTACK;
						frame.x = 0;
					}
				}
				else {
					if (motion != ACTOR_DAMAGE) {
						motion = ACTOR_DAMAGE;
						frame.x = 0;
					}
				}
			}
		}
		else {
			if (motion == ACTOR_MOVE ||
				(motion != ACTOR_MOVE && !isInBattle)) {
				if (motion != ACTOR_IDLE) {
					motion = ACTOR_IDLE;
					frame.x = 0;
				}
			}
		}
	}
	else {
		if(motion != ACTOR_MOVE) motion = ACTOR_MOVE;
	}

	if (prePos.x > pos.x)
	{
		isRight = false;
	}
	else if (prePos.x < pos.x)
	{
		isRight = true;
	}

	if (prePos.y > pos.y)
	{
		frame.y = 1;
	}
	else if (prePos.y < pos.y)
	{
		frame.y = 0;
	}

	ChangeImage();

	if (frame.y >= img->GetMaxFrameY()) frame.y = 0;
	prePos.x = pos.x;
	prePos.y = pos.y;
}

void Actor::ExcuteTimeUpdate(void)
{
	if (!isExcute) {
		if (comType == COM_GUARD || comType == COM_AVOID) excuteTime = 1.0f;
		else excuteTime = 6.0f;
		return;
	}

	excuteTime -= _TIMER->GetElapsedTime();

	if (excuteTime <= 0)
	{
		astar->ClearBattlePath();
		astar->SetEnd(nullptr);
		pathNum = 0;
		excuteTime = 6.0f;
		comType = COM_DEFAULT;
		isExcute = false;
	}
}
