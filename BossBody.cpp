#include "stdafx.h"
#include "BossBody.h"
#include "Player.h"
#include "progressBar.h"

BossBody::BossBody()
{
}


BossBody::~BossBody()
{
}

HRESULT BossBody::init(int x, int y, const char* imageName)
{
	imgInit();


	_x = (float)x;
	_y = (float)y;
	_width = _bossBodyImg->getFrameWidth();
	_height = _bossBodyImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_movRect = RectMakeCenter((int)_x, (int)_y, _width + 78 * 2, _height + 78 * 2);
	_headRect = RectMakeCenter((int)_x, _rc.top, 200, 30);
	_currentHP = _maxHP = 600;
	_damage = 5;
	_MonsterType = E_BOSS;

	//_progressBarForward = IMAGEMANAGER->addImage("123", "image/boss/hpBarTop.bmp", 414, 10, false, false);

	_imageName = imageName;
	_hurtSound = "enemy_hurt2";

	_phase = BOSSJUMPER;
	_motion = BOSSGROUND;
	_speed = 3.f;
	_power = 12.f;
	_angle = 0.f;
	_gravity = 0.f;

	_jumpCount = 0;   //점프 쿨타임
	_transCount = 0; //변신 쿨타임
	_woodPopCount = 0; //나무판자 팝업 쿨타임

	_stageNum = 0;

	_transed = false;
	_spikeY = BOSSCENTERY * 2;

	for (float i = 0; i < PI2 - PI / 4; i += PI / 4)
	{
		addBall(-100, -100, i);
		addWood(-100, -100, i);
	}

	_bullet = new Pop;
	_bullet->init("effect_pop", 17, 400);

	_hpbar = new progressBar;
	_hpbar->init(370, 720, 414, 10);
	_hpbar->gauge(_currentHP, _maxHP);

	IMAGEMANAGER->addImage("hpBarBottom", "image/boss/hpBarBottom.bmp", 480, 20, false, false);
	IMAGEMANAGER->addImage("alhpa", "image/boss/alhpa.bmp", 480, 20, false, false);

	alphanum = 0;

	_isTheEnd = false;
	_isHurt = false;
	_bossImgName = "boss_body1";

	return S_OK;
}

void BossBody::release(bool isBoss)
{
	clear(true);
}

void BossBody::update(bool isBoss)
{
	if (KEYMANAGER->isOnceDown('H'))
	{
		_stageNum++;
	}
	if(_stageNum != 3)
	dealDmg(_player);
	//보스의 정보 계속 업데이트 할 수 있게
	_rc = RectMakeCenter(_x, _y, 240, 240);
	_movRect = RectMakeCenter(_x, _y, 380, 380);
	_headRect = RectMakeCenter(_x, _y - 85, 120, 30);
	if (_currentHP <= 0)
	{
		_stageNum = 3;
	}
	else if (_currentHP <= 200)
	{
		_stageNum = 2;
	}
	else if (_currentHP <= 400)
	{
		_stageNum = 1;
	}

	switch (_stageNum)
	{
	case 0:
		phase1();
		break;
	case 1:	phase2();
		break;
	case 2:	phase3();
		break;
	case 3: phase4();
		break;
	default: _stageNum = 0;
		break;
	}


	_hpbar->setX(_player->GetCamera()->getCamX() + CENTERX / 2 - 28);
	_hpbar->setY(_player->GetCamera()->getCamY() + 430);
	_hpbar->gauge(_currentHP, _maxHP);
	_hpbar->update();

	_bullet->LinkToEnemy(_player);
	_bullet->update();
	alphanum++;


	hurt();
}

void BossBody::render(bool isBoss)
{

	switch (_stageNum)
	{
	case 0:
		_bullet->render();
		phase1_render();
		break;
	case 1:	phase2_render();
		break;
	case 2:	phase3_render();
		break;
	case 3:phase4_render();
		break;
	default: _stageNum = 0;
		break;
	}

	_bossBodyImg->render(getMemDC(), _rc.left, _rc.top);
	/*if(alphanum < 255 )
	IMAGEMANAGER->findImage("alhpa")->alphaRender(getMemDC(), _player->GetCamera()->getCamX() + 70, _player->GetCamera()->getCamY() + 430, alphanum);
	else
	{*/

}

//PHASE 1~3
void BossBody::phase1()
{
	jump();
	phase1_pxlCollision();
}

void BossBody::phase2()
{
	for (int i = 0; i < _vBall.size(); i++)
	{
		_vBall[i]->update(_player, true);
		_vBall[i]->move(_x, _y);

	}

	_player->GetCamera()->camVibeSwitch();

	phase2_pxlCollision();
	phase2_move();
	phase2_bollCollision();

	_soundCount++;
	if (_soundCount < 15) return;
	SOUNDMANAGER->play("몬스터벽꿍", 1.f);
	_soundCount = 0;
}

void BossBody::phase3()
{

	bossTrans();
	ballSpin();
	woodSpin();
}

void BossBody::phase4()
{
	bossdead();
	if (_rc.bottom + _height * 1 / 6 > IMAGEMANAGER->findImage(_imageName)->getHeight()) {
		_isTheEnd = true;
	}
}

//PHASE 1
void BossBody::jump()
{
	_rc = RectMakeCenter(_x, _y, 240, 240);

	float distance = MY_UTIL::getDistance(_x, _y, _player->getPlayer()->getX(), _player->getPlayer()->getY());

	if (abs(distance) < 1000)
	{
		if (_motion != BOSSJUMP)
		{
			if (_player->getPlayer()->getX() < _x)
			{
				_angle = PI / 2 + PI16;
			}
			else
			{
				_angle = PI / 2 - PI16;
			}

			if (abs(distance) < 1000)
			{
				if (_motion != BOSSJUMP)
				{
					_motion = BOSSGROUND;
				}
			}
			else
			{

			}
		}
	}


	if (_jumpCount > 10)
	{
		_motion = BOSSJUMP;
		_jumpCount = 0;
	}
	else if (_motion == BOSSGROUND)
	{
		_jumpCount++;
		_motion = BOSSGROUND;

	}

	if (_motion == BOSSJUMP)
	{
		_gravity += 0.3f;
		_x += cosf(_angle) * (_power);
		_y += -sinf(_angle) * (_power - _gravity);
	}


}

void BossBody::phase1_pxlCollision()
{
	image* img = IMAGEMANAGER->findImage(_imageName);

	COLORREF color;
	//BOTTOM

	for (int i = _rc.bottom - 2; i < _rc.bottom; i++)
	{
		color = GetPixel(img->getMemDC(), _x, i);
		if (color != 0x00ff00) continue;

		_motion = BOSSGROUND;
		_gravity = 0.f;
		_y = i - _width / 2 - 2;
		EFFECTMANAGER->play("effect_dustBig", _x - 45, _y + 100);
		EFFECTMANAGER->play("effect_dustBig", _x + 45, _y + 100);
		EFFECTMANAGER->play("effect_dust", _x - 80, _y + 100);
		EFFECTMANAGER->play("effect_dust", _x + 80, _y + 100);

		SOUNDMANAGER->play("enemy_death2", 1.f);

		//pop공격 함수
		_bullet->fire(_x + 2, _rc.bottom - 20, 0.f, 5.f, 1, 0, _imageName);
		_bullet->fire(_x, _rc.bottom - 20, PI / 64, 5.f, 1, 0, _imageName);
		_bullet->fire(_x - 3, _rc.bottom - 20, PI32, 5.f, 1, 0, _imageName);
		_bullet->fire(_x + 3, _rc.bottom - 20, PI - PI32, 5.f, 1, 0, _imageName);
		_bullet->fire(_x, _rc.bottom - 20, PI - PI / 64, 5.f, 1, 0, _imageName);
		_bullet->fire(_x - 2, _rc.bottom - 20, PI, 5.f, 1, 0, _imageName);

		_player->GetCamera()->camVibeSwitch();

		break;
	}

	//LEFT
	for (int i = _rc.left; i < _rc.left + 5; i++)
	{
		color = GetPixel(img->getMemDC(), i, _y);
		if (color != 0x00ff00) continue;
		_motion = BOSSGROUND;
		_angle -= PI;
		_x = i + _width / 2 + 3;

		break;
	}
	//RIGHT
	for (int i = _rc.right - 5; i < _rc.right; i++)
	{
		color = GetPixel(img->getMemDC(), i, _y);
		if (color != 0x00ff00) continue;
		_motion = BOSSGROUND;
		_angle += PI;
		_x = i - _width / 2 - 3;

		break;
	}


}

//PHASE 2
void BossBody::phase2_pxlCollision()
{
	image* img = IMAGEMANAGER->findImage(_imageName);

	COLORREF color;
	//LEFT
	for (int i = _movRect.left; i < _x; i++)
	{
		color = GetPixel(img->getMemDC(), i, _y);
		if (color != 0x00ff00) continue;
		_motion = BOSSUP;
		_x = _x + 3;
		break;
	}
	//RIGHT
	for (int i = _x; i < _movRect.right; i++)
	{
		color = GetPixel(img->getMemDC(), i, _y);;
		if (color != 0x00ff00) continue;
		_motion = BOSSDOWN;
		_x = _x - 3;
		break;
	}
	//TOP
	for (int i = _movRect.top; i < _y; i++)
	{
		color = GetPixel(img->getMemDC(), _x, i);
		if (color != 0x00ff00) continue;
		_motion = BOSSRIGHT;
		_y = _y + 3;
		break;
	}
	//BOTTOM
	for (int i = _y; i < _movRect.bottom; i++)
	{
		color = GetPixel(img->getMemDC(), _x, i);
		if (color != 0x00ff00) continue;
		_motion = BOSSLEFT;
		_y = _y - 3;
		break;
	}
}

void BossBody::phase2_move()
{
	switch (_motion)
	{
	case BOSSUP:
		_y -= _speed;
		break;
	case BOSSDOWN:
		_y += _speed;
		break;
	case BOSSLEFT:
		_x -= _speed;
		break;
	case BOSSRIGHT:
		_x += _speed;
		break;
	default:_x -= _speed;
		break;
	}
}

void BossBody::phase2_bollCollision()
{

}

//PHASE 3

void BossBody::bossTrans()
{
	//스파이크 추가해야함

	_bossImgName = "boss_body2";

	//보스 볼 돌아가도록

	for (int i = 0; i < _vBall.size(); i++)
	{
		_vBall[i]->update(_player, true);
		_vBall[i]->move(_x, _y);

	}

	for (int i = 0; i < _vWood.size(); i++)
	{
		_vWood[i]->update();
		_vWood[i]->move(_x, _y);
	}

	float bossDis = MY_UTIL::getDistance(_x, _y, BOSSCENTERX, BOSSCENTERY - 50);

	if (_x < BOSSCENTERX)	_x++;

	if (_x >  BOSSCENTERX)	_x--;

	if (_y >  BOSSCENTERY - 50) _y--;

	if (_y <  BOSSCENTERY - 50)	_y++;

	if (abs(bossDis) <= 3)
	{

		_transCount++;
		_woodPopCount += 7;
		_spikeY -= 5;
		_transed = true;
		if (_spikeY <= (BOSSCENTERY * 2) - 200)
		{
			_spikeY = (BOSSCENTERY * 2) - 200;

		}

		//공이 빨리 돌 수 있도록

		for (int i = 0; i < _vBall.size(); i++)
		{
			_vBall[i]->setSpeed(0.08f);
		}

		for (int i = 0; i < _vWood.size(); i++)
		{
			_vWood[i]->setRadius(_woodPopCount);

			if (_woodPopCount > 280) _woodPopCount = 280;
		}



		//	if (_spike.y > BOSSCENTERY + 265) _spike.y--;


		if (_transCount >= 300) // 5초 이상이 되면
		{


			for (int i = 0; i < _vBall.size(); i++)
			{
				_vBall[i]->setSpeed(0.03f);

			}

			_bossImgName = "boss_body3";

			//(*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollTop");

			//if (_collision == true) _bossBody.img = IMAGEMANAGER->findImage("boss_body3Hit");

			//if ((*_viBossBoll)->collision == true) (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollHit");
			//else (*_viBossBoll)->img = IMAGEMANAGER->findImage("boss_bollTop");

			//for (int i = 0; i < _vBlood.size(); i++)
			//{
			//	if (!_vBlood[i]->turnOn)
			//	{
			//		_vBlood[i]->x = _bossBody.x - 100 + (i * 40);
			//		_vBlood[i]->y = _bossBody.y + RND->getFromIntTo(10, 100), 12, 12;
			//	}
			//
			//
			//	_vBlood[i]->turnOn = true;


			//}

		}



	}


}

void BossBody::ballSpin()
{

}

void BossBody::woodSpin()
{

}

void BossBody::bossdead()
{
	boomrndx = RND->getFromIntTo(_rc.left, _rc.right);
	boomrndy = RND->getFromIntTo(_rc.top, _rc.bottom);
}

// 이미지 초기화 및 랜더함수
void BossBody::imgInit()
{

	_bossBodyImg = IMAGEMANAGER->findImage("boss_body1");

}

void BossBody::phase1_render()
{
	//if (_bossBody.collision) _bossBody.img = IMAGEMANAGER->findImage("boss_bodyHit");
	//else
	_bossBodyImg = IMAGEMANAGER->findImage(_bossImgName);

	//for (int i = 0; i < _vBossPops.size(); i++)
	//{
	//	_vBossPops[i]->img->aniRender(getMemDC(), _vBossPops[i]->rc.left, _vBossPops[i]->rc.top, _vBossPops[i]->ani);
	//	//Rectangle(getMemDC(), _vBossPops[i]->rc.left, _vBossPops[i]->rc.top, _vBossPops[i]->rc.right, _vBossPops[i]->rc.bottom);
	//
	//}
}

void BossBody::phase2_render()
{
	_bossBodyImg = IMAGEMANAGER->findImage(_bossImgName);

	for (int i = 0; i < _vBall.size(); i++)
	{
		_vBall[i]->render(true);
	}


}

void BossBody::phase3_render()
{
	_bossBodyImg = IMAGEMANAGER->findImage(_bossImgName);

	for (int i = 0; i < _vBall.size(); i++)
	{
		_vBall[i]->render(true);
	}

	for (int i = 0; i < _vWood.size(); i++)
	{
		_vWood[i]->render();
	}

	if (_transed) IMAGEMANAGER->findImage("spike")->render(getMemDC(), 60, _spikeY);

}

void BossBody::phase4_render()
{
	_transed = false;

	_y++;
	_bossBodyImg = IMAGEMANAGER->findImage("boss_body3");
	//IMAGEMANAGER->findImage("먼지")->frameRender(getMemDC(), _rc.left, _rc.right);
	EFFECTMANAGER->play("빨간 먼지", boomrndx, boomrndy);

}

//VECTOR함수
void BossBody::addBall(int x, int y, float angle)
{
	BossBall* temp = new BossBall;
	temp->init(x, y, angle, "stage_finalPixel");
	_vBall.push_back(temp);
}

void BossBody::addWood(int x, int y, float angle)
{
	Wood* temp = new Wood;
	temp->init(x, y, angle);
	_vWood.push_back(temp);
}

void BossBody::clear(bool isBoss)
{
	//BALL
	/*for (int i = 0; i < _vBall.size(); i++) {
	_vBall[i]->release();
	SAFE_DELETE(_vBall[i]);
	}*/
	_vBall.clear();
	//WOOD
	for (int i = 0; i < _vWood.size(); i++) {
		_vWood[i]->release();
		SAFE_DELETE(_vWood[i]);
	}
	_vWood.clear();
}

void BossBody::takeHit(int dmg)
{
	SOUNDMANAGER->play(_hurtSound, 1.f);
	_currentHP -= dmg;
	_StackedDamage += dmg;

	_DamageOutTime = TIMEMANAGER->getWorldTime() + 1;
	_isHitOut = true;
	_DamageNumUpCount = 0;

	_isHurt = true;
}

void BossBody::hurt()
{
	switch (_stageNum)
	{
	case 0:
		_bossImgName = "boss_body1";
		break;
	case 1:
		_bossImgName = "boss_body2";
		break;
	}

	if (!_isHurt) return;
	
	switch (_stageNum)
	{
	case 0: case 1:
		_bossImgName = "boss_body1Hit";
		break;
	case 2:
		_bossImgName = "boss_body3Hit";
		break;
	}

	_isHurt = false;
}

void BossBody::ProgressBarRender()
{
	IMAGEMANAGER->findImage("hpBarBottom")->render(getMemDC(), _player->GetCamera()->getCamX() + 70, _player->GetCamera()->getCamY() + 430);
	_hpbar->render();
}