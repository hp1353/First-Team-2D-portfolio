#include "stdafx.h"
#include "basil.h"
#include "Player.h"

basil::basil()
{
}


basil::~basil()
{
}


HRESULT basil::init(int x, int y, const char* imageName)
{
	imgInit();
	aniInit();

	_x = (float)x;
	_y = (float)y;
	_width = _basilImg->getFrameWidth();
	_height = _basilImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 1;
	_damage = 100;
	_isDead = false;
	_MonsterType = E_BASIL;

	_imgName = imageName;
	_hurtSound = "enemy_block";
	_deathSound = "enemy_death1";

	_playX = 0;
	_playY = 0;

	_pivot = CENTERX;
	_speed = 4.5f;
	_isRight = true;

	return S_OK;
}

void basil::release()
{
	SAFE_DELETE(_basilAni);
}

void basil::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	_playX = player->getPlayer()->getX();
	_playY = player->getPlayer()->getY();

	move();
	leftPxl();
	rightPxl();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	dealDmg(player);
	aniUpdate();
}

void basil::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	//Rectangle(getMemDC(), _pivot, WINSIZEY - 10, _pivot + 10, WINSIZEY);
	aniRender();
}

void basil::move()
{
	if (_pivot < _playX - 3.f) {
		_pivot += _speed;
	}
	else if (_pivot > _playX + 3.f) {
		_pivot -= _speed;
	}

	if (_isRight) {
		_x += _speed;
	}
	else {
		_x -= _speed;
	}

	if (_x > _pivot + CENTERX) {
		_isRight = false;
	}
	else if (_x < _pivot - CENTERX) {
		_isRight = true;
	}
}

void basil::leftPxl()
{
	if (_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.left + _speed; i > _rc.left; i--)
	{
		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _y);

		if (color == 0x00ff00) {
			_x = i + _width / 2;
			_isRight = true;
			break;
		}
	}
}

void basil::rightPxl()
{
	if (!_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.right - _speed; i < _rc.right; i++)
	{
		COLORREF color = GetPixel(pxlImg->getMemDC(), i, _y - 5);

		if (color == 0x00ff00) {
			_x = i - _width / 2;
			_isRight = false;
			break;
		}
	}
}

void basil::imgInit()
{
	image* img = IMAGEMANAGER->findImage("basil");
	if (!img) {
		_basilImg = IMAGEMANAGER->addFrameImage("basil", "image/enemy/basil.bmp", 384, 27, 6, 1, true, 0x000000);
	}
	else {
		_basilImg = img;
	}
}

void basil::aniInit()
{
	_basilAni = new animation;
	_basilAni->init(_basilImg->getWidth(), _basilImg->getHeight(), _basilImg->getFrameWidth(), _basilImg->getFrameHeight());
	_basilAni->setFPS(10);
	_basilAni->start();
}

void basil::aniUpdate()
{
	if (_isRight)
	{
		_basilAni->setPlayFrame(3, 5, false, true);
	}
	else
	{
		_basilAni->setPlayFrame(0, 2, false, true);
	}
	_basilAni->frameUpdate(TIMEMANAGER->getElapsedTime());

}

void basil::aniRender()
{
	_basilImg->aniRender(getMemDC(), _rc.left, _rc.top, _basilAni);
}