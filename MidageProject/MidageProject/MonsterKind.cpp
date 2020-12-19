#include "stdafx.h"
#include "Monster.h"
#include "SearchObject.h"

void Monster::SetName(int type)
{
	motion = ACTOR_IDLE;
	string sTemp;
	switch (type) {
	case MON_BAT:
		searchSize = 7;
		delayTime = 230.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Bat_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "체드";
			break;
		case MON_WATER:
			sTemp = "Bat_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "처드";
			break;
		case MON_FIRE:
			sTemp = "Bat_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "허드";
			break;
		case MON_WIND:
			sTemp = "Bat_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "람드";
			break;
		}
		break;
	case MON_BEAR:
		searchSize = 11;
		delayTime = 270.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Bear_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "지우르";
			break;
		case MON_WATER:
			sTemp = "Bear_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "수르";
			break;
		case MON_FIRE:
			sTemp = "Bear_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "여르";
			break;
		case MON_WIND:
			break;
		}
		break;
	case MON_MYSTIC:
		searchSize = 17;
		delayTime = 230.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Mystic_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "펜릴";
			break;
		case MON_WATER:
			sTemp = "Mystic_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "스콜";
			break;
		case MON_FIRE:
			sTemp = "Mystic_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "하티";
			break;
		case MON_WIND:
			sTemp = "Mystic_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "게리";
			break;
		}
		break;
	case MON_WHALE:
		searchSize = 11;
		delayTime = 300.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Whale_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "지고양";
			break;
		case MON_WATER:
			sTemp = "Whale_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "수고양";
			break;
		case MON_FIRE:
			sTemp = "Whale_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "화고양";
			break;
		case MON_WIND:
			sTemp = "Whale_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "풍고양";
			break;
		}
		break;
	case MON_AQUADEMON:
		searchSize = 15;
		delayTime = 270.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "AquaDemon_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "지로로";
			break;
		case MON_WATER:
			sTemp = "AquaDemon_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "수로로";
			break;
		case MON_FIRE:
			sTemp = "AquaDemon_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "화로로";
			break;
		case MON_WIND:
			sTemp = "AquaDemon_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "푸로로";
			break;
		}
		break;
	case MON_GARGOYLE:
		searchSize = 17;
		delayTime = 260.0f;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Gargoyle_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "가고일";
			break;
		case MON_WATER:
			sTemp = "Gargoyle_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "스고일";
			break;
		case MON_FIRE:
			sTemp = "Gargoyle_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "하고일";
			break;
		case MON_WIND:
			sTemp = "Gargoyle_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "누고일";
			break;
		}
		break;
	case MON_SERPENT:
		delayTime = 300.0f;
		searchSize = 9;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Serpent_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "도우사메";
			break;
		case MON_WATER:
			sTemp = "Serpent_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "수이사메";
			break;
		case MON_FIRE:
			sTemp = "Serpent_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "호노사메";
			break;
		case MON_WIND:
			sTemp = "Serpent_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "카지사메";
			break;
		}
		break;
	case MON_SUCCUBUS:
		delayTime = 220.0f;
		searchSize = 15;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Succubus_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "베르단디";
			break;
		case MON_WATER:
			sTemp = "Succubus_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "스쿨드";
			break;
		case MON_FIRE:
			sTemp = "Succubus_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "울드";
			break;
		case MON_WIND:
			sTemp = "Succubus_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "프레이야";
			break;
		}
		break;
	case MON_DRAGON:
		delayTime = 260.0f;
		searchSize = 21;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Dragon_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "미도곤";
			break;
		case MON_WATER:
			sTemp = "Dragon_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "아오곤";
			break;
		case MON_FIRE:
			sTemp = "Dragon_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "아카곤";
			break;
		case MON_WIND:
			sTemp = "Dragon_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "기로곤";
			break;
		}
		break;
	case MON_WYRM:
		delayTime = 270.0f;
		searchSize = 17;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "GreatWyrm_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "가르웜";
			break;
		case MON_WATER:
			sTemp = "GreatWyrm_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "오스웜";
			break;
		case MON_FIRE:
			sTemp = "GreatWyrm_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "플러웜";
			break;
		case MON_WIND:
			sTemp = "GreatWyrm_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "블러웜";
			break;
		}
		break;
	case MON_KNIGHT:
		delayTime = 280.0f;
		searchSize = 15;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "DarkKnight_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "퍼시발";
			break;
		case MON_WATER:
			sTemp = "DarkKnight_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "트리스탄";
			break;
		case MON_FIRE:
			sTemp = "DarkKnight_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "가웨인";
			break;
		case MON_WIND:
			sTemp = "DarkKnight_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "가레스";
			break;
		}
		break;
	case MON_HOBIT:
		delayTime = 250.0f;
		searchSize = 11;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Hobit_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "지로움";
			break;
		case MON_WATER:
			sTemp = "Hobit_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "수로움";
			break;
		case MON_FIRE:
			sTemp = "Hobit_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "호로움";
			break;
		case MON_WIND:
			sTemp = "Hobit_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "카로움";
			break;
		}
		break;
	case MON_KITCAT:
		delayTime = 240.0f;
		searchSize = 13;
		switch (monProperties) {
		case MON_EARTH:
			sTemp = "Kitcat_Earth";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "바르칸";
			break;
		case MON_WATER:
			sTemp = "Kitcat_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "샤르칸";
			break;
		case MON_FIRE:
			sTemp = "Kitcat_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "하르칸";
			break;
		case MON_WIND:
			sTemp = "Kitcat_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "프로칸";
			break;
		}
		break;
	}

	initDelayTime = delayTime;
}

void Monster::ChangeImage(void)
{
	imgKey = FindMImg();
	SetImg(imgKey);
}

void Monster::CreateMImg(string name)
{
	string tTemp[ACTOR_GUARD + 1] = { "_IDLE", "_MOVE", "_ATTACK", "_DAMAGE", "_GUARD" };

	for (int i = 0; i <= ACTOR_GUARD; i++)
	{
		string temp = name;
		temp.append(tTemp[i]);

		mImgKey.insert(make_pair(i, temp));
	}
}

string Monster::FindMImg(void)
{
	for (_mIter mIter = mImgKey.begin(); mIter != mImgKey.end(); mIter++)
	{
		if (motion == mIter->first) {
			return mIter->second;
		}
	}

	return nullptr;
}
