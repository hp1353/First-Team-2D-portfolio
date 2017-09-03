#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

//�ʱ�ȭ�� ���⼭ �Ѵ�
HRESULT gameStudy::init()
{
	gameNode::init(true);

	_TestScene = new TestScene;
	_eggHatchery = new eggHatchery;
	_stage0 = new stage0;
	_eggLab = new eggLab;
	_eggHatchery2 = new eggHatchery2;
	_bossRoom = new BossRoom;
	_endingScene = new endingScene;

	IMAGEMANAGER->addFrameImage("DamageNum", "image/UI/Number-.bmp", 0, 0, 176, 16, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PlusNum", "image/UI/Number+.bmp", 0, 0, 176, 16, 11, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("background0", "image/Map/Stage0_image.bmp", 640, 480, false, false);
	IMAGEMANAGER->addImage("Stage0Pxl", "image/Map/Stage0.bmp", 640, 480, false, false);

	IMAGEMANAGER->addImage("backgroundEggLab", "image/Map/eggLab_img.bmp", 640, 480, false, false);
	IMAGEMANAGER->addImage("StageEggLabPxl", "image/Map/eggLab.bmp", 640, 480, false, false);

	IMAGEMANAGER->addImage("background", "image/background.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("background1", "image/Map/Stage1_image.bmp", 1956, 1556, false, false);

	IMAGEMANAGER->addImage("background2", "image/Map/Stage2_img_3.bmp", 4335, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background3", "image/Map/Stage3_img_2.bmp", 5262, 480, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Stage1Pxl", "image/Map/Stage1.bmp", 1956, 1556, false, false);
	IMAGEMANAGER->addImage("Stage2Pxl", "image/Map/Stage2_2.bmp", 4335, 480, false, false);
	IMAGEMANAGER->addImage("Stage3Pxl", "image/Map/Stage3.bmp", 5262, 480, false, false);

	IMAGEMANAGER->addImage("background2_obj", "image/Map/Stage2_obj_2.bmp", 4335, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background3_obj", "image/Map/Stage3_obj.bmp", 5262, 480, true, RGB(255, 0, 255));
	//��������2 ����(20160628 �߰�)
	IMAGEMANAGER->addImage("background2_loop", "image/Map/Stage2_loop.bmp", 640, 480, false, false);

	//��������0 ��
	IMAGEMANAGER->addImage("stage0water", "image/Map/stage0water.bmp", 137, 38, true, RGB(255, 0, 255));

	//��������1 ��
	IMAGEMANAGER->addImage("stage1water", "image/Map/stage1water.bmp", 949, 108, true, RGB(255, 0, 255));

	//������ npc
	IMAGEMANAGER->addImage("character", "image/NpcEvent/character.bmp", 29, 28, true, RGB(255, 0, 255));
	//������ npc ������ ��� �̺�Ʈ �̹���
	IMAGEMANAGER->addImage("item", "image/NpcEvent/item.bmp", 180, 65, false, false);
	IMAGEMANAGER->addImage("itemtxt", "image/NpcEvent/itemtxt.bmp", 599, 144, false, false);

	//������ ������ npc
	IMAGEMANAGER->addImage("Mcharacter", "image/NpcEvent/machine.bmp", 36, 20, true, RGB(255, 0, 255));





	//�����̹���
	IMAGEMANAGER->addImage("ending", "image/ending.bmp", 640, 5200, false, false);

	//��������1 �����
	SOUNDMANAGER->addSound("Stage1", "sound/Stage1.ogg", true, true);
	SOUNDMANAGER->addSound("���׷���", "sound/eggLabBGM.ogg", true, true);
	SOUNDMANAGER->addSound("�������", "sound/BossBGM.ogg", true, true);

		SOUNDMANAGER->addSound("credits", "sound/credits.ogg");
	SOUNDMANAGER->addSound("Stage1Intro", "sound/Stage1Intro.ogg");

	SOUNDMANAGER->addSound("Stage2", "sound/Stage2.ogg", true, true);
	SOUNDMANAGER->addSound("Stage2Intro", "sound/Stage2Intro.ogg");

	SOUNDMANAGER->addSound("GetTextItem", "sound/GetTextItem.mp3");

	SOUNDMANAGER->addSound("WalkSound", "sound/WalkSound.wav");
	SOUNDMANAGER->addSound("Jump", "sound/Jump.wav");
	SOUNDMANAGER->addSound("����", "sound/����.wav");
	SOUNDMANAGER->addSound("�Ѿ˺��浹", "sound/�Ѿ˺��浹.wav");
	SOUNDMANAGER->addSound("MachineGun", "sound/MachineGun.wav");
	SOUNDMANAGER->addSound("FireBallWall", "sound/FireBallWall.wav");
	SOUNDMANAGER->addSound("DamagedSound", "sound/DamagedSound.wav");
	SOUNDMANAGER->addSound("MonsterFire", "sound/MonsterFire.wav");
	SOUNDMANAGER->addSound("MonsterBulletCollision", "sound/MonsterBulletCollision.wav");
	SOUNDMANAGER->addSound("����ġ ������ �ñ�� �Ҹ�", "sound/����ġ ������ �ñ�� �Ҹ�.wav");
	SOUNDMANAGER->addSound("���ͺ���", "sound/���ͺ���.wav");
	SOUNDMANAGER->addSound("MonsterBulletCollision", "sound/MonsterBulletCollision.wav");
	SOUNDMANAGER->addSound("critter_jump", "sound/critter_jump.wav");
	SOUNDMANAGER->addSound("breakableBox", "sound/breakableBox.wav");
	SOUNDMANAGER->addSound("Zet", "sound/Zet.wav");

	SOUNDMANAGER->addSound("enemy_block", "sound/enemy_block.wav");
	SOUNDMANAGER->addSound("enemy_hurtSmall", "sound/enemy_hurtSmall.wav");
	SOUNDMANAGER->addSound("enemy_hurt2", "sound/enemy_hurt2.wav");
	SOUNDMANAGER->addSound("enemy_hurt", "sound/enemy_hurt.wav");
	SOUNDMANAGER->addSound("enemy_death1", "sound/enemy_death.wav");
	SOUNDMANAGER->addSound("enemy_death2", "sound/enemy_death2.wav");
	SOUNDMANAGER->addSound("enemy_death3", "sound/enemy_death3.wav");

	SOUNDMANAGER->addSound("player_water", "sound/player_water.wav");
	SOUNDMANAGER->addSound("Ǯ��", "sound/fullHeal.wav");
	SOUNDMANAGER->addSound("��������", "sound/RocketBoom.wav");
	SOUNDMANAGER->addSound("�������߻�", "sound/LaserFire.wav");

	SOUNDMANAGER->addSound("����ġ����", "sound/����ġ����.wav");
	SOUNDMANAGER->addSound("�����۽���", "sound/�����۽���.wav");
	SOUNDMANAGER->addSound("ü��ȸ��", "sound/ü��ȸ��.wav");
	SOUNDMANAGER->addSound("��ȭ��", "sound/��ȭ��.wav");
	SOUNDMANAGER->addSound("����ü����", "sound/Weapone_Change.wav");
	SOUNDMANAGER->addSound("������", "sound/������.wav");
	SOUNDMANAGER->addSound("�����ٿ�", "sound/�����ٿ�.wav");
	
	SOUNDMANAGER->addSound("�÷��̾�����", "sound/player_death.wav");
	SOUNDMANAGER->addSound("��Ƽ", "sound/EmptySound.wav");
	SOUNDMANAGER->addSound("��3�Ҹ�", "sound/Knife3Sound.wav");

	SOUNDMANAGER->addSound("������", "sound/LaserCollect.wav");
	SOUNDMANAGER->addSound("������1", "sound/LaserCollect1.wav");
	SOUNDMANAGER->addSound("ZombieFire", "sound/ZombieFire.wav");



	SCENEMANAGER->addScene("TestScene", _TestScene);
	SCENEMANAGER->addScene("MainMenu", new MainMenu);
	SCENEMANAGER->addScene("eggHatchery", _eggHatchery);
	SCENEMANAGER->addScene("stage0", _stage0);
	SCENEMANAGER->addScene("eggLab", _eggLab);
	SCENEMANAGER->addScene("eggHatchery2", _eggHatchery2);
	SCENEMANAGER->addScene("boss", _bossRoom);
	SCENEMANAGER->addScene("blank", new blankScene);
	SCENEMANAGER->addScene("ending", _endingScene);

	_player = new Player;
	_player->init();

	_saveLoad = new SaveLoad;
	_saveLoad->setPlayerLink(_player);
	
	_TestScene->setPlayerMemory(_player);
	_eggHatchery->setPlayerMemory(_player);
	_stage0->setPlayerMemory(_player);
	_eggLab->setPlayerMemory(_player);
	_eggHatchery2->setPlayerMemory(_player);
	_bossRoom->setPlayerMemory(_player);

	IMAGEMANAGER->addImage("�⺻������Ʈ", "image/effect/BaseFireEffect.bmp", 128, 34, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("�⺻������Ʈ", "image/effect/BaseFireEffect.bmp", 128, 34, 32, 34, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("���浹����Ʈ", "image/effect/BaseGunCollision.bmp", 120, 30, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("���浹����Ʈ", "image/effect/BaseGunCollision.bmp", 120, 30, 30, 30, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("����", "image/effect/Dust.bmp", 224, 33, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("����", "image/effect/Dust.bmp", 224, 33, 32, 33, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("���� ����", "image/effect/RedDust.bmp", 224, 32, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("���� ����", "image/effect/RedDust.bmp", 224, 32, 32, 32, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("���Ѿ��浹", "image/effect/EnemyMissileCollision.bmp", 128, 30, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("���Ѿ��浹", "image/effect/EnemyMissileCollision.bmp", 128, 30, 32, 30, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("����ǥ", "image/effect/����ǥ.bmp", 17, 18, TRUE, RGB(255, 0, 255));
	//EFFECTMANAGER->addEffect("����ǥ", "image/effect/����ǥ.bmp", 17, 18, 17, 18, 30, 1.0f, 100);

	IMAGEMANAGER->addImage("Empty", "image/effect/Empty.bmp", 750, 16, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Empty", "image/effect/Empty.bmp", 750, 16, 75, 16, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("LevelDown", "image/effect/LevelDown.bmp", 1120, 22, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("LevelDown", "image/effect/LevelDown.bmp", 1120, 22, 112, 22, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("LevelUp", "image/effect/LevelUp.bmp", 1568, 26, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("LevelUp", "image/effect/LevelUp.bmp", 1568, 26, 112, 26, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("RocketSmoke", "image/effect/RocketSmoke.bmp", 84, 12, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("RocketSmoke", "image/effect/RocketSmoke.bmp", 84, 12, 12, 12, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("Boom", "image/effect/Boom.bmp", 128, 64, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Boom", "image/effect/Boom.bmp", 128, 64, 64, 64, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("Knife3Effect1", "image/effect/Knife3Effect1.bmp", 240, 48, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Knife3Effect1", "image/effect/Knife3Effect1.bmp", 240, 48, 48, 48, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("Knife3Effect2", "image/effect/Knife3Effect2.bmp", 240, 48, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("Knife3Effect2", "image/effect/Knife3Effect2.bmp", 240, 48, 48, 48, 1, 0.3f, 100);

	IMAGEMANAGER->addImage("FireLv2", "image/effect/FireLv2.bmp", 216, 24, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("FireLv2", "image/effect/FireLv2.bmp", 216, 24, 24, 24, 40, 0.3f, 100);

	IMAGEMANAGER->addImage("FireLv3", "image/effect/FireLv3.bmp", 216, 24, TRUE, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("FireLv3", "image/effect/FireLv3.bmp", 216, 24, 24, 24, 40, 0.3f, 100);



	IMAGEMANAGER->addFrameImage("SaveDiscket", "image/Iteam/SaveDiscket.bmp", 256, 33, 8, 1, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("FullHeal", "image/Iteam/FullHeal.bmp", 56, 33, 2, 1, true, 0xff00ff);

	SCENEMANAGER->changeScene("MainMenu");

	IMAGEMANAGER->addFrameImage("ChangeDcIn", "image/effect/ChangeDcIn.bmp", 7680, 480, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ChangeDcOut", "image/effect/ChangeDcOut.bmp", 7680, 480, 12, 1, true, RGB(255, 0, 255));
	///////////////////////////////////////////////
	ChangeDcInAni = new animation;
	ChangeDcInAni->init(IMAGEMANAGER->findImage("ChangeDcIn")->getWidth(), IMAGEMANAGER->findImage("ChangeDcIn")->getHeight(), 640, 480);
	ChangeDcInAni->setDefPlayFrame(false, false);
	ChangeDcInAni->setFPS(15);
	///////////////////////////////////////////////
	_DeadCount = false;
	//_test = new cameraAngle;
	//_test->init();

	return S_OK;
}

//�޸� ������ ���⼭
void gameStudy::release()
{
	//_test->release();
	SAFE_DELETE(ChangeDcInAni);
	gameNode::release();
}

//��� ���� �ݺ� �Ǿ�� �� �͵� ���⼭
void gameStudy::update()
{
	ChangeDcInAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	/*if (KEYMANAGER->isOnceDown('1'))
	{
		_saveLoad->Save();
	}*/
	if (_player->getPlayer()->_isDie && !_DeadCount)
	{
		ChangeDcInAni->start();
		_DeadCount = true;
	}
	if (_DeadCount && !ChangeDcInAni->isPlay())
	{
		_player->setInvulOff();
		_player->getPlayer()->_iscrush = false;
		_player->setDmgCountOff();
		_player->getPlayer()->_knockBack = 0.f;

		_player->getPlayer()->_isWater = false;
		_player->getPlayer()->_isDrown = false;
		_player->getPlayer()->_air = 100;
		_player->getPlayer()->_motion = IDLE;
		_DeadCount = false;
		SCENEMANAGER->changeScene("blank");
		_saveLoad->Load();
	}

	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	SOUNDMANAGER->update();

	

	//_test->update();
	gameNode::update();
}

//�׷��ִ� �� ���⼭
void gameStudy::render()
{
	//��� ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===============================================
	IMAGEMANAGER->findImage("background")->render(getMemDC());


	SCENEMANAGER->render();


	if (ChangeDcInAni->isPlay()) {
		IMAGEMANAGER->findImage("ChangeDcIn")->aniRender(getMemDC(), _player->GetCamera()->getCamX(), _player->GetCamera()->getCamY(), ChangeDcInAni);
	}

	//===============================================
	//����ۿ� �ִ� ������ HDC�� �׸���.
	//TIMEMANAGER->render(getMemDC());

	if (SCENEMANAGER->CurrentScene("TestScene") || SCENEMANAGER->CurrentScene("eggHatchery") || SCENEMANAGER->CurrentScene("stage0") || SCENEMANAGER->CurrentScene("eggLab") || SCENEMANAGER->CurrentScene("eggHatchery2") || SCENEMANAGER->CurrentScene("boss"))
		this->getBackBuffer()->render(getHDC(), 0, 0, _TestScene->GetPlayer()->GetCamera()->getCamX(), _TestScene->GetPlayer()->GetCamera()->getCamY(), WINSIZEX, WINSIZEY);
	else
		this->getBackBuffer()->render(getHDC(), 0, 0);

}

