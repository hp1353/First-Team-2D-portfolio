#include "stdafx.h"
#include "critter.h"
#include "Player.h"

extern float MusicMasterVol;
extern float SoundMasterVol;


critter::critter()
{
}


critter::~critter()
{
}


HRESULT critter::init(int x, int y, const char* imageName, vector<enemy*> arrBox)
{
	imgInit();

	_x = (float)x;
	_y = (float)y;
	_width = _critterImg->getFrameWidth();
	_height = _critterImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 2;
	_damage = 2;
	_isDead = false;
	_MonsterType = E_CRITTER;

	_arrBox = arrBox;
	_playX = 0;
	_playY = 0;

	_imgName = imageName;
	_hurtSound = "enemy_hurt";
	_deathSound = "enemy_death2";

	_state = slimeJUMP;
	_isAlert = false;
	_isAggro = false;
	_isRight = false;

	_angle = PI / 2 + PI16;
	_power = 5.f;
	_gravity = 0.f;
	_jumpCounter = 0;

	return S_OK;
}

void critter::release()
{

}

void critter::update(Player* player)
{
	_playX = player->getPlayer()->getX();
	_playY = player->getPlayer()->getY();

	checkDead();
	if(_DamageNumUpCount <= 12)
	_DamageNumUpCount += 1;


	bottomPxl();

	checkAlert();
	jump();
	airUpdate();

	topPxl();
	leftPxl();
	rightPxl();
	CheckRectHit();

	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	dealDmg(player);
}

void critter::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	frameRender();
}

void critter::checkAlert()
{
	float distance = MY_UTIL::getDistance(_x, _y, _playX, _playY);

	if (abs(distance) < 250) {
		if (_state != slimeJUMP) {
			if (_playX < _x) {
				_isRight = false;
				_angle = PI / 2 + PI16;
			}
			else {
				_isRight = true;
				_angle = PI / 2 - PI16;
			}

			if (abs(distance) < 150) {
				_isAggro = true;
				if (_state != slimeJUMP) { _state = GROUND; }
			}
			else {
				if (_state != slimeJUMP) { _state = ALERT; }
			}
		}
	}
	else {
		if (_state != slimeJUMP) { _state = REST; }
	}
}

void critter::jump()
{
	if (!_isAggro) return;

	if (_jumpCounter > 20) {
		SOUNDMANAGER->play("critter_jump", SoundMasterVol);
		_state = slimeJUMP;
		_jumpCounter = 0;
	}
	else if (_state == GROUND) {
		_jumpCounter++;
	}
}

void critter::airUpdate()
{
	if (_state != slimeJUMP) return;

	_gravity += 0.2f;
	_x += cosf(_angle) * (_power);
	_y += -sinf(_angle) * (_power - _gravity);

}

void critter::bottomPxl()
{
	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.bottom; i < _rc.bottom + _power; i++)
	{
		COLORREF color = GetPixel(pxlImg->getMemDC(), _x, i);

		if (color == 0x00ff00) {
			if (_state == slimeJUMP) SOUNDMANAGER->play("WalkSound", 1.f);
			_y = i - _height / 2;
			_state = GROUND;
			_gravity = 0.f;
			break;
		}
	}
}

void critter::leftPxl()
{
	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.left + _power; i > _rc.left; i--)
	{
		COLORREF colorHi = GetPixel(pxlImg->getMemDC(), i, _y - 5);
		COLORREF colorLo = GetPixel(pxlImg->getMemDC(), i, _y + 5);

		if (colorHi == 0x00ff00 || colorLo == 0x00ff00) {
			_x = i + _width / 2;
			break;
		}
	}
}

void critter::rightPxl()
{
	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	for (int i = _rc.right - _power; i < _rc.right; i++)
	{
		COLORREF colorHi = GetPixel(pxlImg->getMemDC(), i, _y - 5);
		COLORREF colorLo = GetPixel(pxlImg->getMemDC(), i, _y + 5);

		if (colorHi == 0x00ff00 || colorLo == 0x00ff00) {
			_x = i - _width / 2;
			break;
		}
	}
}

void critter::topPxl()
{
	if (_state != slimeJUMP) return;

	image* pxlImg = IMAGEMANAGER->findImage(_imgName);

	COLORREF color = GetPixel(pxlImg->getMemDC(), _x, _rc.top);

	if (color == 0x00ff00) {
		_gravity = _power * 1.2;
	}
}

void critter::CheckRectHit()
{
	RECT temp = RectMake(0, 0, 0, 0);

	for (int i = 0; i < _arrBox.size(); i++)
	{
		if (!IntersectRect(&temp, &_rc, &_arrBox[i]->getRect())) continue;

		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

		if ((temp.bottom - temp.top) <= (temp.right - temp.left)) //»óÇÏ
		{
			if (temp.bottom == _rc.bottom && (temp.right - temp.left) > 3) //ÇÏ
			{
				_y = temp.top - _height / 2;
				_state = GROUND;
				_gravity = 0.f;
			}
			else if (temp.top == _rc.top) //»ó
			{
				_gravity = _power * 1.2;
				if (!SOUNDMANAGER->isPlaySound("º®²á")) {
					SOUNDMANAGER->play("º®²á", SoundMasterVol);
				}
			}
		}
		else if ((temp.bottom - temp.top) > (temp.right - temp.left)) //ÁÂ¿ì
		{
			if (temp.right == _rc.right) //¿ì
			{
				_x = temp.left - _width / 2;
			}
			else if (temp.left == _rc.left) //ÁÂ
			{
				_x = temp.right + _width / 2;
			}
		}
	}
}

void critter::imgInit()
{
	image* img = IMAGEMANAGER->findImage("critter");
	if (!img) {
		_critterImg = IMAGEMANAGER->addFrameImage("critter", "image/enemy/critter.bmp", 192, 30, 6, 1, true, 0x000000);
	}
	else {
		_critterImg = img;
	}
}

void critter::frameRender()
{
	switch (_state)
	{
	case REST: case GROUND:
		if (_isRight) _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 3, 0);
		else _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 0, 0);
		break;
	case ALERT:
		if (_isRight) _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 4, 0);
		else _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 1, 0);
		break;
	case slimeJUMP:
		if (_isRight) _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 5, 0);
		else _critterImg->frameRender(getMemDC(), _rc.left, _rc.top, 2, 0);
		break;
	}
}