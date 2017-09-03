#include "stdafx.h"
#include "boss.h"

//
//boss::boss()
//{
//}
//
//
//boss::~boss()
//{
//}


//HRESULT boss::init()
//{
//	IMAGEMANAGER->addImage("stage_finalBack",   "image/stage_finalBack.bmp", 1088, 898, true, 0xff00ff);
//	IMAGEMANAGER->addImage("stage_finalFront",  "image/stage_finalFront.bmp", 1088, 898, true, 0xff00ff);
//	IMAGEMANAGER->addImage("stage_finalWall",   "image/stage_finalWall.bmp", 1088, 898, false, false);
//	IMAGEMANAGER->addImage("stage_finalPixel",  "image/stage_finalPixel.bmp", 1088, 898, false, false);
//
//	IMAGEMANAGER->addImage("boss_body",         "image/boss_body.bmp", 240, 240, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_bodyHit",      "image/boss_bodyHit.bmp", 240, 240, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_body2",        "image/boss_body2.bmp", 240, 240, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_body3",        "image/boss_body3.bmp", 240, 240, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_body3Hit",     "image/boss_body3Hit.bmp", 240, 240, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_wood",         "image/boss_wood.bmp", 64, 22, true, 0xff00ff);
//	IMAGEMANAGER->addImage("spike",             "image/spike.bmp", 961, 47, true, 0xff00ff);
//	IMAGEMANAGER->addImage("effect_blood",      "image/effect_blood.bmp", 12, 12, true, 0xff00ff);
//											    
//											    
//	IMAGEMANAGER->addImage("boss_bollBtm",      "image/boss_bollBtm.bmp", 78, 78, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_bollTop",      "image/boss_bollTop.bmp", 78, 78, true, 0xff00ff);
//	IMAGEMANAGER->addImage("boss_bollHit",      "image/boss_bollHit.bmp", 78, 78, true, 0xff00ff);
//	IMAGEMANAGER->addImage("effect_skul",       "image/effect_skul.bmp", 128, 32, true, 0xff00ff);
//	IMAGEMANAGER->addImage("effect_pop",        "image/effect_pop.bmp", 128, 32, true, 0xff00ff);
//	IMAGEMANAGER->addImage("effect_bones",      "image/effect_bones.bmp", 128, 32, true, 0xff00ff);
//	EFFECTMANAGER->init();					    
//	EFFECTMANAGER->addEffect("effect_dust",     "image/effect_dust.bmp", 231, 33, 33, 33, 1, 0.4f, 8);
//	EFFECTMANAGER->addEffect("effect_dustPop",  "image/effect_dust.bmp", 231, 33, 33, 33, 1, 0.4f, 20);
//	EFFECTMANAGER->addEffect("effect_dustBig",  "image/effect_dust2.bmp", 462, 66, 66, 66, 1, 0.3f, 4);
//	EFFECTMANAGER->addEffect("effect_dustUP",   "image/effect_dustUP.bmp", 231, 33, 33, 33, 1, 0.28f, 8);
//	EFFECTMANAGER->addEffect("effect_bossPop",  "image/effect_bossPop.bmp", 2002, 285, 286, 285, 1, 0.28f, 1);
//
//	_rc = RectMakeCenter(BOSSCENTERX / 2, BOSSCENTERY / 2 + 100, 240, 240);
//	_headRc = RectMakeCenter(BOSSCENTERX / 2, BOSSCENTERY / 2, 200, 30);
//	_movingRc = RectMakeCenter(BOSSCENTERX / 2, BOSSCENTERY / 2 + 100, 400, 400);
//	_img = IMAGEMANAGER->findImage("boss_body");
//	_radius = BOSSRADIUS;
//	_angle = PI / 2 + PI16;
//	_x = _bossBody.rc.left + (_bossBody.rc.right - _bossBody.rc.left) / 2;
//	_y = _bossBody.rc.top + (_bossBody.rc.bottom - _bossBody.rc.top) / 2;
//	_speed = 3.0f;
//	_motion = BOSSGROUND;
//	_power = 12.f;
//	_gravity = 0.f;
//	_jumpCount = 0;
//
//
//	for (float i = 0; i < PI2 - PI / 4; i += PI / 4) // 플롯으로 
//	{
//		_BossBall = new BossBall;
//		_BossBall->init(_x + cosf(i) * 10, _y + -sinf(i) * 10, i);
//
//		_vBossBall.push_back(_BossBall);
//	}
//
//
//	for (float i = 0; i < 2 * PI; i += PI / 4) // 플롯으로 
//	{
//		tagBossBoll* wood = new tagBossBoll;
//		ZeroMemory(wood, sizeof(tagBossBoll));
//		wood->rc = RectMakeCenter(_bossBody.x + cosf(i) * 40, _bossBody.y + -sinf(i) * 40, 64, 22);
//		//괄호 안에 10, 10은 거리비례를 나타냄
//		//원중심 탄환은 이걸 기준으로 하면 됨
//		wood->angle = i;
//		wood->x = wood->rc.left + (wood->rc.right - wood->rc.left) / 2;
//		wood->y = wood->rc.top + (wood->rc.bottom - wood->rc.top) / 2;
//		wood->speed = 0.5f;
//
//		_vBossWood.push_back(wood);
//	}
//
//
//	for (int i = 0; i < 8; i++)
//	{
//		tagBossBoll* skull = new tagBossBoll;
//		ZeroMemory(skull, sizeof(tagBossBoll));
//		skull->rc = RectMakeCenter((BOSSCENTERX * 2) + 32, (BOSSCENTERY * 2) + 32, 32, 32);
//		skull->x = skull->rc.left + (skull->rc.right - skull->rc.left) / 2;
//		skull->y = skull->rc.top + (skull->rc.bottom - skull->rc.top) / 2;
//		skull->img = IMAGEMANAGER->findImage("effect_skul");
//		skull->speed = 5.0f;
//		skull->fire = false;
//		skull->ani = new animation;
//		skull->ani->init(skull->img->getWidth(), skull->img->getHeight(), 32, 32);
//		skull->ani->setDefPlayFrame(false, true);
//		skull->ani->setFPS(10);
//		skull->ani->start();
//
//		_vBossSkull.push_back(skull);
//	}
//
//	for (int i = 0; i < 20; i++)
//	{
//		tagBoss* pops = new tagBoss;
//		ZeroMemory(pops, sizeof(tagBoss));
//		//skull->rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32, 32);
//		pops->x = pops->rc.left + (pops->rc.right - pops->rc.left) / 2;
//		pops->y = pops->rc.top + (pops->rc.bottom - pops->rc.top) / 2;
//		pops->img = IMAGEMANAGER->findImage("effect_bones");
//		pops->angle = PI - PI / 5;
//		pops->speed = RND->getFromFloatTo(4.3f, 4.6f);
//		pops->power = 0.4f;
//		pops->gravity = 0.f;
//		pops->motion = BOSSGROUND;
//		pops->fire = false;
//
//		pops->ani = new animation;
//		pops->ani->init(pops->img->getWidth(), pops->img->getHeight(), 32, 32);
//		pops->ani->setDefPlayFrame(false, true);
//		pops->ani->setFPS(10);
//		pops->ani->start();
//
//		_vBossPops.push_back(pops);
//	}
//	
//	for (int i = 0; i < 5; i++)
//	{
//		tagRect* blood = new tagRect;
//		ZeroMemory(blood, sizeof(tagRect));
//		blood->rc = RectMakeCenter(BOSSCENTERX, BOSSCENTERY * 2, 12, 12);
//		blood->x = blood->rc.left + (blood->rc.right - blood->rc.left) / 2;
//		blood->y = blood->rc.top + (blood->rc.bottom - blood->rc.top) / 2;
//		blood->img = IMAGEMANAGER->findImage("effect_blood");
//		blood->turnOn = false;
//		blood->speed = RND->getFromFloatTo(3.0f, 4.5f);
//
//		_vBlood.push_back(blood);
//	}
//
//
//
//	_spike.rc = RectMakeCenter(BOSSCENTERX, BOSSCENTERY * 2, 961, 47);
//	_spike.y = _spike.rc.top + (_spike.rc.bottom - _spike.rc.top) / 2;
//	_spike.img = IMAGEMANAGER->findImage("spike");
//	_spike.count = 0;
//
//	_bossCount = 0;
//	_bossWoodPop = 0;
//
//	_testRc.rc = RectMakeCenter(0, 0, 30, 30);
//
//	return S_OK;
//}
//
//void boss::release()
//{
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//		SAFE_DELETE((*_viBossBoll));
//	}
//	_vBossBoll.clear();
//}
//
//void boss::update()
//{
//	//지울 것
//	_testRc.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 30, 30);
//
//	EFFECTMANAGER->update();
//
//	_bossBody.rc = RectMakeCenter(_bossBody.x, _bossBody.y, 240, 240);
//	_bossBody.movingRc = RectMakeCenter(_bossBody.x, _bossBody.y, 380, 380);
//	_bossBody.headRc = RectMakeCenter(_bossBody.x, _bossBody.y - 85, 120, 30);
//
//	if (KEYMANAGER->isOnceDown(VK_UP))
//	{
//		
//		_stageNum++;
//	}
//
//
//		switch (_stageNum)
//		{
//		case 0:bossStageOne();
//			break;
//		case 1:bossStageTwo();
//			break;
//		case 2:bossStageThree();
//			break;
//		default:  _stageNum = 0;
//			break;
//		}
//
//	
//	
//}
//
//void boss::render()
//{
//	IMAGEMANAGER->findImage("stage_finalWall")->render(getMemDC());
//	IMAGEMANAGER->findImage("stage_finalBack")->render(getMemDC(), 0, 0);
//
//
//	//지울것
//	Rectangle(getMemDC(), _testRc.rc.left, _testRc.rc.top, _testRc.rc.right, _testRc.rc.bottom);
//
//	switch (_stageNum)
//	{
//	case 0:
//		bossStageOneRender();
//		break;
//	case 1:bossStageTwoRender();
//		break;
//	case 2:bossStageThreeRender();
//		break;
//	default: _stageNum = 0;
//		break;
//	}
//
//	_bossBody.img->render(getMemDC(), _bossBody.rc.left, _bossBody.rc.top);
//
//	
//	for (_viBlood = _vBlood.begin(); _viBlood != _vBlood.end(); ++_viBlood)
//	{
//		if ((*_viBlood)->turnOn)
//		{
//			(*_viBlood)->img->render(getMemDC(), (*_viBlood)->rc.left, (*_viBlood)->rc.top);
//		}
//	}
//
//	EFFECTMANAGER->render();
//
//
//	IMAGEMANAGER->findImage("stage_finalFront")->render(getMemDC(), 0, 0);
//	
//	//Rectangle(getMemDC(), _bossBody.headRc.left, _bossBody.headRc.top, _bossBody.headRc.right, _bossBody.headRc.bottom);
//}
//
////=============보스 패턴 1에 대한 함수=============
//
//void boss::bossHeadCollision()
//{
//	if (IntersectRect(&RectMake(0, 0, 0, 0), &_bossBody.headRc, &_testRc.rc));
//	{
//		//_testRc.rc = RectMakeCenter(WINSIZEX / 2, _bossBody.headRc.top, 30, 30);
//	}
//	
//
//	
//}
//
//void boss::bossJump()
//{
//
//	_bossBody.rc = RectMakeCenter(_bossBody.x, _bossBody.y, 240, 240);
//
//	float distance = MY_UTIL::getDistance(_bossBody.x, _bossBody.y, _ptMouse.x, _ptMouse.y);
//
//	if (abs(distance) < 1000)
//	{
//		if (_bossBody.motion != BOSSJUMP)
//		{
//			if (_ptMouse.x < _bossBody.x)
//			{
//				_bossBody.angle = PI / 2 + PI16;
//			}
//			else
//			{
//				_bossBody.angle = PI / 2 - PI16;
//			}
//
//			if (abs(distance) < 1000)
//			{
//				if (_bossBody.motion != BOSSJUMP)
//				{
//					_bossBody.motion = BOSSGROUND;
//				}
//			}
//			else
//			{
//
//			}
//		}
//	}
//
//
//	if (_bossBody.jumpCount > 10)
//	{
//		_bossBody.motion = BOSSJUMP;
//		_bossBody.jumpCount = 0;
//	}
//	else if (_bossBody.motion == BOSSGROUND)
//	{
//		_bossBody.jumpCount++;
//		_bossBody.motion = BOSSGROUND;
//
//	}
//
//	if (_bossBody.motion == BOSSJUMP)
//	{
//		_bossBody.gravity += 0.3f;
//		_bossBody.x += cosf(_bossBody.angle) * (_bossBody.power);
//		_bossBody.y += -sinf(_bossBody.angle) * (_bossBody.power - _bossBody.gravity);
//	}
//
//
//}
//
//void boss::bossJumpCollision()
//{
//
//	image* pxlImg = IMAGEMANAGER->findImage("stage_finalPixel");
//
//	//충돌검사
//	if (IntersectRect(&RectMake(0, 0, 0, 0), &_bossBody.rc, &_testRc.rc))
//	{
//		_bossBody.collision = true;
//	}
//	else _bossBody.collision = false;
//
//
//	//아래쪽 검사
//	for (int i = _bossBody.y; i < _bossBody.rc.bottom; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), _bossBody.x, i);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.motion = BOSSGROUND;
//			_bossBody.gravity = 0.f;
//			_bossBody.y = i - 240 / 2;
//			EFFECTMANAGER->play("effect_dustBig", _bossBody.x - 45, _bossBody.y + 100);
//			EFFECTMANAGER->play("effect_dustBig", _bossBody.x + 45, _bossBody.y + 100);
//			EFFECTMANAGER->play("effect_dust", _bossBody.x - 80, _bossBody.y + 100);
//			EFFECTMANAGER->play("effect_dust", _bossBody.x + 80, _bossBody.y + 100);
//
//			popsFire(_bossBody.x);
//			break;
//		}
//	}
//
//
//
//	// 왼쪽 검사
//	for (int i = _bossBody.rc.left; i < _bossBody.x; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _bossBody.y);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.angle -= PI;
//			_bossBody.motion = BOSSUP;
//			_bossBody.x = i + 240 / 2 + 1;
//			break;
//		}
//	}
//
//	// 오른쪽 검사
//	for (int i = _bossBody.x; i < _bossBody.rc.right; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _bossBody.y);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.angle -= PI;
//			_bossBody.motion = BOSSDOWN;
//			_bossBody.x = i - 240 / 2 - 1;
//			break;
//		}
//	}
//}
//
//void boss::popsFire(int fireX)
//{
//	for (int i = 0; i < _vBossPops.size(); i++)
//	{
//
//
//		if (_vBossPops[i]->fire) return;
//		_vBossPops[i]->fire = true;
//		_vBossPops[i]->x = fireX + (RND->getFromIntTo(5, 100));
//		_vBossPops[i]->y = _bossBody.y + 90 + (RND->getFromIntTo(0, 30));
//		_vBossPops[i]->rc = RectMakeCenter(_vBossPops[i]->x, _vBossPops[i]->y, 32, 32);
//	}
//
//
//}
//
//void boss::popsMove()
//{
//
//	for (int i = 0; i < 5; i++)
//	{
//		_vBossPops[i]->ani->frameUpdate(TIMEMANAGER->getElapsedTime());
//
//		_vBossPops[i]->x -= _vBossPops[i]->speed;
//
//
//		_vBossPops[i]->rc = RectMakeCenter(_vBossPops[i]->x, _vBossPops[i]->y, 32, 32);
//
//
//	}
//
//	for (int i = 5; i < 10; i++)
//	{
//		_vBossPops[i]->speed = 5.5f;
//		_vBossPops[i]->img = IMAGEMANAGER->findImage("effect_pop");
//		_vBossPops[i]->ani->frameUpdate(TIMEMANAGER->getElapsedTime());
//
//		_vBossPops[i]->x -= _vBossPops[i]->speed;
//
//
//		_vBossPops[i]->rc = RectMakeCenter(_vBossPops[i]->x, _vBossPops[i]->y, 32, 32);
//
//
//	}
//
//	for (int i = 10; i < 15; i++)
//	{
//
//
//		_vBossPops[i]->ani->frameUpdate(TIMEMANAGER->getElapsedTime());
//
//		_vBossPops[i]->x += _vBossPops[i]->speed;
//
//
//		_vBossPops[i]->rc = RectMakeCenter(_vBossPops[i]->x, _vBossPops[i]->y, 32, 32);
//
//	}
//
//	for (int i = 15; i < _vBossPops.size(); i++)
//	{
//		_vBossPops[i]->speed = 5.5f;
//		_vBossPops[i]->img = IMAGEMANAGER->findImage("effect_pop");
//		_vBossPops[i]->ani->frameUpdate(TIMEMANAGER->getElapsedTime());
//
//		_vBossPops[i]->x += _vBossPops[i]->speed;
//
//
//		_vBossPops[i]->rc = RectMakeCenter(_vBossPops[i]->x, _vBossPops[i]->y, 32, 32);
//
//
//	}
//
//
//	for (int i = 0; i < 10; i++)
//	{
//		if (_vBossPops[i]->x < 0)
//		{
//			_vBossPops[i]->fire = false;
//		}
//
//	}
//
//	for (int i = 10; i < _vBossPops.size(); i++)
//	{
//		if (_vBossPops[i]->x > (BOSSCENTERY*2))
//		{
//			_vBossPops[i]->fire = false;
//		}
//
//	}
//}
//
//
////=============보스 패턴 2에 대한 함수=============
//
//void boss::collision()
//{
//
//	image* pxlImg = IMAGEMANAGER->findImage("stage_finalPixel");
//
//	//아래쪽 검사
//	for (int i = _bossBody.y; i < _bossBody.movingRc.bottom; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), _bossBody.x, i);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.motion = BOSSLEFT;
//			_bossBody.y = _bossBody.y - 3;
//			break;
//		}
//	}
//
//	// 위쪽 검사
//	for (int i = _bossBody.movingRc.top; i < _bossBody.y; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), _bossBody.x, i);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.motion = BOSSRIGHT;
//			_bossBody.y = _bossBody.y + 3;
//			break;
//		}
//	}
//
//	// 왼쪽 검사
//	for (int i = _bossBody.movingRc.left; i < _bossBody.x; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _bossBody.y);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.motion = BOSSUP;
//			_bossBody.x = _bossBody.x + 3;
//			break;
//		}
//	}
//
//	// 오른쪽 검사
//	for (int i = _bossBody.x; i < _bossBody.movingRc.right; i++)
//	{
//		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _bossBody.y);
//
//		if (color == 0x00ff00)
//		{
//			_bossBody.motion = BOSSDOWN;
//			_bossBody.x = _bossBody.x - 3;
//			break;
//		}
//	}
//}
//
//void boss::move()
//{
//	switch (_bossBody.motion)
//	{
//	case BOSSUP:
//		_bossBody.y -= _bossBody.speed;
//		break;
//	case BOSSDOWN:
//		_bossBody.y += _bossBody.speed;
//		break;
//	case BOSSLEFT:
//		_bossBody.x -= _bossBody.speed;
//		break;
//	case BOSSRIGHT:
//		_bossBody.x += _bossBody.speed;
//		break;
//	default:_bossBody.x -= _bossBody.speed;
//		break;
//	}
//
//}
//
//void boss::bollCollision()
//{
//	int count = 0;
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//
//		//사각형 충돌 검사
//		if (IntersectRect(&RectMake(0, 0, 0, 0), &_testRc.rc, &(*_viBossBoll)->rc))
//		{
//			(*_viBossBoll)->collision = true;
//		}
//		else  (*_viBossBoll)->collision = false;
//
//
//		image* pxlImg = IMAGEMANAGER->findImage("stage_finalPixel");
//
//		//아래쪽 검사
//		for (int i = (*_viBossBoll)->y; i < (*_viBossBoll)->rc.bottom; i++)
//		{
//			COLORREF color = GetPixel(pxlImg->getMemDC(), (*_viBossBoll)->x, i);
//
//			if (color == 0x00ff00)
//			{
//				EFFECTMANAGER->play("effect_dustBig", (*_viBossBoll)->x + 40, (*_viBossBoll)->y + 45);
//				EFFECTMANAGER->play("effect_dustBig", (*_viBossBoll)->x - 40, (*_viBossBoll)->y + 45);
//
//				EFFECTMANAGER->play("effect_dust", (*_viBossBoll)->x + 27, (*_viBossBoll)->y + 10);
//				EFFECTMANAGER->play("effect_dust", (*_viBossBoll)->x - 27, (*_viBossBoll)->y + 10);
//
//
//
//				break;
//			}
//		}
//
//		//위쪽 검사
//		for (int i = (*_viBossBoll)->rc.top; i < (*_viBossBoll)->y; i++)
//		{
//			COLORREF color = GetPixel(pxlImg->getMemDC(), (*_viBossBoll)->x, i);
//
//			if (color == 0x00ff00)
//			{
//
//
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x + 50, (*_viBossBoll)->y - 20);
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x - 50, (*_viBossBoll)->y - 20);
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x + 27, (*_viBossBoll)->y - 40);
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x - 27, (*_viBossBoll)->y - 40);
//
//				if (count < _vBossSkull.size()) {
//					skullDrop(count, (*_viBossBoll)->x);
//				}
//				//for (_viBossSkull = _vBossSkull.begin(); _viBossSkull != _vBossSkull.end(); ++_viBossSkull)
//				//{
//				//	
//				//	
//				//	if ((*_viBossSkull)->fire) break;
//
//				//	skullDrop((*_viBossBoll)->x);
//				//	
//				//
//				//}
//
//
//			}
//		}
//		count++;
//
//		//오른쪽 검사
//		for (int i = (*_viBossBoll)->x; i < (*_viBossBoll)->rc.right; i++)
//		{
//			COLORREF color = GetPixel(pxlImg->getMemDC(), i, (*_viBossBoll)->y);
//
//			if (color == 0x00ff00)
//			{
//				EFFECTMANAGER->play("effect_dustBig", (*_viBossBoll)->x + 35, (*_viBossBoll)->y);
//
//				EFFECTMANAGER->play("effect_dust", (*_viBossBoll)->x + 25, (*_viBossBoll)->y - 35);
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x + 30, (*_viBossBoll)->y + 35);
//
//				break;
//			}
//		}
//
//		//왼쪽 검사
//		for (int i = (*_viBossBoll)->rc.left; i < (*_viBossBoll)->x; i++)
//		{
//			COLORREF color = GetPixel(pxlImg->getMemDC(), i, (*_viBossBoll)->y);
//
//			if (color == 0x00ff00)
//			{
//				EFFECTMANAGER->play("effect_dustBig", (*_viBossBoll)->x - 35, (*_viBossBoll)->y);
//
//				EFFECTMANAGER->play("effect_dust", (*_viBossBoll)->x - 25, (*_viBossBoll)->y - 35);
//				EFFECTMANAGER->play("effect_dustUP", (*_viBossBoll)->x - 30, (*_viBossBoll)->y + 35);
//
//				break;
//			}
//		}
//
//
//
//
//
//	}
//
//}
//
//void boss::skullDrop(int arrNum, int fireX)
//{
//	if (_vBossSkull[arrNum]->fire) return;
//	_vBossSkull[arrNum]->fire = true;
//	_vBossSkull[arrNum]->x = fireX;
//	_vBossSkull[arrNum]->y = 0;
//	_vBossSkull[arrNum]->rc = RectMakeCenter(_vBossSkull[arrNum]->x, _vBossSkull[arrNum]->y, 32, 32);
//
//	//for (_viBossSkull = _vBossSkull.begin(); _viBossSkull != _vBossSkull.end(); ++_viBossSkull)
//	//{
//	//	if ((*_viBossSkull)->fire) continue;
//	//	(*_viBossSkull)->fire = true;
//	//	(*_viBossSkull)->x = fireX;
//	//	(*_viBossSkull)->y = 0;
//	//	(*_viBossSkull)->rc = RectMakeCenter((*_viBossSkull)->x, (*_viBossSkull)->y, 32, 32);
//	//	
//	//	break;
//	//}
//
//
//
//}
//
//void boss::skullMove()
//{
//
//
//	for (_viBossSkull = _vBossSkull.begin(); _viBossSkull != _vBossSkull.end(); ++_viBossSkull)
//	{
//		(*_viBossSkull)->ani->frameUpdate(TIMEMANAGER->getElapsedTime());
//
//		if (!(*_viBossSkull)->fire) continue;
//
//		(*_viBossSkull)->y += (*_viBossSkull)->speed;
//		(*_viBossSkull)->rc = RectMakeCenter((*_viBossSkull)->x, (*_viBossSkull)->y, 32, 32);
//		//EFFECTMANAGER->play("effect_dustBig", (*_viBossSkull)->x, (*_viBossSkull)->y - 10);
//		//EFFECTMANAGER->play("effect_dust", (*_viBossSkull)->x, (*_viBossSkull)->y - 15);
//		//EFFECTMANAGER->play("effect_dust", (*_viBossSkull)->x, (*_viBossSkull)->y - 40);
//		//EFFECTMANAGER->play("effect_dust", (*_viBossSkull)->x, (*_viBossSkull)->y - 80);
//		//EFFECTMANAGER->play("effect_dust", (*_viBossSkull)->x, (*_viBossSkull)->y - 100);
//
//		if ((*_viBossSkull)->y >  (BOSSCENTERY*2))
//		{
//			(*_viBossSkull)->y = 40;
//			(*_viBossSkull)->fire = false;
//		}
//
//	}
//}
//
////=============보스 패턴 3에 대한 함수=============
//
//
//void boss::bossWheelMove()
//{
//	
//	_spike.rc = RectMakeCenter(BOSSCENTERX, _spike.y , 961, 47);
//
//	_bossBody.img = IMAGEMANAGER->findImage("boss_body");
//
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//		(*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollBtm");
//	}
//
//
//	float bossDis = MY_UTIL::getDistance(_bossBody.x, _bossBody.y, BOSSCENTERX, BOSSCENTERY - 50);
//
//	if (_bossBody.x < BOSSCENTERX)	_bossBody.x++;
//	
//	if (_bossBody.x >  BOSSCENTERX)	_bossBody.x--;
//
//	if (_bossBody.y >  BOSSCENTERY - 50) _bossBody.y--;
//
//	if (_bossBody.y <  BOSSCENTERY - 50)	_bossBody.y++;
//
//
//	if (abs(bossDis) <= 3 )
//	{
//	
//
//		_bossCount++;
//
//
//		for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//		{
//			(*_viBossBoll)->angle += 0.03f;
//			_bossWoodPop++;
//			if (_spike.y > BOSSCENTERY + 265) _spike.y--;
//
//
//		    if (_bossCount >= 300) // 5초 이상이 되면
//		    {
//				
//		    	(*_viBossBoll)->angle -= 0.03f;
//		    	_bossBody.img = IMAGEMANAGER->findImage("boss_body3");
//
//				(*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollTop");
//
//				if (_bossBody.collision == true) _bossBody.img = IMAGEMANAGER->findImage("boss_body3Hit");
//
//				if ((*_viBossBoll)->collision == true) (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollHit");
//				else (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollTop");
//
//				for (int i = 0; i < _vBlood.size(); i++)
//				{
//					if (!_vBlood[i]->turnOn)
//					{
//						_vBlood[i]->x = _bossBody.x - 100 + (i * 40);
//						_vBlood[i]->y = _bossBody.y + RND->getFromIntTo(10, 100), 12, 12;
//					}
//
//				
//					_vBlood[i]->turnOn = true;
//
//					
//				}
//		    
//		    }
//
//		}
//
//
//	}
//
//
//	for (_viBlood = _vBlood.begin(); _viBlood != _vBlood.end(); ++_viBlood)
//	{
//		if ((*_viBlood)->turnOn)
//		{
//			(*_viBlood)->rc = RectMakeCenter((*_viBlood)->x, (*_viBlood)->y, 12, 12);
//			(*_viBlood)->y += (*_viBlood)->speed;
//
//			if ((*_viBlood)->y > (BOSSCENTERY * 2))
//			{
//				(*_viBlood)->y = _bossBody.y + RND->getFromIntTo(10, 100), 12, 12;
//			}
//		}
//		
//
//	}
//
//
//	for (_viBossWood = _vBossWood.begin(); _viBossWood != _vBossWood.end(); ++_viBossWood)
//	{
//		if (_bossWoodPop >= 230) _bossWoodPop = 230;
//		(*_viBossWood)->angle += 0.005f;
//		(*_viBossWood)->x = _bossBody.x + cosf((*_viBossWood)->angle) * _bossWoodPop;
//		(*_viBossWood)->y = _bossBody.y + -sinf((*_viBossWood)->angle) * _bossWoodPop;
//		(*_viBossWood)->rc = RectMakeCenter((*_viBossWood)->x, (*_viBossWood)->y, 64, 22);
//
//	}
//
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//		(*_viBossBoll)->angle += 0.03f;
//
//		(*_viBossBoll)->x = _bossBody.x + cosf((*_viBossBoll)->angle) * 160;
//		(*_viBossBoll)->y = _bossBody.y + -sinf((*_viBossBoll)->angle) * 160;
//		(*_viBossBoll)->rc = RectMakeCenter((*_viBossBoll)->x, (*_viBossBoll)->y, 78, 78);
//
//	}
//
//
//
//}
//
//void boss::bossWheelCollision()
//{
//	//볼 충돌
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//
//		//사각형 충돌 검사
//		if (IntersectRect(&RectMake(0, 0, 0, 0), &_testRc.rc, &(*_viBossBoll)->rc))
//		{
//			(*_viBossBoll)->collision = true;
//		}
//		else  (*_viBossBoll)->collision = false;
//	}
//
//
//	//판대기 충돌
//	if (IntersectRect(&RectMake(0, 0, 0, 0), &_testRc.rc, &_bossBody.rc))
//	{
//		_bossBody.collision = true;
//	}
//	else _bossBody.collision = false;
//
//
//}
//
//
//void boss::bossStageOne()
//{
//
//	bossJump();
//	bossJumpCollision();
//	bossHeadCollision();
//	popsMove();
//
//};
//
//void boss::bossStageTwo()
//{
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//		(*_viBossBoll)->angle += 0.03f;
//
//		(*_viBossBoll)->x = _bossBody.x + cosf((*_viBossBoll)->angle) * 160;
//		(*_viBossBoll)->y = _bossBody.y + -sinf((*_viBossBoll)->angle) * 160;
//		(*_viBossBoll)->rc = RectMakeCenter((*_viBossBoll)->x, (*_viBossBoll)->y, 78, 78);
//
//	}
//
//	collision();
//
//	move();
//
//	bollCollision();
//
//	skullMove();
//};
//
//void boss::bossStageThree()
//{
//	bossWheelMove();
//
//	bossWheelCollision();
//
//};
//
//
//
//
//
//
//
//void boss::bossStageOneRender()
//{
//	if (_bossBody.collision) _bossBody.img = IMAGEMANAGER->findImage("boss_bodyHit");
//	else _bossBody.img = IMAGEMANAGER->findImage("boss_body2");
//
//	for (int i = 0; i < _vBossPops.size(); i++)
//	{
//		_vBossPops[i]->img->aniRender(getMemDC(), _vBossPops[i]->rc.left, _vBossPops[i]->rc.top, _vBossPops[i]->ani);
//		//Rectangle(getMemDC(), _vBossPops[i]->rc.left, _vBossPops[i]->rc.top, _vBossPops[i]->rc.right, _vBossPops[i]->rc.bottom);
//
//	}
//
//
//
//}
//
//void boss::bossStageTwoRender()
//{
//	//Rectangle(getMemDC(), _bossBody.movingRc.left, _bossBody.movingRc.top, _bossBody.movingRc.right, _bossBody.movingRc.bottom);
//
//
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//		//Rectangle(getMemDC(), (*_viBossBoll)->rc.left, (*_viBossBoll)->rc.top, (*_viBossBoll)->rc.right, (*_viBossBoll)->rc.bottom);
//		//Rectangle(getMemDC(), (*_viBossBoll)->rc.right, (*_viBossBoll)->rc.top + i, (*_viBossBoll)->rc.right + 10, (*_viBossBoll)->rc.top + 10 + i);
//		
//		if ((*_viBossBoll)->collision == true) (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollHit");
//		else (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollTop");
//
//		(*_viBossBoll)->img->render(getMemDC(), (*_viBossBoll)->rc.left, (*_viBossBoll)->rc.top);
//
//	}
//
//
//	_bossBody.img = IMAGEMANAGER->findImage("boss_body");
//	_bossBody.img->render(getMemDC(), _bossBody.rc.left, _bossBody.rc.top);
//
//	int i = 0;
//	for (_viBossSkull = _vBossSkull.begin(); _viBossSkull != _vBossSkull.end(); ++_viBossSkull)
//	{
//		//if (!(*_viBossSkull)->fire) continue;
//		(*_viBossSkull)->img->aniRender(getMemDC(), (*_viBossSkull)->rc.left, (*_viBossSkull)->rc.top, (*_viBossSkull)->ani);
//		//Rectangle(getMemDC(), (*_viBossSkull)->rc.left + 10 * i, (*_viBossSkull)->rc.top - 10, (*_viBossSkull)->rc.left + (10 * i) + 10, (*_viBossSkull)->rc.top);
//		i++;
//	}
//}
//
//void boss::bossStageThreeRender()
//{
//	for (_viBossWood = _vBossWood.begin(); _viBossWood != _vBossWood.end(); ++_viBossWood)
//	{
//		IMAGEMANAGER->findImage("boss_wood")->render(getMemDC(), (*_viBossWood)->rc.left, (*_viBossWood)->rc.top);
//		//Rectangle(getMemDC(), (*_viBossWood)->rc.left, (*_viBossWood)->rc.top, (*_viBossWood)->rc.right, (*_viBossWood)->rc.bottom);
//	}
//
//	for (_viBossBoll = _vBossBoll.begin(); _viBossBoll != _vBossBoll.end(); ++_viBossBoll)
//	{
//
//		//Rectangle(getMemDC(), (*_viBossBoll)->rc.left, (*_viBossBoll)->rc.top, (*_viBossBoll)->rc.right, (*_viBossBoll)->rc.bottom);
//		(*_viBossBoll)->img->render(getMemDC(), (*_viBossBoll)->rc.left, (*_viBossBoll)->rc.top);
//	}
//
//	
//	_spike.img->render(getMemDC(), _spike.rc.left, _spike.rc.top);
//
//
//
//}

