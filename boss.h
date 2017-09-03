#pragma once
#include "gameNode.h"
#include "animation.h"
#include "enemy.h"
#include "BossBall.h"

//class boss : public enemy
//{
//private:
//
//
//	float _playX;
//	float _playY;
//	RECT _headRc;
//	RECT _movingRc;
//	image* _img;
//	float _radius;
//	float _angle;
//
//	float _speed;
//	int _motion;
//	float _power;
//	float _gravity;
//	float _jumpCount;
//
//
//	int _stageNum;
//	int _bossCount;
//	int _bossWoodPop;
//
//	tagRect _testRc;
//
//	tagBoss _bossBody;
//	tagRect _spike;
//	bool _spikeOut;
//
//	enemy* _BossBall;
//
//	vector<enemy*> _vBossBall;
//	vector<enemy*>::iterator _viBossBall;
//
//	vector<tagBossBoll*> _vBossWood;
//	vector<tagBossBoll*>::iterator _viBossWood;
//
//	vector<tagBossBoll*> _vBossSkull;
//	vector<tagBossBoll*>::iterator _viBossSkull;
//
//	vector<tagBoss*> _vBossPops;
//	vector<tagBoss*>::iterator _viBossPops;
//
//	vector<tagRect*> _vBlood;
//	vector<tagRect*>::iterator _viBlood;
//	
//
//
//
//
//
//public:
//	boss();
//	~boss();
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//
//	void bossHeadCollision();
//	void collision();
//	void move();
//
//	
//	
//	void bollCollision();
//
//	void skullDrop(int arrNum, int fireX);
//	void skullMove();
//
//
//	void bossJump();
//	void bossJumpCollision();
//	void popsFire(int fireX);
//	void popsMove();
//
//
//	void bossWheelMove();
//	void bossWheelCollision();
//
//
//
//	void bossStageOne();
//	void bossStageTwo();
//	void bossStageThree();
//
//	void bossStageOneRender();
//	void bossStageTwoRender();
//	void bossStageThreeRender();
//};
//
