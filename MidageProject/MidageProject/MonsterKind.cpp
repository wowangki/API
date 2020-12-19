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
			name = "ü��";
			break;
		case MON_WATER:
			sTemp = "Bat_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ó��";
			break;
		case MON_FIRE:
			sTemp = "Bat_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "���";
			break;
		case MON_WIND:
			sTemp = "Bat_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����";
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
			name = "���츣";
			break;
		case MON_WATER:
			sTemp = "Bear_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����";
			break;
		case MON_FIRE:
			sTemp = "Bear_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����";
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
			name = "�渱";
			break;
		case MON_WATER:
			sTemp = "Mystic_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����";
			break;
		case MON_FIRE:
			sTemp = "Mystic_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "��Ƽ";
			break;
		case MON_WIND:
			sTemp = "Mystic_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�Ը�";
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
			name = "�����";
			break;
		case MON_WATER:
			sTemp = "Whale_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�����";
			break;
		case MON_FIRE:
			sTemp = "Whale_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ȭ���";
			break;
		case MON_WIND:
			sTemp = "Whale_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ǳ���";
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
			name = "���η�";
			break;
		case MON_WATER:
			sTemp = "AquaDemon_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "���η�";
			break;
		case MON_FIRE:
			sTemp = "AquaDemon_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ȭ�η�";
			break;
		case MON_WIND:
			sTemp = "AquaDemon_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "Ǫ�η�";
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
			name = "������";
			break;
		case MON_WATER:
			sTemp = "Gargoyle_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "������";
			break;
		case MON_FIRE:
			sTemp = "Gargoyle_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�ϰ���";
			break;
		case MON_WIND:
			sTemp = "Gargoyle_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "������";
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
			name = "������";
			break;
		case MON_WATER:
			sTemp = "Serpent_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "���̻��";
			break;
		case MON_FIRE:
			sTemp = "Serpent_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ȣ����";
			break;
		case MON_WIND:
			sTemp = "Serpent_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ī�����";
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
			name = "�����ܵ�";
			break;
		case MON_WATER:
			sTemp = "Succubus_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�����";
			break;
		case MON_FIRE:
			sTemp = "Succubus_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "���";
			break;
		case MON_WIND:
			sTemp = "Succubus_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�����̾�";
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
			name = "�̵���";
			break;
		case MON_WATER:
			sTemp = "Dragon_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�ƿ���";
			break;
		case MON_FIRE:
			sTemp = "Dragon_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "��ī��";
			break;
		case MON_WIND:
			sTemp = "Dragon_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "��ΰ�";
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
			name = "������";
			break;
		case MON_WATER:
			sTemp = "GreatWyrm_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "������";
			break;
		case MON_FIRE:
			sTemp = "GreatWyrm_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�÷���";
			break;
		case MON_WIND:
			sTemp = "GreatWyrm_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����";
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
			name = "�۽ù�";
			break;
		case MON_WATER:
			sTemp = "DarkKnight_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "Ʈ����ź";
			break;
		case MON_FIRE:
			sTemp = "DarkKnight_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "������";
			break;
		case MON_WIND:
			sTemp = "DarkKnight_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "������";
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
			name = "���ο�";
			break;
		case MON_WATER:
			sTemp = "Hobit_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "���ο�";
			break;
		case MON_FIRE:
			sTemp = "Hobit_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ȣ�ο�";
			break;
		case MON_WIND:
			sTemp = "Hobit_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "ī�ο�";
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
			name = "�ٸ�ĭ";
			break;
		case MON_WATER:
			sTemp = "Kitcat_Water";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����ĭ";
			break;
		case MON_FIRE:
			sTemp = "Kitcat_Fire";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "�ϸ�ĭ";
			break;
		case MON_WIND:
			sTemp = "Kitcat_Wind";
			CreateMImg(sTemp);
			imgKey = FindMImg();
			name = "����ĭ";
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
