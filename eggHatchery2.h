#pragma once
#include "gameNode.h"
#include "EnemyFullManager.h"
#include "wallcrush.h"
#include "NpcEvent.h"

class Player;
class Inventory;
class ItemManager;
class NpcEvent;
class eggHatchery2 : public gameNode
{
	int count;
	float index;
	float loopx;
	image* SelectPoint1;
	wallcrush* _wce;
	RECT doorExit;
	RECT doorSaveRoom1;
	RECT doorBossRoom;
	RECT doorSaveRoom2;
	NpcEvent* _npc;
	Player* _player;
	Inventory* _Inven;
	ItemManager* _ItemManager;
	PlayerInfo player;

	EnemyFullManager* _eManager;
	animation* ChangeDcOutAni;
	animation* ChangeDcInAni;
	bool changescene;
	bool changescene2;
	bool changescene3;

	//º¸½º ¹®
	RECT _bossRoomDoor = RectMake(4990, 250, 30, 20);

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

	void setNpcLink(NpcEvent* npc) { _npc = npc; }

	void FrameUpdate();
	void Loop();

	eggHatchery2();
	~eggHatchery2();
};

