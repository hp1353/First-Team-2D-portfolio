#include "stdafx.h"
#include "eggHatchery.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "wallcrush.h"
extern float MusicMasterVol;
extern float SoundMasterVol;

eggHatchery::eggHatchery()
{
}


eggHatchery::~eggHatchery()
{
}


HRESULT eggHatchery::init()
{
	loopx = 0;

	doorExit = RectMake(143, 162, 30, 45);
	doorSaveRoom = RectMake(3983, 355, 30, 45);
	doorStage3 = RectMake(4272, 162, 30, 45);

	_eManager = new EnemyFullManager;
	_eManager->init("Stage2Pxl");
	//ENEMY
	//BASIL
	_eManager->addEnemy(210, 451, E_BASIL, true, NULL);
	//CRITTER
	_eManager->addEnemy(684, 185, E_CRITTER, false, NULL);
	_eManager->addEnemy(723, 185, E_CRITTER, false, NULL);
	_eManager->addEnemy(648, 185, E_CRITTER, false, NULL);
	_eManager->addEnemy(1073, 185, E_CRITTER, true, NULL);
	_eManager->addEnemy(1174, 185, E_CRITTER, true, NULL);
	_eManager->addEnemy(1840, 217, E_CRITTER, true, NULL);
	_eManager->addEnemy(1899, 217, E_CRITTER, true, NULL);
	_eManager->addEnemy(1974, 217, E_CRITTER, true, NULL);
	_eManager->addEnemy(3231, 185, E_CRITTER, true, NULL);
	_eManager->addEnemy(3274, 185, E_CRITTER, true, NULL);
	_eManager->addEnemy(3324, 185, E_CRITTER, true, NULL);
	//BEHEMOTH
	_eManager->addEnemy(833, 217, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(913, 217, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(1342, 217, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(1448, 217, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(2358, 250, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(2459, 250, E_BEHEMOTH, true, NULL);
	//BASU
	_eManager->addEnemy(2700, 95, E_BASU, true, NULL);
	_eManager->addEnemy(4200, 100, E_BASU, true, NULL);
	//ZOMBIE
	_eManager->addEnemy(3962, 206, E_ZOMBIE, true, NULL);

	_player->setCurScene("eggHatchery");
	_player->setPxlImg("Stage2Pxl");
	_player->SetLinkEnemy(_eManager);

	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		_player->getVWeapone()[i]->LinkToEnemy(_eManager);
		_player->getVWeapone()[i]->setPxlImg("Stage2Pxl");
	}


	_ItemManager = new ItemManager;
	_ItemManager->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), "Stage2Pxl");
	_ItemManager->setPlayerLink(_player);

	_eManager->SetItemMemory(_ItemManager);

	_Inven = new Inventory;
	_Inven->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());

	SOUNDMANAGER->stop("에그랩실");
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("Stage1Intro");
	SOUNDMANAGER->stop("보스브금");
	if(!SOUNDMANAGER->isPlaySound("Stage2"))
	SOUNDMANAGER->play("Stage2", MusicMasterVol / 2);

	//////////////////////////////////////////////
	ChangeDcOutAni = new animation;
	ChangeDcOutAni->init(IMAGEMANAGER->findImage("ChangeDcOut")->getWidth(), IMAGEMANAGER->findImage("ChangeDcOut")->getHeight(), 640, 480);
	ChangeDcOutAni->setPlayFrame(11, 0, false, false);
	ChangeDcOutAni->setFPS(15);
	ChangeDcOutAni->start();
	///////////////////////////////////////////////
	ChangeDcInAni = new animation;
	ChangeDcInAni->init(IMAGEMANAGER->findImage("ChangeDcIn")->getWidth(), IMAGEMANAGER->findImage("ChangeDcIn")->getHeight(), 640, 480);
	ChangeDcInAni->setDefPlayFrame(false, false);
	ChangeDcInAni->setFPS(15);
	///////////////////////////////////////////////
	changescene = false;
	changescene2 = false;
	changescene3 = false;

	_wce = new wallcrush;
	_wce->init();
	_wce->setPlayerLink(_player);

	_npc = new MachineNpc;
	_npc->init();
	_npc->setPlayerLink(_player);


	_ItemManager->SetMaxHeal(1340, 347, 2);
	_ItemManager->SetFire(1418, 221);
	//_ItemManager->SetLaser(4266, 380);

	//_ItemManager->Set

	return S_OK;
}
void eggHatchery::release()
{
	_eManager->release();
	SAFE_DELETE(_eManager);

}
void eggHatchery::update()
{
	//Loop();
	//doorExit = RectMake(143, 162, 30, 45);
	//doorSaveRoom1 = RectMake(3983, 355, 30, 45);
	//doorSaveRoom2 = RectMake(7022, 194, 30, 45);
	//doorSaveRoom3 = RectMake(9485, 225, 30, 45);


	_npc->update();
	ChangeDcOutAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	ChangeDcInAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	


	if (!SOUNDMANAGER->isPlaySound(("Stage2Intro")) && !SOUNDMANAGER->isPlaySound(("Stage2")))
		SOUNDMANAGER->play("Stage2", MusicMasterVol / 2);

	if (!_npc->isStopTime())
	{
		if (!_ItemManager->isStopTime())
		{
			_player->update(false);
			_eManager->update(_player);
			_Inven->update(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());
		}

		_ItemManager->update(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());
		_wce->update();
	}
	if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorExit))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			
			if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
			ChangeDcInAni->start();
			changescene = true;

			
		}
	}
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorSaveRoom))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			

			if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
			ChangeDcInAni->start();
			changescene2 = true;

			
		}
	}
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorStage3))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			

			if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
			ChangeDcInAni->start();
			changescene3 = true;

			
		}
	}

	if (changescene && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(1762, 300, 25, 25));
		_player->GetCamera()->setCamPos();

		SCENEMANAGER->changeScene("TestScene");
	}
	else if (changescene2 && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(541, 336, 25, 25));
		_player->GetCamera()->setCamPos();
		//플레이어 들어가는 위치 저장
		_player->getPlayer()->_SaveStagestr = STAGE_EGG1;
		_player->SavePlayerPos(doorSaveRoom.left + 10, doorSaveRoom.top + 34);
		SCENEMANAGER->changeScene("eggLab");
	}
	else if (changescene3 && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(189, 190, 25, 25));
		_player->GetCamera()->setCamPos();
		SCENEMANAGER->changeScene("eggHatchery2");

		
	}
}
void eggHatchery::render()
{
	//IMAGEMANAGER->findImage("background2_loop")->loopRender(getMemDC(), &RectMake(0, 0, 4335, WINSIZEY), loopx, 0);
	IMAGEMANAGER->findImage("background2")->render(getMemDC());
	_eManager->render();

	_player->render();
	_wce->render();
	_ItemManager->render();

	IMAGEMANAGER->findImage("background2_obj")->render(getMemDC());


	_player->uiRender();
	_npc->render();

		_ItemManager->UIrender();
	


		EFFECTMANAGER->render();
	IMAGEMANAGER->findImage("ChangeDcIn")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcInAni);

	if (ChangeDcOutAni->isPlay()) {
		IMAGEMANAGER->findImage("ChangeDcOut")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcOutAni);
	}


	//Rectangle(getMemDC(), doorExit.left, doorExit.top, doorExit.right, doorExit.bottom);
	//Rectangle(getMemDC(), doorSaveRoom.left, doorSaveRoom.top, doorSaveRoom.right, doorSaveRoom.bottom);
	//Rectangle(getMemDC(), doorStage3.left, doorStage3.top, doorStage3.right, doorStage3.bottom);
}
/*
void eggHatchery::FrameUpdate()
{

	//프레임돌리자
	count++;
	SelectPoint1->setFrameY(0);
	if (count % 10 == 0)
	{

		SelectPoint1->setFrameX(index);
		index++;
		if (index > SelectPoint1->getMaxFrameX())
		{
			index = 0;
		}
	}
}
*/
void eggHatchery::Loop()
{
	if (!_player->getPlayer()->_isPixelR && !_player->getPlayer()->_isPixelL)
	{
		if (_player->getPlayer()->getMotion() != IDLE && _player->getPlayer()->getMotion() != JUMP)
		{
			if (_player->getPlayer()->_isRight) loopx += 0.2;
			else loopx -= 0.2;
		}
	}
}