#pragma once
#include "gameNode.h"
#include "wallcrush.h"
#include "EnemyFullManager.h"
#include "SaveLoad.h"

class Player;
class Inventory;
class ItemManager;

class eggLab : public gameNode
{
	Player* _player;
	Inventory* _Inven;
	ItemManager* _ItemManager;
	PlayerInfo player;
	wallcrush* _wce;
	EnemyFullManager* _enemyManager;
	RECT door;

	image* ChangeDcOut;
	image* ChangeDcIn;
	animation* ChangeDcOutAni;
	animation* ChangeDcInAni;
	bool changescene;

	bool _isSaving;
	int _saveCount;
	SaveLoad* _saveLoad;
	animation* _diskSpin;
	RECT _saveDisk;
	RECT _fullHeal;

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

	eggLab();
	~eggLab();
};