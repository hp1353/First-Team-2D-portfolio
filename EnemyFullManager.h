#pragma once
#include "gameNode.h"
#include <vector>
#include "angel.h"
#include "critter.h"
#include "basil.h"
#include "basu.h"
#include "bat.h"
#include "beetle.h"
#include "behemoth.h"
#include "breakBrick.h"
#include "BossBody.h"
#include "ZombieDragon.h"

class ItemManager;

class EnemyFullManager : public gameNode
{
private:
	critter* _critter;
	basu* _basu;
	basil* _basil;
	bat* _bat;
	beetle* _beetle;
	behemoth* _behemoth;
	angel* _angel;
	ZombieDragon* _dragon;
	breakBrick* _Brick;
	ItemManager* _ItemManager;
	Player *_player;

	POINT _EnemyDeadPos[200];


	const char* _imgName; //맵 픽셀 충돌용 이미지 이름

	typedef vector<enemy*> _arrEnemy;
	typedef vector<enemy*>::iterator _iterEnemy;

	typedef vector<enemy*> _arrBrick;
	typedef vector<enemy*>::iterator _iterBrick;
	//깨지는 벽돌이 에네미 벡터에 넣든 브릭 함수에 넣든 자유

	_arrEnemy _vEnemy;
	_arrBrick _vBrick;

	int _AngelNum;

public:
	EnemyFullManager();
	~EnemyFullManager();

	HRESULT init(const char* imageName);
	void release();
	void update(Player* player);
	void render();

	void addEnemy(int x, int y, int EnemyType, bool Right, float power);
	void addBoss(enemy* boss);
	void addBall(BossBody* boss);
	void addWood(BossBody* boss);
	void eraseEnemy(int arrNum);
	void eraseBrick(int arrNum);
	void clearEnemy();
	void clearBrick();
	int CheckAngelNum();
	void AllKillAngel();

	_arrEnemy getVEnemy() { return _vEnemy; }
	_arrEnemy getVBrick() { return _vBrick; }

	void DamageRender(int i);


	void SetItemMemory(ItemManager* Itmemanager) { _ItemManager = Itmemanager; }

};
