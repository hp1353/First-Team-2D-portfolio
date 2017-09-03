#include "stdafx.h"
#include "basu.h"
#include "Player.h"

extern float MusicMasterVol;
extern float SoundMasterVol;


basu::basu()
{
}


basu::~basu()
{
}

HRESULT basu::init(int x, int y, const char* imageName)
{
	imgInit();
	aniInit();

	_bullet = new Basu_Bullet;
	_bullet->init("BasuBullet", 50, 600);



	_x = (float)x;
	_y = (float)y;
	_width = 40;
	_height = 40;
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 16;
	_damage = 4;
	_isDead = false;
	_MonsterType = E_BASU;

	_imgName = imageName;
	_hurtSound = "enemy_hurt2";
	_deathSound = "enemy_death3";

	_playX = 0;
	_playY = 0;

	_xAngle = 0.f;
	_xPivot = _x;
	_xPower = 50;

	_yAngle = 0.f;
	_yPivot = _y;
	_yPower = 25;

	_isRight = true;
	_isFire = false;
	_fireCount = 0;
	_chargeCount = 0;

	return S_OK;
}

void basu::release()
{
	SAFE_DELETE(_basuNormal);
	SAFE_DELETE(_basuFire);
}

void basu::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	_playX = player->getPlayer()->getX();
	_playY = player->getPlayer()->getY();

	_bullet->LinkToEnemy(player);
	move();
	fire();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	dealDmg(player);
	aniUpdate();
	_bullet->update();
	checkDead();
}

void basu::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	aniRender();
	_bullet->render();

}

void basu::move()
{
	if (_xPivot <= _playX)	_xPivot += 1.2f;
	else _xPivot -= 1.2f;

	if (_x < _playX) _isRight = true;
	else _isRight = false;

	_xAngle += 0.04f;
	if (_xAngle > PI2) _xAngle - PI2;
	_yAngle += 0.01f;
	if (_yAngle > PI2) _yAngle - PI2;

	_x = cosf(_xAngle) * _xPower + _xPivot;
	_y = -sinf(_yAngle) * _yPower + _yPivot;
}

void basu::fire()
{
	int distance = MY_UTIL::getDistance(_x, _y, _playX, _playY);

	if (distance > 250) return;

	if (!_isFire)
	{
		_fireCount++;
		if (_fireCount >= 90)
		{
			_isFire = true;
			_fireCount = 0;
		}
	}
	else
	{
		_chargeCount++;
		if (_chargeCount >= 30)
		{
			SOUNDMANAGER->play("MonsterFire", SoundMasterVol);
			_bullet->fire(_x, _y,
				MY_UTIL::getAngle(_x, _y, _playX, _playY),
				7.0f,
				2, 0, _imgName);

			_isFire = false;
			_chargeCount = 0;
		}
	}
}

void basu::imgInit()
{
	image* img = IMAGEMANAGER->findImage("basu");
	if (!img) {
		_basuImg = IMAGEMANAGER->addFrameImage("basu", "image/enemy/basu.bmp", 288, 44, 6, 1, true, 0x000000);
	}
	else {
		_basuImg = img;
	}
}

void basu::aniInit()
{
	_basuNormal = new animation;
	_basuNormal->init(_basuImg->getWidth(), _basuImg->getHeight(), _basuImg->getFrameWidth(), _basuImg->getFrameHeight());
	_basuNormal->setFPS(12);

	_basuFire = new animation;
	_basuFire->init(_basuImg->getWidth(), _basuImg->getHeight(), _basuImg->getFrameWidth(), _basuImg->getFrameHeight());
	_basuFire->setFPS(12);
}

void basu::aniUpdate()
{
	if (!_isFire) {
		_basuFire->pause();
		_basuNormal->resume();
		if (_isRight) _basuNormal->setPlayFrame(3, 4, false, true);
		else _basuNormal->setPlayFrame(0, 1, false, true);
		_basuNormal->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
	else {
		_basuNormal->pause();
		_basuFire->resume();
		if (_isRight) _basuFire->setPlayFrame(5, 4, false, true);
		else _basuFire->setPlayFrame(2, 1, false, true);
		_basuFire->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void basu::aniRender()
{
	if (_isFire) _basuImg->aniRender(getMemDC(), _rc.left, _rc.top, _basuFire);
	else _basuImg->aniRender(getMemDC(), _rc.left, _rc.top, _basuNormal);
}