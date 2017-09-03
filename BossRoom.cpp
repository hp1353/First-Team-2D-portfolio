#include "stdafx.h"
#include "BossRoom.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemManager.h"
extern float MusicMasterVol;
extern float SoundMasterVol;


BossRoom::BossRoom()
{

}
BossRoom::~BossRoom()
{

}



HRESULT BossRoom::init()
{
	IMAGEMANAGER->addImage("stage_finalBack", "image/boss/stage_finalBack.bmp", 1088, 898, true, 0xff00ff);
	IMAGEMANAGER->addImage("stage_finalFront", "image/boss/stage_finalFront.bmp", 1088, 898, true, 0xff00ff);
	IMAGEMANAGER->addImage("stage_finalWall", "image/boss/stage_finalWall.bmp", 1088, 898, false, false);
	IMAGEMANAGER->addImage("stage_finalPixel", "image/boss/stage_finalPixel.bmp", 1088, 898, false, false);
	IMAGEMANAGER->addImage("stage_finalPixelSpike", "image/boss/stage_finalPixelSpike.bmp", 1088, 898, false, false);

	IMAGEMANAGER->addImage("boss_body1", "image/boss/boss_body.bmp", 240, 240, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_body1Hit", "image/boss/boss_bodyHit.bmp", 240, 240, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_body2", "image/boss/boss_body2.bmp", 240, 240, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_body3", "image/boss/boss_body3.bmp", 240, 240, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_body3Hit", "image/boss/boss_body3Hit.bmp", 240, 240, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_wood", "image//boss/boss_wood.bmp", 64, 22, true, 0xff00ff);
	IMAGEMANAGER->addImage("spike", "image/boss/spike.bmp", 961, 47, true, 0xff00ff);
	IMAGEMANAGER->addImage("effect_blood", "image//boss/effect_blood.bmp", 12, 12, true, 0xff00ff);


	IMAGEMANAGER->addImage("boss_bollBtm", "image/boss/boss_bollBtm.bmp", 78, 78, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_bollTop", "image/boss/boss_bollTop.bmp", 78, 78, true, 0xff00ff);
	IMAGEMANAGER->addImage("boss_bollHit", "image/boss/boss_bollHit.bmp", 78, 78, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("effect_skul", "image/boss/effect_skul.bmp", 128, 32, 4, 1, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("effect_pop", "image/boss/effect_pop.bmp", 128, 32, 4, 1, true, 0xff00ff);
	IMAGEMANAGER->addImage("effect_bones", "image/boss/effect_bones.bmp", 128, 32, true, 0xff00ff);
	EFFECTMANAGER->init();
	EFFECTMANAGER->addEffect("effect_dust", "image/boss/effect_dust.bmp", 231, 33, 33, 33, 1, 0.4f, 8);
	EFFECTMANAGER->addEffect("effect_dustPop", "image/boss/effect_dust.bmp", 231, 33, 33, 33, 1, 0.4f, 20);
	EFFECTMANAGER->addEffect("effect_dustBig", "image/boss/effect_dust2.bmp", 462, 66, 66, 66, 1, 0.3f, 4);
	EFFECTMANAGER->addEffect("effect_dustUP", "imag/boss/effect_dustUP.bmp", 231, 33, 33, 33, 1, 0.28f, 8);
	EFFECTMANAGER->addEffect("effect_bossPop", "image/boss/effect_bossPop.bmp", 2002, 285, 286, 285, 1, 0.28f, 1);

	//////////////////////////////////////////////
	ChangeDcOutAni = new animation;
	ChangeDcOutAni->init(IMAGEMANAGER->findImage("ChangeDcOut")->getWidth(), IMAGEMANAGER->findImage("ChangeDcOut")->getHeight(), 640, 480);
	ChangeDcOutAni->setPlayFrame(11, 0, false, false);
	ChangeDcOutAni->setFPS(15);
	ChangeDcOutAni->start();
	///////////////////////////////////////////////
	//ChangeDcInAni = new animation;
	//ChangeDcInAni->init(IMAGEMANAGER->findImage("ChangeDcIn")->getWidth(), IMAGEMANAGER->findImage("ChangeDcIn")->getHeight(), 640, 480);
	//ChangeDcInAni->setDefPlayFrame(false, false);
	//ChangeDcInAni->setFPS(15);
	/////////////////////////////////////////////////
	changescene = false;



	SOUNDMANAGER->stop("에그랩실");
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("Stage2");
	SOUNDMANAGER->stop("Stage1Intro");
	if (!SOUNDMANAGER->isPlaySound("보스브금"))
		SOUNDMANAGER->play("보스브금", SoundMasterVol / 2);
	_enemyManager = new EnemyFullManager;

	_player->setCurScene("boss");
	_player->setPxlImg("stage_finalPixel");
	_player->SetLinkEnemy(_enemyManager);

	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		_player->getVWeapone()[i]->LinkToEnemy(_enemyManager);
		_player->getVWeapone()[i]->setPxlImg("stage_finalPixel");
	}

	_bossBody = new BossBody;
	_bossBody->init(BOSSCENTERX, BOSSCENTERY, "stage_finalPixel");
	_bossBody->setPlayerLink(_player);


	_enemyManager->init("stage_finalPixel");

	_ItemManager = new ItemManager;
	_ItemManager->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), "stage_finalPixel");
	_ItemManager->setPlayerLink(_player);

	_enemyManager->SetItemMemory(_ItemManager);

	_enemyManager->addBoss(_bossBody);
	_enemyManager->addBall(_bossBody);
	_enemyManager->addWood(_bossBody);
		
	return S_OK;

}

void BossRoom::release()
{
	_bossBody->release(true);
	//SAFE_DELETE(_bossBody);
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void BossRoom::update()
{
	if (ChangeDcOutAni->isPlay()) ChangeDcOutAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	_bossBody->update(true);
	_player->update(isClear);
	_enemyManager->update(_player);
	_ItemManager->update(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());

	if (_bossBody->getTransed())
	{
		_player->setPxlImg("stage_finalPixelSpike");
	}
	else _player->setPxlImg("stage_finalPixel");

	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		if (_bossBody->getTransed())
		{
			_player->getVWeapone()[i]->setPxlImg("stage_finalPixelSpike");
		}
		else _player->getVWeapone()[i]->setPxlImg("stage_finalPixel");
	}

	if (_bossBody->getTransed())
	{
		_enemyManager->init("stage_finalPixelSpike");
	}
	else _enemyManager->init("stage_finalPixel");

	if (_bossBody->getStageNum() == 2 )
	{
		if (_enemyManager->CheckAngelNum() <= 9)
			_enemyManager->addEnemy(RND->getFromIntTo(0, 898), RND->getFromIntTo(0, 898), E_ANGEL, true, NULL);
	}
	else if (_bossBody->getStageNum() == 3)
	{
		isClear = true;
		_enemyManager->AllKillAngel();
	}

	if (_bossBody->getStageNum() == 3) {
		_enemyManager->clearBrick();
		_player->getPlayer()->_motion = IDLE;

	}

	if (_bossBody->isTheEnd())
	{
		if (!changescene &&!ChangeDcOutAni->isPlay()) {
			ChangeDcOutAni->setDefPlayFrame(false, false);
			ChangeDcOutAni->start();
			changescene = true;
		}
	}
	if (changescene && !ChangeDcOutAni->isPlay())
	{
		SCENEMANAGER->changeScene("ending");
	}






}

void BossRoom::render()
{
	IMAGEMANAGER->findImage("stage_finalWall")->render(getMemDC());
	IMAGEMANAGER->findImage("stage_finalBack")->render(getMemDC());

	_enemyManager->render();
	_bossBody->render(true);

	_player->render();
	_ItemManager->render();

	EFFECTMANAGER->render();
	IMAGEMANAGER->findImage("stage_finalFront")->render(getMemDC());


	

	_bossBody->ProgressBarRender();

	if (ChangeDcOutAni->isPlay()) {
		IMAGEMANAGER->findImage("ChangeDcOut")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcOutAni);
	}
}