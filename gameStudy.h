#pragma once

#include "gameNode.h"
#include "actionTest.h"
#include "starWarsScene.h"
#include "selectScene.h"
#include "Player.h"

#include "MainMenu.h"
#include "TestScene.h"
#include "eggHatchery.h"
#include "stage0.h"
#include "eggLab.h"
#include "eggHatchery2.h"
#include "BossRoom.h"
#include "endingScene.h"

#include "SaveLoad.h"

class gameStudy : public gameNode
{
private:
	bool _DeadCount;
	//EnemyFullManager* _EnemyManager;
	Player *_player;
	TestScene *_TestScene;
	stage0* _stage0;
	eggHatchery *_eggHatchery;
	eggLab *_eggLab;
	SaveLoad* _saveLoad;
	eggHatchery2 *_eggHatchery2;
	BossRoom* _bossRoom;
	endingScene* _endingScene;

	animation* ChangeDcInAni;
	
	//엔딩이미지
	image* _endImg;
	int _endImgY;
	int _endingOn;


public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

class blankScene : public gameNode
{
public:
	blankScene() {};
	~blankScene() {};
};