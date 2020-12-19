#include "stdafx.h"
#include "ObjectManager.h"
#include "Matter.h"
#include "Player.h"
#include "Monster.h"
#include "Tile.h"
#include "MapClass.h"
#include "EffectManager.h"


ObjectManager::ObjectManager()
{
	map = nullptr;
}

ObjectManager::ObjectManager(MapClass * map)
{
	this->map = map;
}

ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::Init(void)
{
	for (UINT y = 0; y < 2; y++)
	{
		vector<GameObject*> vTemp;
		vObject.push_back(vTemp);
	}

	sortTime = 30.0f;
	_BRUSH->CreateBrush("TEST", RGB(255, 0, 255));

	effect = new EffectManager;
	return S_OK;
}

void ObjectManager::Release(void)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] != nullptr)
			vObject[y][x]->Release();
		}
	}
}

void ObjectManager::Update(void)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		SortObject(y, 0, vObject[y].size() - 1);
	}

	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] != nullptr)
			vObject[y][x]->Update();
			
		}
	}
}

void ObjectManager::BattleUpdate(void)
{
	for (UINT x = 0; x < vObject[ACTOR].size(); x++)
	{
		if (vObject[ACTOR][x]->GetOpacity() <= 0) {
			vObject[ACTOR].erase(vObject[ACTOR].begin() + x);
			continue;
		}
		if (vObject[ACTOR][x] == nullptr) break;

		dynamic_cast<Actor*>(vObject[ACTOR][x])->BattleUpdate();

		if (dynamic_cast<Actor*>(vObject[ACTOR][x])->GetIsInBattle()) {
			if (dynamic_cast<Actor*>(vObject[ACTOR][x])->GetMotion() == ACTOR_ATTACK) {
				effect->AddEffect(dynamic_cast<Actor*>(vObject[ACTOR][x])->GetEffect());
			}
			else effect->DeleteEffect(dynamic_cast<Actor*>(vObject[ACTOR][x])->GetEffect());
		}

		if (dynamic_cast<Actor*>(vObject[ACTOR][x])->GetIsExcute()) {
			SortObject(ACTOR, 0, vObject[ACTOR].size() - 1);
		}
	}

	effect->Update();
}

void ObjectManager::Render(void)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] != nullptr) {
				vObject[y][x]->Render();
				//_RenderTarget->DrawRectangle(vObject[y][x]->GetRc(), _BRUSH->GetBrush("TEST"));
			}
		}
	}
	
	effect->Render();
}


void ObjectManager::SetObject(Matter * matter, Tile* tile)
{
	if (tile == nullptr || matter == nullptr) return;

	if (!vObject[matter->GetKind()].empty()) {
		
		for (UINT i = 0; i < vObject[matter->GetKind()].size(); i++)
		{
			if (vObject[matter->GetKind()][i]->GetPos().x == tile->GetPos().x &&
				vObject[matter->GetKind()][i]->GetPos().y == tile->GetPos().y)
				return;
		}
	}

	if (matter->GetMatterKind() == TREE) {
		Matter* tree = new Matter;
		tree->Init(tile->GetId(), matter->GetFrame(), matter->GetMatterKind(), matter->GetType(), matter->GetKind());
		tree->SetOffset(tile->GetOffset());
		vObject[MATTER].push_back(tree);
	}
}

void ObjectManager::SetObject(Actor * actor, Tile * tile)
{
	if (tile == nullptr || actor == nullptr) return;

	if (!vObject[actor->GetKind()].empty()) {

		for (UINT i = 0; i < vObject[actor->GetKind()].size(); i++)
		{
			if (vObject[actor->GetKind()][i]->GetPos().x == tile->GetPos().x &&
				vObject[actor->GetKind()][i]->GetPos().y == tile->GetPos().y)
				return;
		}

	}

	if (actor->GetActorKind() == PLAYER) {
		Player* player = new Player;
		player->Init(tile->GetId(), actor->GetFrame(), actor->GetType(), actor->GetKind());
		player->SetOffset(tile->GetOffset());
		vObject[ACTOR].push_back(player);
	}
	else if (actor->GetActorKind() == MONSTER) {
		Monster* monster = new Monster;
		monster->Init(tile->GetId(), actor->GetFrame(), dynamic_cast<Monster*>(actor)->GetProperties(), actor->GetType(), actor->GetKind());
		monster->SetOffset(tile->GetOffset());
		vObject[ACTOR].push_back(monster);
	}

}

void ObjectManager::SetObject(string name, D2D_POINT_2L id, D2D_SIZE_F offset, D2D_POINT_2L frame, int objectKind, string typeName, int type, int kind, int properties)
{
	if (string(typeName).find("Matter") != string::npos) {
		if (objectKind == TREE) {
			Matter* tree = new Matter;
			tree->Init(id, frame, (Matter_Kind)objectKind, type, (GameObject_Kind)kind);
			tree->SetOffset(offset);
			if (CheckOverLap(tree)) {
				vObject[MATTER].push_back(tree);
			}
		}
	}
	else if (string(typeName).find("Actor") != string::npos) {
		if (objectKind == PLAYER) {
			Player* player = new Player(map, this);
			player->Init(id, frame, type, (GameObject_Kind)kind);
			player->SetName(name);
			player->StatusInit(0, 0, 0, 0);
			player->SetOffset(offset);
			player->SetProperty(0, 0, 0, 0);
			if (CheckOverLap(player)) {
				vObject[ACTOR].push_back(player);
			}
		}
		else if (objectKind == MONSTER) {
			Monster* monster = new Monster(map, this);
			monster->Init(id, frame, (Monster_Properties)properties, type, (GameObject_Kind)kind);
			monster->SetOffset(offset);
			if (CheckOverLap(monster)) {
				vObject[ACTOR].push_back(monster);
			}
		}
	}
}

void ObjectManager::SetObjectTimeBoard(TurnParameter* parameter)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x]->GetKind() == ACTOR) {
				dynamic_cast<Actor*>(vObject[y][x])->CreateTimeBoard(parameter);
			}
		}
	}

}

void ObjectManager::EraseObject(void)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			if (vObject[y][x] == nullptr) continue;
			if (MouseInISO(vObject[y][x]->GetRymPos())) {
				vObject[y].erase(vObject[y].begin() + x);
			}
		}
	}
}

void ObjectManager::DeleteObject(void)
{
	Player* tPlayer = GetPlayer();

	for (UINT x = 0; x < vObject[ACTOR].size(); x++)
	{
		if (tPlayer->GetEngageMonster() == vObject[ACTOR][x]) {
			vObject[ACTOR].erase(vObject[ACTOR].begin() + x);
			return;
		}
	}
}

bool ObjectManager::CheckOverLap(GameObject * object)
{
	if (vObject.empty()) return true;
	if (vObject[object->GetKind()].empty()) return true;
	
	for (UINT i = 0; i < vObject[object->GetKind()].size(); i++)
	{
		if (object->GetId().x == vObject[object->GetKind()][i]->GetId().x &&
			object->GetId().y == vObject[object->GetKind()][i]->GetId().y &&
			object->GetImg() == vObject[object->GetKind()][i]->GetImg())
			return false;
	}

	return true;
}

D2D_POINT_2L ObjectManager::ChkIDOverLab(D2D_POINT_2L chkOverLab)
{
	D2D_POINT_2L temp;
	bool isOverLab = false;
	while (true) {
		temp.x = GetRandomInt(0, map->GetVMap().size() - 1);
		temp.y = GetRandomInt(0, map->GetVMap().size() - 1);

		if (map->GetVMap()[temp.y][temp.x]->GetType() == TILE_LIQUDE ||
			map->GetVMap()[temp.y][temp.x]->GetType() == TILE_DEFAULT) continue;

		for (UINT i = 0; i < vObject[ACTOR].size(); i++)
		{
			if (vObject[ACTOR][i]->GetId().x != temp.x && 
				vObject[ACTOR][i]->GetId().y != temp.y) {
				isOverLab = true;
			}
			else isOverLab = false;
		}
		
		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (temp.x == chkOverLab.x + x &&
					temp.y == chkOverLab.y + y) {
					isOverLab = true;
				}
				else isOverLab = false;
			}
		}

		if (!isOverLab) return temp;
	}
}

void ObjectManager::SortObject(UINT type, int start, int end)
{
	// 매개 변수 start와 end는 vObject의 인덱스 값으로 한다.

	// 시작 값이 끝 값보다 크거나 같을 경우 정렬이 완료된 것으로 한다.
	if (start >= end) {
		return;
	}

	int pivot = start;			// 기준점
	int lStart = pivot + 1;		// 왼쪽 시작 지점
	int rStart = end;			// 오른쪽 시작 지점
	GameObject* temp;			// 교체를 위한 임시 변수

	while (lStart <= rStart) {

		// 왼쪽 시작 지점 지정 (시작 지점 비교시 Object의 LONG형 변수인 ID 값으로 한다)
		while (lStart <= end &&
			(vObject[type][lStart]->GetId().x <= vObject[type][pivot]->GetId().x ||
				vObject[type][lStart]->GetId().y <= vObject[type][pivot]->GetId().y))
		{
			lStart++;
		}

		// 오른쪽 시작 지점 지정 (시작 지점 비교시 Object의 LONG형 변수인 ID 값으로 한다)
		while (rStart > start &&
			(vObject[type][rStart]->GetId().x >= vObject[type][pivot]->GetId().x ||
				vObject[type][rStart]->GetId().y >= vObject[type][pivot]->GetId().y))
		{
			rStart--;
		}

		if (lStart > rStart) {
			temp = vObject[type][rStart];
			vObject[type][rStart] = vObject[type][pivot];
			vObject[type][pivot] = temp;
		}
		else {
			temp = vObject[type][lStart];
			vObject[type][lStart] = vObject[type][pivot];
			vObject[type][pivot] = temp;
		}
	}

	// 왼쪽과 오른쪽을 재귀함수를 통해 확인 정렬 한다.
	SortObject(type, start, rStart - 1);
	SortObject(type, rStart + 1, end);
		
}

void ObjectManager::SetEditMode(bool isEdit)
{
	for (UINT y = 0; y < vObject.size(); y++)
	{
		for (UINT x = 0; x < vObject[y].size(); x++)
		{
			vObject[y][x]->SetIsEdit(isEdit);
		}
	}
}


Player * ObjectManager::GetPlayer()
{
	for (UINT x = 0; x < vObject[ACTOR].size(); x++)
	{
		if (dynamic_cast<Actor*>(vObject[ACTOR][x])->GetActorKind() == PLAYER) {
			return dynamic_cast<Player*>(vObject[ACTOR][x]);
		}
	}
	return nullptr;
}
