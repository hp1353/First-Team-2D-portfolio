#include "stdafx.h"
#include "beetle.h"
#include "Player.h"


beetle::beetle()
{
}


beetle::~beetle()
{
}

HRESULT beetle::init(int x, int y, bool isRight, const char* imageName)
{
	imgInit();
	aniInit();

	_x = (float)x;
	_y = (float)y;
	_width = _beetleImg->getFrameWidth();
	_height = _beetleImg->getFrameHeight();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_currentHP = _maxHP = 4;
	_damage = 2;
	_isDead = false;
	_MonsterType = E_BEETLE;

	_imgName = imageName;
	_hurtSound = "enemy_hurt";
	_deathSound = "enemy_death2";

	_idleCounter = 0;
	_state = FLY;
	_speed = 4.f;
	_isRight = isRight;

	return S_OK;
}

void beetle::release()
{
	SAFE_DELETE(_beetleAni);
}

void beetle::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	checkDead();
	move();
	leftPxl();
	rightPxl();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	dealDmg(player);
	aniUpdate();
}

void beetle::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	aniRender();
}

void beetle::move()
{
	switch (_state)
	{
	case WALL:
		_idleCounter++;
		if (_idleCounter >= 90)
		{
			_idleCounter = 0;
			_beetleAni->start();
			_state = FLY;
		}
		break;
	case FLY:
		if (_isRight) {
			_x += _speed;
		}
		else {
			_x -= _speed;
		}
		break;
	}
}

void beetle::leftPxl()
{
	if (_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.left + _speed; i > _rc.left; i--)
	{
		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _y);

		if (color == 0x00ff00) {
			_x = i + _width / 2;
			_beetleAni->stop();
			_isRight = true;
			_state = WALL;
		}
	}
}

void beetle::rightPxl()
{
	if (!_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.right - _speed; i < _rc.right; i++)
	{
		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _y);

		if (color == 0x00ff00) {
			_x = i - _width / 2;
			_beetleAni->stop();
			_isRight = false;
			_state = WALL;
		}
	}
}

void beetle::imgInit()
{
	image* img = IMAGEMANAGER->findImage("beetle");
	if (!img) {
		_beetleImg = IMAGEMANAGER->addFrameImage("beetle", "image/enemy/beetle_wall.bmp", 192, 27, 6, 1, true, 0x000000);
	}
	else {
		_beetleImg = img;
	}
}

void beetle::aniInit()
{
	_beetleAni = new animation;
	_beetleAni->init(_beetleImg->getWidth(), _beetleImg->getHeight(), _beetleImg->getFrameWidth(), _beetleImg->getFrameHeight());
	_beetleAni->setFPS(10);
	_beetleAni->start();
}

void beetle::aniUpdate()
{
	if (!_beetleAni->isPlay()) return;
	if (_isRight) {
		_beetleAni->setPlayFrame(4, 5, false, true);
	}
	else {
		_beetleAni->setPlayFrame(1, 2, false, true);
	}
	_beetleAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void beetle::aniRender()
{
	switch (_state)
	{
	case WALL:
		if (_isRight) _beetleImg->frameRender(getMemDC(), _rc.left, _rc.top, 3, 0);
		else _beetleImg->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	case FLY:
		_beetleImg->aniRender(getMemDC(), _rc.left, _rc.top, _beetleAni);
		break;
	}
}