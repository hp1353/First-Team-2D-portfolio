#include "stdafx.h"
#include "behemoth.h"
#include "Player.h"


behemoth::behemoth()
{
}


behemoth::~behemoth()
{
}


HRESULT behemoth::init(int x, int y, const char* imageName)
{
	imgInit();
	aniInit();

	_x = (float)x;
	_y = (float)y;
	_width = _behemothImg->getFrameWidth();
	_height = _behemothImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 8;
	_damage = 1;
	_isDead = false;
	_MonsterType = E_BEHEMOTH;

	_imgName = imageName;
	_hurtSound = "enemy_hurt2";
	_deathSound = "enemy_death3";

	_isRight = true;
	_isRage = false;

	_speed = 1.5f;
	_soundCount = 0;

	return S_OK;
}

void behemoth::release()
{
	SAFE_DELETE(_behemothPeace);
	SAFE_DELETE(_behemothRage);
}

void behemoth::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	move();
	leftPxl();
	rightPxl();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	dealDmg(player);
	checkDead();
	checkRage();
	aniUpdate();
}

void behemoth::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	aniRender();
}

void behemoth::checkRage()
{
	if (_currentHP < _maxHP && !_isRage) {
		_isRage = true;
		_speed = 5.f;
		_damage = 5;
	}
}

void behemoth::move()
{
	if (_isRight) { _x += _speed; }
	else { _x -= _speed; }

	if (!_isRage) return;
	_soundCount++;
	if (_soundCount < 6) return;
	SOUNDMANAGER->play("WalkSound", 3.f);
	EFFECTMANAGER->play("¸ÕÁö", _x, _rc.bottom);
	_soundCount = 0;
}

void behemoth::leftPxl()
{
	if (_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.left + _speed; i > _rc.left; i--)
	{
		COLORREF colorHi = GetPixel(pxlImg->getMemDC(), i, _y - 5);
		COLORREF colorLo = GetPixel(pxlImg->getMemDC(), i, _y + 5);

		if (colorHi == 0x00ff00 || colorLo == 0x00ff00) {
			_x = i + _width / 2;
			_isRight = true;
			break;
		}
	}
}

void behemoth::rightPxl()
{
	if (!_isRight) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.right - _speed; i < _rc.right; i++)
	{
		COLORREF colorHi = GetPixel(pxlImg->getMemDC(), i, _y - 5);
		COLORREF colorLo = GetPixel(pxlImg->getMemDC(), i, _y + 5);

		if (colorHi == 0x00ff00 || colorLo == 0x00ff00) {
			_x = i - _width / 2;
			_isRight = false;
			break;
		}
	}
}

void behemoth::imgInit()
{
	image* img = IMAGEMANAGER->findImage("behemoth");
	if (!img) {
		_behemothImg = IMAGEMANAGER->addFrameImage("behemoth", "image/enemy/behemoth.bmp", 768, 48, 12, 1, true, 0x000000);
	}
	else {
		_behemothImg = img;
	}
}

void behemoth::aniInit()
{
	_behemothPeace = new animation;
	_behemothPeace->init(_behemothImg->getWidth(), _behemothImg->getHeight(), _behemothImg->getFrameWidth(), _behemothImg->getFrameHeight());
	_behemothPeace->setFPS(7);
	_behemothPeace->start();

	_behemothRage = new animation;
	_behemothRage->init(_behemothImg->getWidth(), _behemothImg->getHeight(), _behemothImg->getFrameWidth(), _behemothImg->getFrameHeight());
	_behemothRage->setFPS(7);
}

void behemoth::aniUpdate()
{
	if (!_isRage) {
		if (_isRight) _behemothPeace->setPlayFrame(6, 8, false, true);
		else _behemothPeace->setPlayFrame(0, 2, false, true);
		_behemothPeace->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
	else {
		if (_isRight) _behemothRage->setPlayFrame(10, 11, false, true);
		else _behemothRage->setPlayFrame(4, 5, false, true);
		_behemothRage->resume();
		_behemothRage->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void behemoth::aniRender()
{
	if (_isRage) _behemothImg->aniRender(getMemDC(), _rc.left, _rc.top, _behemothRage);
	else _behemothImg->aniRender(getMemDC(), _rc.left, _rc.top, _behemothPeace);
}