#include "stdafx.h"
#include "eggHatchery2.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "wallcrush.h"
#include "NpcEvent.h"
extern float MusicMasterVol;
extern float SoundMasterVol;
extern bool viewAllEvent;

eggHatchery2::eggHatchery2()
{
}


eggHatchery2::~eggHatchery2()
{
}


HRESULT eggHatchery2::init()
{
	loopx = 0;

	doorExit = RectMake(178, 162, 30, 45);
	doorSaveRoom1 = RectMake(2720, 194, 30, 45);
	doorBossRoom = RectMake(4991, 226, 30, 45);
	doorSaveRoom2 = RectMake(5182, 226, 30, 45);

	_eManager = new EnemyFullManager;
	_eManager->init("Stage3Pxl");
	//ENEMY
	//CRITTER
	_eManager->addEnemy(3965, 182, E_CRITTER, true, NULL);
	_eManager->addEnemy(4050, 182, E_CRITTER, true, NULL);


	//BEHEMOTH
	_eManager->addEnemy(3680, 220, E_BEHEMOTH, true, NULL);
	_eManager->addEnemy(3793, 220, E_BEHEMOTH, true, NULL);
	//BASIL
	_eManager->addEnemy(210, 451, E_BASIL, true, NULL);
	//BEETLE
	_eManager->addEnemy(611, 348, E_BEETLE, true, NULL);
	_eManager->addEnemy(677, 259, E_BEETLE, false, NULL);
	_eManager->addEnemy(153, 316, E_BEETLE, true, NULL);
	_eManager->addEnemy(1187, 379, E_BEETLE, false, NULL);
	_eManager->addEnemy(1222, 316, E_BEETLE, true, NULL);
	_eManager->addEnemy(1673, 251, E_BEETLE, false, NULL);
	_eManager->addEnemy(1726, 282, E_BEETLE, true, NULL);
	_eManager->addEnemy(2146, 272, E_BEETLE, false, NULL);
	_eManager->addEnemy(2224, 348, E_BEETLE, true, NULL);
	_eManager->addEnemy(2236, 160, E_BEETLE, true, NULL);
	_eManager->addEnemy(2227, 125, E_BEETLE, false, NULL);
	_eManager->addEnemy(3132, 222, E_BEETLE, true, NULL);
	_eManager->addEnemy(3151, 279, E_BEETLE, false, NULL);
	_eManager->addEnemy(3282, 285, E_BEETLE, true, NULL);
	_eManager->addEnemy(3217, 348, E_BEETLE, false, NULL);
	_eManager->addEnemy(3232, 110, E_BEETLE, true, NULL);
	//BASU
	_eManager->addEnemy(2250, 95, E_BASU, true, NULL);
	_eManager->addEnemy(3600, 95, E_BASU, true, NULL);
	_eManager->addEnemy(4600, 95, E_BASU, true, NULL);
	//Zombie
	_eManager->addEnemy(675, 143, E_ZOMBIE, true, NULL);
	_eManager->addEnemy(1463, 175, E_ZOMBIE, true, NULL);
	_eManager->addEnemy(4000, 175, E_ZOMBIE, true, NULL);
	_eManager->addEnemy(4192, 207, E_ZOMBIE, true, NULL);
	_eManager->addEnemy(3418, 175, E_ZOMBIE, true, NULL);



	_player->setCurScene("eggHatchery2");
	_player->setPxlImg("Stage3Pxl");
	_player->SetLinkEnemy(_eManager);

	for (int i = 0; i < _player->getVWeapone().size(); i++)
	{
		_player->getVWeapone()[i]->LinkToEnemy(_eManager);
		_player->getVWeapone()[i]->setPxlImg("Stage3Pxl");
	}


	_ItemManager = new ItemManager;
	_ItemManager->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), "Stage3Pxl");
	_ItemManager->setPlayerLink(_player);

	_eManager->SetItemMemory(_ItemManager);

	_Inven = new Inventory;
	_Inven->init(_player->GetCamera()->getCamX(), _player->GetCamera()->getCamY());

	SOUNDMANAGER->stop("에그랩실");
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("Stage1Intro");
	SOUNDMANAGER->stop("보스브금");
	if (!SOUNDMANAGER->isPlaySound("Stage2"))
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

	_npc = new NpcEvent;
	_npc->setPlayerLink(_player);
	_npc->init();

	_bossRoomDoor;

	_ItemManager->SetKnife(396, 444);
	_ItemManager->SetMaxHeal(2700, 440, 3);//
	_ItemManager->SetRocketMaxUp(3524, 370,false);


	_ItemManager->SetRocketReload(4340, 23, false);
	_ItemManager->SetRocketReload(4300, 23, false);
	_ItemManager->SetRocketMaxUp(4480, 23, false);

	return S_OK;
}
void eggHatchery2::release()
{
	_eManager->release();
	SAFE_DELETE(_eManager);

}
void eggHatchery2::update()
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
			changescene = true;
			ChangeDcInAni->start();
			
		}
	}
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorSaveRoom1))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
			changescene2 = true;
			ChangeDcInAni->start();
		}
	}
	/*
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorBossRoom))
	{
	if (KEYMANAGER->isOnceDown(VK_DOWN))
	{
	_player->getPlayer()->setRect(RectMakeCenter(4282, 196, 25, 25));
	_player->GetCamera()->setCamPos();
	SCENEMANAGER->changeScene("보스룸");
	}
	}
	*/
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->getRect(), &doorSaveRoom2))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			if (ChangeDcInAni->isPlay() || ChangeDcOutAni->isPlay()) return;
			changescene3 = true;
			ChangeDcInAni->start();
		}
	}

	if (changescene && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(4282, 196, 25, 25));
		_player->GetCamera()->setCamPos();
		SCENEMANAGER->changeScene("eggHatchery");
	}
	else if (changescene2 && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(541, 336, 25, 25));
		_player->GetCamera()->setCamPos();
		//플레이어 들어가는 위치 저장

		_player->getPlayer()->_SaveStagestr = STAGE_EGG2;
		_player->SavePlayerPos(doorSaveRoom1.left + 10, doorSaveRoom1.top + 34);
		SCENEMANAGER->changeScene("eggLab");
	}
	else if (changescene3 && !ChangeDcInAni->isPlay())
	{
		_player->getPlayer()->setRect(RectMakeCenter(541, 336, 25, 25));
		_player->GetCamera()->setCamPos();
		_player->getPlayer()->_SaveStagestr = STAGE_EGG2;
		//플레이어 들어가는 위치 저장
		_player->SavePlayerPos(doorSaveRoom2.left + 10, doorSaveRoom2.top + 34);
		SCENEMANAGER->changeScene("eggLab");
	}
}
void eggHatchery2::render()
{
	//IMAGEMANAGER->findImage("background2_loop")->loopRender(getMemDC(), &RectMake(0, 0, 5262, WINSIZEY), loopx, 0);
	IMAGEMANAGER->findImage("background3")->render(getMemDC());
	_eManager->render();
	_player->render();
	_wce->render();
	
	_ItemManager->render();
	IMAGEMANAGER->findImage("background3_obj")->render(getMemDC());
	_npc->render();
	_player->uiRender();

	EFFECTMANAGER->render();
	_ItemManager->UIrender();

	if (ChangeDcInAni->isPlay()) {
		IMAGEMANAGER->findImage("ChangeDcIn")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcInAni);
	}
	if (ChangeDcOutAni->isPlay()) {
		IMAGEMANAGER->findImage("ChangeDcOut")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcOutAni);
	}

	if (IntersectRect(&RectMake(0, 0, 0, 0), &_player->getPlayer()->_rc, &_bossRoomDoor))
	{
		if (KEYMANAGER->isOnceDown(VK_DOWN))
		{
			if (viewAllEvent)
			{
				_player->getPlayer()->setRect(RectMakeCenter(87, 725, 25, 25));
				_player->GetCamera()->setCamPos();
				SCENEMANAGER->changeScene("boss");
			}
		}

	}
	
	//Rectangle(getMemDC(), doorExit.left, doorExit.top, doorExit.right, doorExit.bottom);
	//Rectangle(getMemDC(), doorSaveRoom1.left, doorSaveRoom1.top, doorSaveRoom1.right, doorSaveRoom1.bottom);
	//Rectangle(getMemDC(), doorBossRoom.left, doorBossRoom.top, doorBossRoom.right, doorBossRoom.bottom);
	//Rectangle(getMemDC(), doorSaveRoom2.left, doorSaveRoom2.top, doorSaveRoom2.right, doorSaveRoom2.bottom);
}

//void eggHatchery2::FrameUpdate()
//{
//
//	//프레임돌리자
//	count++;
//	SelectPoint1->setFrameY(0);
//	if (count % 10 == 0)
//	{
//
//		SelectPoint1->setFrameX(index);
//		index++;
//		if (index > SelectPoint1->getMaxFrameX())
//		{
//			index = 0;
//		}
//	}
//}

void eggHatchery2::Loop()
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