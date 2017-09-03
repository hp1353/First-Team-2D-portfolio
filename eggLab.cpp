#include "stdafx.h"
#include "eggLab.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "wallcrush.h"

extern float MusicMasterVol;
extern float SoundMasterVol;
eggLab::eggLab()
{
}


eggLab::~eggLab()
{
}


HRESULT eggLab::init()
{
	door = RectMake(0, 0, 30, 45);


	_enemyManager = new EnemyFullManager;

	_player->setCurScene("eggLab");
	_player->setPxlImg("StageEggLabPxl");
	_player->SetLinkEnemy(_enemyManager);

	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		_player->getVWeapone()[i]->LinkToEnemy(_enemyManager);
		_player->getVWeapone()[i]->setPxlImg("StageEggLabPxl");
	}


	_ItemManager = new ItemManager;
	_ItemManager->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), "StageEggLabPxl");
	_ItemManager->setPlayerLink(_player);






	_wce = new wallcrush;
	_wce->init();
	_wce->setPlayerLink(_player);

	SOUNDMANAGER->play("에그랩실", MusicMasterVol /2);
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("보스브금");
	SOUNDMANAGER->stop("Stage1Intro");
	SOUNDMANAGER->stop("Stage2");
	



	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		_player->getVWeapone()[i]->LinkToEnemy(_enemyManager);
		_player->getVWeapone()[i]->setPxlImg("StageEggLabPxl");
	}

	ChangeDcOut = IMAGEMANAGER->findImage("ChangeDcOut");
	ChangeDcIn = IMAGEMANAGER->findImage("ChangeDcIn");

	//////////////////////////////////////////////
	ChangeDcOutAni = new animation;
	ChangeDcOutAni->init(ChangeDcOut->getWidth(), ChangeDcOut->getHeight(), 640, 480);
	ChangeDcOutAni->setPlayFrame(11, 0, false, false);
	ChangeDcOutAni->setFPS(15);
	ChangeDcOutAni->start();
	///////////////////////////////////////////////
	ChangeDcInAni = new animation;
	ChangeDcInAni->init(ChangeDcIn->getWidth(), ChangeDcIn->getHeight(), 640, 480);
	ChangeDcInAni->setDefPlayFrame(false, false);
	ChangeDcInAni->setFPS(15);
	///////////////////////////////////////////////
	changescene = false;

	_saveLoad = new SaveLoad;
	_saveLoad->setPlayerLink(_player);
	_saveDisk = RectMake(173, 315, 32, 33);
	_fullHeal = RectMake(213, 315, 28, 33);
	_diskSpin = new animation;
	_diskSpin->init(256, 33, 32, 33);
	_diskSpin->setDefPlayFrame(false, true);
	_diskSpin->setFPS(10);
	_diskSpin->start();
	_isSaving = false;
	_saveCount = 0;

	_ItemManager->SetLaser(284, 200);
	_ItemManager->SetSnake(60, 335);

	return S_OK;
}
void eggLab::release()
{
	SAFE_DELETE(ChangeDcOutAni);
	SAFE_DELETE(ChangeDcInAni);
	SAFE_DELETE(_saveLoad);
	SAFE_DELETE(_diskSpin);
}
void eggLab::update()
{
	ChangeDcOutAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	ChangeDcInAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	_diskSpin->frameUpdate(TIMEMANAGER->getElapsedTime());

	door = RectMake(530, 301, 30, 45);
	_wce->update();
	if (!_isSaving)
	{
		if (!_ItemManager->isStopTime())
		_player->update(false);
		if (PtInRect(&_saveDisk, { _player->getPlayer()->x, _player->getPlayer()->y }))
		{
			if (KEYMANAGER->isOnceDown(VK_DOWN))
			{
				_saveLoad->Save();
				SOUNDMANAGER->play("레벨업", 1.f);
				_isSaving = true;
			}
		}
		else if (PtInRect(&_fullHeal, { _player->getPlayer()->x, _player->getPlayer()->y }))
		{
			if (KEYMANAGER->isOnceDown(VK_DOWN))
			{
				_player->getPlayer()->fullHeal();
				SOUNDMANAGER->play("풀피", 1.f);
			}
		}
		else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &door))
		{
			if (KEYMANAGER->isOnceDown(VK_DOWN))
			{
				if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
				ChangeDcInAni->start();
				changescene = true;
			}
		}
	}
	_ItemManager->update(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());
	if (changescene && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(_player->getPlayer()->_SaveX, _player->getPlayer()->_SaveY, 25, 25));
		_player->GetCamera()->setCamPos();
		if (_player->getPlayer()->_SaveStagestr == STAGE_EGG1)
			SCENEMANAGER->changeScene("eggHatchery");
		else if (_player->getPlayer()->_SaveStagestr == STAGE_EGG2)
			SCENEMANAGER->changeScene("eggHatchery2");
	}
	else if (_isSaving)
	{
		_saveCount++;
		if (_saveCount < 45) return;
		if (KEYMANAGER->isOnceDown('Z') || KEYMANAGER->isOnceDown(VK_DOWN))
		{
			_isSaving = false;
			_saveCount = 0;
		}
	}
}
void eggLab::render()
{
	IMAGEMANAGER->findImage("backgroundEggLab")->render(getMemDC());
	//Rectangle(getMemDC(), door.left, door.top, door.right, door.bottom);
	IMAGEMANAGER->findImage("SaveDiscket")->aniRender(getMemDC(), _saveDisk.left, _saveDisk.top, _diskSpin);
	IMAGEMANAGER->findImage("FullHeal")->frameRender(getMemDC(), _fullHeal.left, _fullHeal.top, 1, 0);

	_player->render();
	_wce->render();



	EFFECTMANAGER->render();
	_ItemManager->UIrender();


	if (_isSaving) IMAGEMANAGER->findImage("saveEvent")->render(getMemDC(), _player->GetCamera()->getCamX() + 80, _player->GetCamera()->getCamY() + CENTERY - 58);
	if (ChangeDcInAni->isPlay()) {
		ChangeDcIn->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcInAni);
	}
	if (ChangeDcOutAni->isPlay()) {
		ChangeDcOut->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcOutAni);
	}
}