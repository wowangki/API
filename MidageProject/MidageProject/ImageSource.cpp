#include "stdafx.h"
#include "ImageSource.h"


ImageSource::ImageSource()
{
}

ImageSource::~ImageSource()
{
}

HRESULT ImageSource::CreateTitleImage(void)
{
	_IMAGE->CreateFrameImage("TitleBackGround", FileSource("Image", "Title", "TitleBackground.png"), 1, 1);
	_IMAGE->CreateFrameImage("TitleName", FileSource("Image", "Title", "TitleName.png"), 1, 1);
	_IMAGE->CreateFrameImage("TitleNewGame", FileSource("Image", "Title", "TitleNewGame.png"), 1, 2);
	_IMAGE->CreateFrameImage("TitleEditGame", FileSource("Image", "Title", "TitleEditGame.png"), 1, 2);
	_IMAGE->CreateFrameImage("TitleOption", FileSource("Image", "Title", "TitleOption.png"), 1, 2);
	_IMAGE->CreateFrameImage("TitleSelect", FileSource("Image", "Title", "TitleSelectArrow.png"), 1, 1);
	return S_OK;
}

HRESULT ImageSource::CreateTileImage(void)
{
	// Tile Image
	_IMAGE->CreateFrameImage("Tile_Autumn", FileSource("Image", "Tile", "Tile_Autumn.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Desert", FileSource("Image", "Tile", "Tile_Desert.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Lava", FileSource("Image", "Tile", "Tile_Lava.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Rocky", FileSource("Image", "Tile", "Tile_Rocky.png"), 5, 1);
	//_IMAGE->CreateFrameImage("Tile_Rocky_Winter", FileSource("Image", "Tile", "Tile_Rocky_Winter.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Spring", FileSource("Image", "Tile", "Tile_Spring.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Summer", FileSource("Image", "Tile", "Tile_Summer.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Winter", FileSource("Image", "Tile", "Tile_Winter.png"), 5, 1);
	_IMAGE->CreateFrameImage("Tile_Liqude", FileSource("Image", "Tile", "Tile_Water_Lava.png"), 2, 2);
	_IMAGE->CreateFrameImage("Enterance", FileSource("Image", "Tile", "Enterance.png"), 1, 1);
	return S_OK;
}

HRESULT ImageSource::CreateMatterImage(void)
{
	//Matter Image
	_IMAGE->CreateFrameImage("Matter_Tree", FileSource("Image", "Matter", "Matter_Tree.png"), 4, 1);

	return S_OK;
}

HRESULT ImageSource::CreateItemImage(void)
{
	//Item Image
	//Equip
	//Axe
	_IMAGE->CreateFrameImage("LongAxe", FileSource("Image", "Item/Axe", "LongAxe.png"), 1, 4);
	_IMAGE->CreateFrameImage("Scythe", FileSource("Image", "Item/Axe", "Scythe.png"), 1, 4);
	_IMAGE->CreateFrameImage("ShortAxe", FileSource("Image", "Item/Axe", "ShortAxe.png"), 1, 4);
	//Sword
	_IMAGE->CreateFrameImage("BastardSword", FileSource("Image", "Item/Sword", "BastardSword.png"), 1, 4);
	_IMAGE->CreateFrameImage("LongSword", FileSource("Image", "Item/Sword", "LongSword.png"), 1, 4);
	_IMAGE->CreateFrameImage("OneHandSword", FileSource("Image", "Item/Sword", "OneHandSword.png"), 1, 4);
	//Defence
	_IMAGE->CreateFrameImage("Body", FileSource("Image", "Item/Body", "Body.png"), 2, 1);
	_IMAGE->CreateFrameImage("Foot", FileSource("Image", "Item/Foot", "Foot.png"), 2, 1);
	_IMAGE->CreateFrameImage("Head", FileSource("Image", "Item/Head", "Head.png"), 2, 1);
	//Material
	//Blood
	_IMAGE->CreateFrameImage("Blood", FileSource("Image", "Item/Material/Blood", "Blood.png"), 4, 1);
	//Cloth
	_IMAGE->CreateFrameImage("Beard", FileSource("Image", "Item/Material/Cloth", "Beard.png"), 4, 1);
	_IMAGE->CreateFrameImage("Cloth", FileSource("Image", "Item/Material/Cloth", "Cloth.png"), 4, 1);
	_IMAGE->CreateFrameImage("Contract", FileSource("Image", "Item/Material/Cloth", "Contract.png"), 4, 1);
	_IMAGE->CreateFrameImage("Promissory", FileSource("Image", "Item/Material/Cloth", "Promissory.png"), 4, 1);
	//Eye
	_IMAGE->CreateFrameImage("Eye", FileSource("Image", "Item/Material/Eye", "Eye.png"), 4, 1);
	//Ladder
	_IMAGE->CreateFrameImage("Fin", FileSource("Image", "Item/Material/Ladder", "Fin.png"), 4, 1);
	_IMAGE->CreateFrameImage("Fur", FileSource("Image", "Item/Material/Ladder", "Fur.png"), 4, 1);
	_IMAGE->CreateFrameImage("Ladder", FileSource("Image", "Item/Material/Ladder", "Ladder.png"), 4, 1);
	_IMAGE->CreateFrameImage("ReverseScale", FileSource("Image", "Item/Material/Ladder", "ReverseScale.png"), 4, 1);
	_IMAGE->CreateFrameImage("Scale", FileSource("Image", "Item/Material/Ladder", "Scale.png"), 4, 1);
	_IMAGE->CreateFrameImage("Wing", FileSource("Image", "Item/Material/Ladder", "Wing.png"), 4, 1);
	//Plant
	_IMAGE->CreateFrameImage("Flower", FileSource("Image", "Item/Material/Plant", "Flower.png"), 4, 1);
	_IMAGE->CreateFrameImage("Cane", FileSource("Image", "Item/Material/Plant", "Cane.png"), 4, 1);
	_IMAGE->CreateFrameImage("FlowerPowder", FileSource("Image", "Item/Material/Plant", "FlowerPowder.png"), 4, 1);
	_IMAGE->CreateFrameImage("Leaf", FileSource("Image", "Item/Material/Plant", "Leaf.png"), 4, 1);
	//Stone
	_IMAGE->CreateFrameImage("DragonStone", FileSource("Image", "Item/Material/Stone", "DragonStone.png"), 1, 1);
	_IMAGE->CreateFrameImage("Stone", FileSource("Image", "Item/Material/Stone", "Stone.png"), 4, 4);
	//Tooth
	_IMAGE->CreateFrameImage("Claw", FileSource("Image", "Item/Material/Tooth", "Claw.png"), 4, 1);
	_IMAGE->CreateFrameImage("Tooth", FileSource("Image", "Item/Material/Tooth", "Tooth.png"), 4, 1);

	return S_OK;
}

HRESULT ImageSource::CreatePlayerImage(void)
{
	//Player Image
	_IMAGE->CreateFrameImage("Laharl_IDLE", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Laharl_MOVE", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_MOVE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Laharl_GUARD", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_GUARD.png"), 4, 2);
	_IMAGE->CreateFrameImage("Laharl_DAMAGE", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_DAMAGE.png"), 3, 2);
	_IMAGE->CreateFrameImage("Laharl_ATTACK_NORMAL", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_ATTACK_NORMAL.png"), 7, 2);
	_IMAGE->CreateFrameImage("Laharl_ATTACK_SWORD_AXE", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_ATTACK_SWORD_AXE.png"), 8, 2);
	_IMAGE->CreateFrameImage("Laharl_ATTACK_SPEAR", FileSource("Image", "Actor/Player/Male/Laharl", "Laharl_ATTACK_SPEAR.png"), 7, 2);

	_IMAGE->CreateFrameImage("Flonne_IDLE", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_IDLE.png"), 7, 2);
	_IMAGE->CreateFrameImage("Flonne_MOVE", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_MOVE.png"), 7, 2);
	_IMAGE->CreateFrameImage("Flonne_GUARD", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_GUARD.png"), 4, 2);
	_IMAGE->CreateFrameImage("Flonne_DAMAGE", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_DAMAGE.png"), 3, 2);
	_IMAGE->CreateFrameImage("Flonne_ATTACK_NORMAL", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_ATTACK_NORMAL.png"), 7, 2);
	_IMAGE->CreateFrameImage("Flonne_ATTACK_SWORD_AXE", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_ATTACK_SWORD_AXE.png"), 8, 2);
	_IMAGE->CreateFrameImage("Flonne_ATTACK_SPEAR", FileSource("Image", "Actor/Player/Female/Flonne", "Flonne_ATTACK_SPEAR.png"), 7, 2);


	return S_OK;
}

HRESULT ImageSource::CreateMonsterImage(void)
{
	//Monster Image
	//Bat
	_IMAGE->CreateFrameImage("Bat_Earth_IDLE", FileSource("Image", "Actor/Monster/Beast/Bat/Earth", "Earth_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Earth_MOVE", FileSource("Image", "Actor/Monster/Beast/Bat/Earth", "Earth_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Earth_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bat/Earth", "Earth_ATTACK.png"), 6, 1);
	_IMAGE->CreateFrameImage("Bat_Earth_GUARD", FileSource("Image", "Actor/Monster/Beast/Bat/Earth", "Earth_GUARD.png"), 3, 1);
	_IMAGE->CreateFrameImage("Bat_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bat/Earth", "Earth_DAMAGE.png"), 1, 1);
	
	_IMAGE->CreateFrameImage("Bat_Fire_IDLE", FileSource("Image", "Actor/Monster/Beast/Bat/Fire", "Fire_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Fire_MOVE", FileSource("Image", "Actor/Monster/Beast/Bat/Fire", "Fire_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Fire_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bat/Fire", "Fire_ATTACK.png"), 6, 1);
	_IMAGE->CreateFrameImage("Bat_Fire_GUARD", FileSource("Image", "Actor/Monster/Beast/Bat/Fire", "Fire_GUARD.png"), 3, 1);
	_IMAGE->CreateFrameImage("Bat_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bat/Fire", "Fire_DAMAGE.png"), 1, 1);
	
	_IMAGE->CreateFrameImage("Bat_Water_IDLE", FileSource("Image", "Actor/Monster/Beast/Bat/Water", "Water_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Water_MOVE", FileSource("Image", "Actor/Monster/Beast/Bat/Water", "Water_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Water_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bat/Water", "Water_ATTACK.png"), 6, 1);
	_IMAGE->CreateFrameImage("Bat_Water_GUARD", FileSource("Image", "Actor/Monster/Beast/Bat/Water", "Water_GUARD.png"), 3, 1);
	_IMAGE->CreateFrameImage("Bat_Water_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bat/Water", "Water_DAMAGE.png"), 1, 1);
	
	_IMAGE->CreateFrameImage("Bat_Wind_IDLE", FileSource("Image", "Actor/Monster/Beast/Bat/Wind", "Wind_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Wind_MOVE", FileSource("Image", "Actor/Monster/Beast/Bat/Wind", "Wind_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Bat_Wind_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bat/Wind", "Wind_ATTACK.png"), 6, 1);
	_IMAGE->CreateFrameImage("Bat_Wind_GUARD", FileSource("Image", "Actor/Monster/Beast/Bat/Wind", "Wind_GUARD.png"), 3, 1);
	_IMAGE->CreateFrameImage("Bat_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bat/Wind", "Wind_DAMAGE.png"), 1, 1);

	//Bear
	_IMAGE->CreateFrameImage("Bear_Earth_IDLE", FileSource("Image", "Actor/Monster/Beast/Bear/Earth", "Earth_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Bear_Earth_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bear/Earth", "Earth_ATTACK.png"), 10, 1);
	_IMAGE->CreateFrameImage("Bear_Earth_GUARD", FileSource("Image", "Actor/Monster/Beast/Bear/Earth", "Earth_GUARD.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bear/Earth", "Earth_DAMAGE.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Earth_MOVE", FileSource("Image", "Actor/Monster/Beast/Bear/Earth", "Earth_MOVE.png"), 4, 2);
	
	_IMAGE->CreateFrameImage("Bear_Fire_IDLE", FileSource("Image", "Actor/Monster/Beast/Bear/Fire", "Fire_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Bear_Fire_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bear/Fire", "Fire_ATTACK.png"), 10, 1);
	_IMAGE->CreateFrameImage("Bear_Fire_GUARD", FileSource("Image", "Actor/Monster/Beast/Bear/Fire", "Fire_GUARD.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bear/Fire", "Fire_DAMAGE.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Fire_MOVE", FileSource("Image", "Actor/Monster/Beast/Bear/Fire", "Fire_MOVE.png"), 4, 2);
	
	_IMAGE->CreateFrameImage("Bear_Water_IDLE", FileSource("Image", "Actor/Monster/Beast/Bear/Water", "Water_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Bear_Water_ATTACK", FileSource("Image", "Actor/Monster/Beast/Bear/Water", "Water_ATTACK.png"), 10, 1);
	_IMAGE->CreateFrameImage("Bear_Water_GUARD", FileSource("Image", "Actor/Monster/Beast/Bear/Water", "Water_GUARD.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Water_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Bear/Water", "Water_DAMAGE.png"), 5, 1);
	_IMAGE->CreateFrameImage("Bear_Water_MOVE", FileSource("Image", "Actor/Monster/Beast/Bear/Water", "Water_MOVE.png"), 4, 2);

	//Mystic Beast
	_IMAGE->CreateFrameImage("Mystic_Earth_IDLE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Earth", "Earth_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Earth_ATTACK", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Earth", "Earth_ATTACK.png"), 7, 2);
	_IMAGE->CreateFrameImage("Mystic_Earth_GUARD", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Earth_MOVE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Earth", "Earth_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Mystic_Fire_IDLE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Fire", "Fire_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Fire_ATTACK", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Fire", "Fire_ATTACK.png"), 7, 2);
	_IMAGE->CreateFrameImage("Mystic_Fire_GUARD", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Fire_MOVE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Fire", "Fire_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Mystic_Water_IDLE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Water", "Water_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Water_ATTACK", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Water", "Water_ATTACK.png"), 7, 2);
	_IMAGE->CreateFrameImage("Mystic_Water_GUARD", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Water_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Water_MOVE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Water", "Water_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Mystic_Wind_IDLE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Wind", "Wind_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Wind_ATTACK", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Wind", "Wind_ATTACK.png"), 7, 2);
	_IMAGE->CreateFrameImage("Mystic_Wind_GUARD", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Mystic_Wind_MOVE", FileSource("Image", "Actor/Monster/Beast/Mystic Beast/Wind", "Wind_MOVE.png"), 6, 2);

	//Whale
	_IMAGE->CreateFrameImage("Whale_Earth_IDLE", FileSource("Image", "Actor/Monster/Beast/Whale/Earth", "Earth_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Whale_Earth_ATTACK", FileSource("Image", "Actor/Monster/Beast/Whale/Earth", "Earth_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Whale_Earth_GUARD", FileSource("Image", "Actor/Monster/Beast/Whale/Earth", "Earth_GUARD.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Whale/Earth", "Earth_DAMAGE.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Earth_MOVE", FileSource("Image", "Actor/Monster/Beast/Whale/Earth", "Earth_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Whale_Fire_IDLE", FileSource("Image", "Actor/Monster/Beast/Whale/Fire", "Fire_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Whale_Fire_ATTACK", FileSource("Image", "Actor/Monster/Beast/Whale/Fire", "Fire_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Whale_Fire_GUARD", FileSource("Image", "Actor/Monster/Beast/Whale/Fire", "Fire_GUARD.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Whale/Fire", "Fire_DAMAGE.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Fire_MOVE", FileSource("Image", "Actor/Monster/Beast/Whale/Fire", "Fire_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Whale_Water_IDLE", FileSource("Image", "Actor/Monster/Beast/Whale/Water", "Water_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Whale_Water_ATTACK", FileSource("Image", "Actor/Monster/Beast/Whale/Water", "Water_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Whale_Water_GUARD", FileSource("Image", "Actor/Monster/Beast/Whale/Water", "Water_GUARD.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Water_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Whale/Water", "Water_DAMAGE.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Water_MOVE", FileSource("Image", "Actor/Monster/Beast/Whale/Water", "Water_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Whale_Wind_IDLE", FileSource("Image", "Actor/Monster/Beast/Whale/Wind", "Wind_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Whale_Wind_ATTACK", FileSource("Image", "Actor/Monster/Beast/Whale/Wind", "Wind_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Whale_Wind_GUARD", FileSource("Image", "Actor/Monster/Beast/Whale/Wind", "Wind_GUARD.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Beast/Whale/Wind", "Wind_DAMAGE.png"), 4, 1);
	_IMAGE->CreateFrameImage("Whale_Wind_MOVE", FileSource("Image", "Actor/Monster/Beast/Whale/Wind", "Wind_MOVE.png"), 6, 2);

	//AquaDemon
	_IMAGE->CreateFrameImage("AquaDemon_Earth_IDLE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Earth", "Earth_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Earth_ATTACK", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Earth", "Earth_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Earth_GUARD", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Earth", "Earth_GUARD.png"), 5, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Earth_MOVE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Earth", "Earth_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("AquaDemon_Fire_IDLE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Fire", "Fire_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Fire_ATTACK", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Fire", "Fire_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Fire_GUARD", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Fire", "Fire_GUARD.png"), 5, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Fire_MOVE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Fire", "Fire_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("AquaDemon_Water_IDLE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Water", "Water_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Water_ATTACK", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Water", "Water_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Water_GUARD", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Water", "Water_GUARD.png"), 5, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Water_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Water_MOVE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Water", "Water_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("AquaDemon_Wind_IDLE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Wind", "Wind_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Wind_ATTACK", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Wind", "Wind_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Wind_GUARD", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Wind", "Wind_GUARD.png"), 5, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("AquaDemon_Wind_MOVE", FileSource("Image", "Actor/Monster/Demon/Aqua Demon/Wind", "Wind_MOVE.png"), 5, 2);

	//Gargoyle
	_IMAGE->CreateFrameImage("Gargoyle_Earth_IDLE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Earth", "Earth_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Gargoyle_Earth_ATTACK", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Earth", "Earth_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Earth_GUARD", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Earth", "Earth_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Earth", "Earth_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Earth_MOVE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Earth", "Earth_MOVE.png"), 7, 2);
	
	_IMAGE->CreateFrameImage("Gargoyle_Fire_IDLE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Fire", "Fire_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Gargoyle_Fire_ATTACK", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Fire", "Fire_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Fire_GUARD", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Fire", "Fire_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Fire", "Fire_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Fire_MOVE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Fire", "Fire_MOVE.png"), 7, 2);
	
	_IMAGE->CreateFrameImage("Gargoyle_Water_IDLE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Water", "Water_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Gargoyle_Water_ATTACK", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Water", "Water_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Water_GUARD", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Water", "Water_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Water_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Water", "Water_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Water_MOVE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Water", "Water_MOVE.png"), 7, 2);
	
	_IMAGE->CreateFrameImage("Gargoyle_Wind_IDLE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Wind", "Wind_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("Gargoyle_Wind_ATTACK", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Wind", "Wind_ATTACK.png"), 8, 2);
	_IMAGE->CreateFrameImage("Gargoyle_Wind_GUARD", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Wind", "Wind_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Wind", "Wind_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Gargoyle_Wind_MOVE", FileSource("Image", "Actor/Monster/Demon/Gargoyle/Wind", "Wind_MOVE.png"), 7, 2);

	//Serpent
	_IMAGE->CreateFrameImage("Serpent_Earth_IDLE", FileSource("Image", "Actor/Monster/Demon/Serpent/Earth", "Earth_IDLE.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Earth_ATTACK", FileSource("Image", "Actor/Monster/Demon/Serpent/Earth", "Earth_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Earth_GUARD", FileSource("Image", "Actor/Monster/Demon/Serpent/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Serpent/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Earth_MOVE", FileSource("Image", "Actor/Monster/Demon/Serpent/Earth", "Earth_MOVE.png"), 4, 2);
	
	_IMAGE->CreateFrameImage("Serpent_Fire_IDLE", FileSource("Image", "Actor/Monster/Demon/Serpent/Fire", "Fire_IDLE.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Fire_ATTACK", FileSource("Image", "Actor/Monster/Demon/Serpent/Fire", "Fire_ATTACK.png"), 4, 1);
	_IMAGE->CreateFrameImage("Serpent_Fire_GUARD", FileSource("Image", "Actor/Monster/Demon/Serpent/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Serpent/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Fire_MOVE", FileSource("Image", "Actor/Monster/Demon/Serpent/Fire", "Fire_MOVE.png"), 4, 2);
	
	_IMAGE->CreateFrameImage("Serpent_Water_IDLE", FileSource("Image", "Actor/Monster/Demon/Serpent/Water", "Water_IDLE.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Water_ATTACK", FileSource("Image", "Actor/Monster/Demon/Serpent/Water", "Water_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Water_GUARD", FileSource("Image", "Actor/Monster/Demon/Serpent/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Water_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Serpent/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Water_MOVE", FileSource("Image", "Actor/Monster/Demon/Serpent/Water", "Water_MOVE.png"), 4, 2);
	
	_IMAGE->CreateFrameImage("Serpent_Wind_IDLE", FileSource("Image", "Actor/Monster/Demon/Serpent/Wind", "Wind_IDLE.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Wind_ATTACK", FileSource("Image", "Actor/Monster/Demon/Serpent/Wind", "Wind_ATTACK.png"), 4, 2);
	_IMAGE->CreateFrameImage("Serpent_Wind_GUARD", FileSource("Image", "Actor/Monster/Demon/Serpent/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Serpent/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Serpent_Wind_MOVE", FileSource("Image", "Actor/Monster/Demon/Serpent/Wind", "Wind_MOVE.png"), 4, 2);

	//Succubus
	_IMAGE->CreateFrameImage("Succubus_Earth_IDLE", FileSource("Image", "Actor/Monster/Demon/Succubus/Earth", "Earth_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Succubus_Earth_ATTACK", FileSource("Image", "Actor/Monster/Demon/Succubus/Earth", "Earth_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Succubus_Earth_GUARD", FileSource("Image", "Actor/Monster/Demon/Succubus/Earth", "Earth_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Succubus/Earth", "Earth_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Earth_MOVE", FileSource("Image", "Actor/Monster/Demon/Succubus/Earth", "Earth_MOVE.png"), 5, 1);
	
	_IMAGE->CreateFrameImage("Succubus_Fire_IDLE", FileSource("Image", "Actor/Monster/Demon/Succubus/Fire", "Fire_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Succubus_Fire_ATTACK", FileSource("Image", "Actor/Monster/Demon/Succubus/Fire", "Fire_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Succubus_Fire_GUARD", FileSource("Image", "Actor/Monster/Demon/Succubus/Fire", "Fire_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Succubus/Fire", "Fire_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Fire_MOVE", FileSource("Image", "Actor/Monster/Demon/Succubus/Fire", "Fire_MOVE.png"), 5, 1);
	
	_IMAGE->CreateFrameImage("Succubus_Water_IDLE", FileSource("Image", "Actor/Monster/Demon/Succubus/Water", "Water_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Succubus_Water_ATTACK", FileSource("Image", "Actor/Monster/Demon/Succubus/Water", "Water_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Succubus_Water_GUARD", FileSource("Image", "Actor/Monster/Demon/Succubus/Water", "Water_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Water_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Succubus/Water", "Water_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Water_MOVE", FileSource("Image", "Actor/Monster/Demon/Succubus/Water", "Water_MOVE.png"), 5, 1);
	
	_IMAGE->CreateFrameImage("Succubus_Wind_IDLE", FileSource("Image", "Actor/Monster/Demon/Succubus/Wind", "Wind_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Succubus_Wind_ATTACK", FileSource("Image", "Actor/Monster/Demon/Succubus/Wind", "Wind_ATTACK.png"), 8, 1);
	_IMAGE->CreateFrameImage("Succubus_Wind_GUARD", FileSource("Image", "Actor/Monster/Demon/Succubus/Wind", "Wind_GUARD.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Demon/Succubus/Wind", "Wind_DAMAGE.png"), 1, 1);
	_IMAGE->CreateFrameImage("Succubus_Wind_MOVE", FileSource("Image", "Actor/Monster/Demon/Succubus/Wind", "Wind_MOVE.png"), 5, 1);

	//Dragon
	_IMAGE->CreateFrameImage("Dragon_Earth_IDLE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Earth", "Earth_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Dragon_Earth_ATTACK", FileSource("Image", "Actor/Monster/Dragon/Dragon/Earth", "Earth_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Dragon_Earth_GUARD", FileSource("Image", "Actor/Monster/Dragon/Dragon/Earth", "Earth_GUARD.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Earth", "Earth_DAMAGE.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Earth_MOVE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Earth", "Earth_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Dragon_Fire_IDLE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Fire", "Fire_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Dragon_Fire_ATTACK", FileSource("Image", "Actor/Monster/Dragon/Dragon/Fire", "Fire_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Dragon_Fire_GUARD", FileSource("Image", "Actor/Monster/Dragon/Dragon/Fire", "Fire_GUARD.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Fire", "Fire_DAMAGE.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Fire_MOVE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Fire", "Fire_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Dragon_Water_IDLE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Water", "Water_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Dragon_Water_ATTACK", FileSource("Image", "Actor/Monster/Dragon/Dragon/Water", "Water_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Dragon_Water_GUARD", FileSource("Image", "Actor/Monster/Dragon/Dragon/Water", "Water_GUARD.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Water_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Water", "Water_DAMAGE.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Water_MOVE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Water", "Water_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Dragon_Wind_IDLE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Wind", "Wind_IDLE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Dragon_Wind_ATTACK", FileSource("Image", "Actor/Monster/Dragon/Dragon/Wind", "Wind_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Dragon_Wind_GUARD", FileSource("Image", "Actor/Monster/Dragon/Dragon/Wind", "Wind_GUARD.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Wind", "Wind_DAMAGE.png"), 2, 2);
	_IMAGE->CreateFrameImage("Dragon_Wind_MOVE", FileSource("Image", "Actor/Monster/Dragon/Dragon/Wind", "Wind_MOVE.png"), 6, 2);

	//GreatWyrm
	_IMAGE->CreateFrameImage("GreatWyrm_Earth_IDLE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Earth", "Earth_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Earth_ATTACK", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Earth", "Earth_ATTACK.png"), 3, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Earth_GUARD", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Earth_MOVE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Earth", "Earth_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("GreatWyrm_Fire_IDLE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Fire", "Fire_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Fire_ATTACK", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Fire", "Fire_ATTACK.png"), 3, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Fire_GUARD", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Fire_MOVE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Fire", "Fire_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("GreatWyrm_Water_IDLE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Water", "Water_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Water_ATTACK", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Water", "Water_ATTACK.png"), 3, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Water_GUARD", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Water_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Water_MOVE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Water", "Water_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("GreatWyrm_Wind_IDLE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Wind", "Wind_IDLE.png"), 6, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Wind_ATTACK", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Wind", "Wind_ATTACK.png"), 3, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Wind_GUARD", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("GreatWyrm_Wind_MOVE", FileSource("Image", "Actor/Monster/Dragon/GreatWyrm/Wind", "Wind_MOVE.png"), 2, 2);

	//Dark Knight
	_IMAGE->CreateFrameImage("DarkKnight_Earth_IDLE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Earth", "Earth_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Earth_ATTACK", FileSource("Image", "Actor/Monster/Human/Dark Knight/Earth", "Earth_ATTACK.png"), 12, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Earth_GUARD", FileSource("Image", "Actor/Monster/Human/Dark Knight/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Earth_MOVE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Earth", "Earth_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("DarkKnight_Fire_IDLE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Fire", "Fire_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Fire_ATTACK", FileSource("Image", "Actor/Monster/Human/Dark Knight/Fire", "Fire_ATTACK.png"), 12, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Fire_GUARD", FileSource("Image", "Actor/Monster/Human/Dark Knight/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Fire_MOVE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Fire", "Fire_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("DarkKnight_Water_IDLE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Water", "Water_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Water_ATTACK", FileSource("Image", "Actor/Monster/Human/Dark Knight/Water", "Water_ATTACK.png"), 12, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Water_GUARD", FileSource("Image", "Actor/Monster/Human/Dark Knight/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Water_DAMAGE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Water_MOVE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Water", "Water_MOVE.png"), 2, 2);
	
	_IMAGE->CreateFrameImage("DarkKnight_Wind_IDLE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Wind", "Wind_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Wind_ATTACK", FileSource("Image", "Actor/Monster/Human/Dark Knight/Wind", "Wind_ATTACK.png"), 12, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Wind_GUARD", FileSource("Image", "Actor/Monster/Human/Dark Knight/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("DarkKnight_Wind_MOVE", FileSource("Image", "Actor/Monster/Human/Dark Knight/Wind", "Wind_MOVE.png"), 2, 2);

	//Hobit
	_IMAGE->CreateFrameImage("Hobit_Earth_IDLE", FileSource("Image", "Actor/Monster/Human/Hobit/Earth", "Earth_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Hobit_Earth_ATTACK", FileSource("Image", "Actor/Monster/Human/Hobit/Earth", "Earth_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Hobit_Earth_GUARD", FileSource("Image", "Actor/Monster/Human/Hobit/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Human/Hobit/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Earth_MOVE", FileSource("Image", "Actor/Monster/Human/Hobit/Earth", "Earth_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Hobit_Fire_IDLE", FileSource("Image", "Actor/Monster/Human/Hobit/Fire", "Fire_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Hobit_Fire_ATTACK", FileSource("Image", "Actor/Monster/Human/Hobit/Fire", "Fire_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Hobit_Fire_GUARD", FileSource("Image", "Actor/Monster/Human/Hobit/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Human/Hobit/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Fire_MOVE", FileSource("Image", "Actor/Monster/Human/Hobit/Fire", "Fire_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Hobit_Water_IDLE", FileSource("Image", "Actor/Monster/Human/Hobit/Water", "Water_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Hobit_Water_ATTACK", FileSource("Image", "Actor/Monster/Human/Hobit/Water", "Water_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Hobit_Water_GUARD", FileSource("Image", "Actor/Monster/Human/Hobit/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Water_DAMAGE", FileSource("Image", "Actor/Monster/Human/Hobit/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Water_MOVE", FileSource("Image", "Actor/Monster/Human/Hobit/Water", "Water_MOVE.png"), 6, 2);
	
	_IMAGE->CreateFrameImage("Hobit_Wind_IDLE", FileSource("Image", "Actor/Monster/Human/Hobit/Wind", "Wind_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Hobit_Wind_ATTACK", FileSource("Image", "Actor/Monster/Human/Hobit/Wind", "Wind_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Hobit_Wind_GUARD", FileSource("Image", "Actor/Monster/Human/Hobit/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Human/Hobit/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Hobit_Wind_MOVE", FileSource("Image", "Actor/Monster/Human/Hobit/Wind", "Wind_MOVE.png"), 6, 2);

	//Kitcat
	_IMAGE->CreateFrameImage("Kitcat_Earth_IDLE", FileSource("Image", "Actor/Monster/Human/Kitcat/Earth", "Earth_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Kitcat_Earth_ATTACK", FileSource("Image", "Actor/Monster/Human/Kitcat/Earth", "Earth_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Kitcat_Earth_GUARD", FileSource("Image", "Actor/Monster/Human/Kitcat/Earth", "Earth_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Earth_DAMAGE", FileSource("Image", "Actor/Monster/Human/Kitcat/Earth", "Earth_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Earth_MOVE", FileSource("Image", "Actor/Monster/Human/Kitcat/Earth", "Earth_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("Kitcat_Fire_IDLE", FileSource("Image", "Actor/Monster/Human/Kitcat/Fire", "Fire_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Kitcat_Fire_ATTACK", FileSource("Image", "Actor/Monster/Human/Kitcat/Fire", "Fire_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Kitcat_Fire_GUARD", FileSource("Image", "Actor/Monster/Human/Kitcat/Fire", "Fire_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Fire_DAMAGE", FileSource("Image", "Actor/Monster/Human/Kitcat/Fire", "Fire_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Fire_MOVE", FileSource("Image", "Actor/Monster/Human/Kitcat/Fire", "Fire_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("Kitcat_Water_IDLE", FileSource("Image", "Actor/Monster/Human/Kitcat/Water", "Water_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Kitcat_Water_ATTACK", FileSource("Image", "Actor/Monster/Human/Kitcat/Water", "Water_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Kitcat_Water_GUARD", FileSource("Image", "Actor/Monster/Human/Kitcat/Water", "Water_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Water_DAMAGE", FileSource("Image", "Actor/Monster/Human/Kitcat/Water", "Water_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Water_MOVE", FileSource("Image", "Actor/Monster/Human/Kitcat/Water", "Water_MOVE.png"), 5, 2);
	
	_IMAGE->CreateFrameImage("Kitcat_Wind_IDLE", FileSource("Image", "Actor/Monster/Human/Kitcat/Wind", "Wind_IDLE.png"), 5, 2);
	_IMAGE->CreateFrameImage("Kitcat_Wind_ATTACK", FileSource("Image", "Actor/Monster/Human/Kitcat/Wind", "Wind_ATTACK.png"), 6, 2);
	_IMAGE->CreateFrameImage("Kitcat_Wind_GUARD", FileSource("Image", "Actor/Monster/Human/Kitcat/Wind", "Wind_GUARD.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Wind_DAMAGE", FileSource("Image", "Actor/Monster/Human/Kitcat/Wind", "Wind_DAMAGE.png"), 1, 2);
	_IMAGE->CreateFrameImage("Kitcat_Wind_MOVE", FileSource("Image", "Actor/Monster/Human/Kitcat/Wind", "Wind_MOVE.png"), 5, 2);

	return S_OK;
}

HRESULT ImageSource::CreateUIImage(void)
{
	_IMAGE->CreateFrameImage("Menu", FileSource("Image", "UI", "Panel.png"), 1, 1);
	_IMAGE->CreateFrameImage("DataButton", FileSource("Image", "UI", "DataButton.png"), 1, 2);
	_IMAGE->CreateFrameImage("StatusPannel", FileSource("Image", "UI", "StatusButton.png"), 1, 1);
	_IMAGE->CreateFrameImage("Plus", FileSource("Image", "UI", "Plus.png"), 1, 2);
	_IMAGE->CreateFrameImage("Minus", FileSource("Image", "UI", "Minus.png"), 1, 2);
	_IMAGE->CreateFrameImage("TimeBoard", FileSource("Image", "UI", "TimeBoard.png"), 1, 1);
	_IMAGE->CreateFrameImage("TimeArrow", FileSource("Image", "UI", "TimeArrow.png"), 1, 1);
	_IMAGE->CreateFrameImage("TimeParameter_Active", FileSource("Image", "UI", "TimeParameter_Active.png"), 1, 1);
	_IMAGE->CreateFrameImage("TimeParameter_Ready", FileSource("Image", "UI", "TimeParameter_Ready.png"), 1, 1);
	_IMAGE->CreateFrameImage("Battle_Avoid", FileSource("Image", "UI", "Battle_UI_Avoid.png"), 1, 1);
	_IMAGE->CreateFrameImage("Battle_Guard", FileSource("Image", "UI", "Battle_UI_Guard.png"), 1, 1);
	_IMAGE->CreateFrameImage("Battle_Attack_Normal", FileSource("Image", "UI", "Battle_UI_Attack_Normal.png"), 1, 1);
	_IMAGE->CreateFrameImage("Battle_Attack_Strong", FileSource("Image", "UI", "Battle_UI_Attack_Strong.png"), 1, 1);
	_IMAGE->CreateFrameImage("Battle_Cancel", FileSource("Image", "UI", "Battle_UI_Cancel.png"), 1, 1);
	return S_OK;
}

HRESULT ImageSource::CreateEffectImage(void)
{
	_IMAGE->CreateFrameImage("Effect_Hit", FileSource("Image", "Effect", "Effect_Hit.png"), 5, 1);
	_IMAGE->CreateFrameImage("Effect_Slash", FileSource("Image", "Effect", "Effect_Slash.png"), 5, 1);
	_IMAGE->CreateFrameImage("Effect_Guard", FileSource("Image", "Effect", "Effect_Guard.png"), 5, 1);
	_IMAGE->CreateFrameImage("Effect_Claw", FileSource("Image", "Effect", "Effect_Claw.png"), 7, 1);
	return S_OK;
}

