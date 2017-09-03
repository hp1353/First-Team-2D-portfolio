#include "stdafx.h"
#include "bat.h"
#include "Player.h"


bat::bat()
{
}


bat::~bat()
{
}


HRESULT bat::init(int x, int y, float angle, float flyPower)
{
	imgInit();
	aniInit();

	_x = (float)x;
	_y = (float)y;
	_width = _batImg->getFrameWidth();
	_height = _batImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP =1;
	_damage = 2;
	_isDead = false;
	_MonsterType = E_BAT;

	_playX = 0;
	_playY = 0;

	_hurtSound = "enemy_hurtSmall";
	_deathSound = "enemy_death1";

	_angle = angle;
	_posY = (float)y;
	_flyPower = flyPower;

	_isRight = true;

	return S_OK;
}

void bat::release()
{
	SAFE_DELETE(_batFly);
}

void bat::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	_playX = player->getPlayer()->getX();
	_playY = player->getPlayer()->getY();

	checkDead();
	checkDirection();
	fly();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	dealDmg(player);
	aniUpdate();
}

void bat::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	aniRender();
}

void bat::fly()
{
	_angle += 0.02f;
	if (_angle > PI2) {
		_angle - PI2;
	}
	_y = -sinf(_angle) * _flyPower + _posY;
}

void bat::checkDirection()
{
	float distance = MY_UTIL::getDistance(_x, _y, _playX, _playY);

	if (distance < 200)
	{
		if (_x < _playX) _isRight = true;
		else _isRight = false;
	}
}

void bat::imgInit()
{
	image* img = IMAGEMANAGER->findImage("bat");
	if (!img) {
		_batImg = IMAGEMANAGER->addFrameImage("bat", "image/enemy/bat.bmp", 193, 32, 6, 1, true, 0x000000);
	}
	else {
		_batImg = img;
	}
}

void bat::aniInit()
{
	_batFly = new animation;
	_batFly->init(_batImg->getWidth(), _batImg->getHeight(), _batImg->getFrameWidth(), _batImg->getFrameHeight());
	_batFly->setFPS(10);
	_batFly->start();
}

void bat::aniUpdate()
{
	if (_isRight)
	{
		_batFly->setPlayFrame(3, 5, false, true);
	}
	else
	{
		_batFly->setPlayFrame(0, 2, false, true);
	}
	_batFly->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void bat::aniRender()
{
	_batImg->aniRender(getMemDC(), _rc.left, _rc.top, _batFly);
}