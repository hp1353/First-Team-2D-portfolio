#pragma once
#include "gameNode.h"
#include "EnemyFullManager.h"
#include "BossBody.h"

class Player;
class Inventory;
class ItemManager;

class BossRoom : public gameNode
{
	Player* _player;
	Inventory* _Inven;
	ItemManager* _ItemManager;
	PlayerInfo player;
	BossBody* _bossBody;


	bool isClear;
	bool changescene;

	EnemyFullManager* _enemyManager;
	/*RECT doorLeft;
	RECT doorRight;*/
	//bool changescene1;
	//bool changescene2;
	int count;
	int index;
	/*image* ChangeDcIn;
	image* ChangeDcOut;*/
	animation* ChangeDcOutAni;
	//animation* ChangeDcInAni;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void setPlayerMemory(Player* Player)
	{
		_player = Player;
	}
	Player* GetPlayer() { return _player; }

	void setLink(Inventory* Inven)
	{
		_Inven = Inven;
	}
	Inventory* GetInven() { return _Inven; }

	

	BossRoom();
	~BossRoom();
};