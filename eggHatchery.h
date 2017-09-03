#pragma once
#include "gameNode.h"
#include "EnemyFullManager.h"
#include "wallcrush.h"
#include "NpcEvent.h"
#include "MachineNpc.h"

class Player;
class Inventory;
class ItemManager;
class MachineNpc;

class eggHatchery : public gameNode
{
	int count;
	float index;
	float loopx;
	image* SelectPoint1;
	wallcrush* _wce;

	RECT doorExit;
	RECT doorSaveRoom;
	RECT doorStage3;

	Player* _player;
	Inventory* _Inven;
	ItemManager* _ItemManager;
	PlayerInfo player;
	MachineNpc* _npc;

	EnemyFullManager* _eManager;
	animation* ChangeDcOutAni;
	animation* ChangeDcInAni;
	bool changescene;
	bool changescene2;
	bool changescene3;
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

	void FrameUpdate();
	void Loop();

	eggHatchery();
	~eggHatchery();
};

