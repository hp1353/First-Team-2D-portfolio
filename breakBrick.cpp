#include "stdafx.h"
#include "breakBrick.h"


breakBrick::breakBrick()
{
}


breakBrick::~breakBrick()
{
}


HRESULT breakBrick::init(int x, int y)
{
	imgInit();

	_x = (float)x;
	_y = (float)y;
	_width = _brickImg->getFrameWidth();
	_height = _brickImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 1;
	_damage = 0;
	_isDead = false;
	_MonsterType = E_BRICK;

	_playX = NULL;
	_playY = NULL;

	_hurtSound = "ÃÑ¾Ëº®Ãæµ¹";
	_deathSound = "breakableBox";

	return S_OK;
}

void breakBrick::release()
{

}

void breakBrick::update(Player* player)
{
	checkDead();
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
}

void breakBrick::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_brickImg->render(getMemDC(), _rc.left, _rc.top);
}

void breakBrick::imgInit()
{
	image* img = IMAGEMANAGER->findImage("brick");
	if (!img) {
		_brickImg = IMAGEMANAGER->addFrameImage("brick", "image/Iteam/BreakableTile.bmp", 32, 32, 1, 1, false, false);
	}
	else {
		_brickImg = img;
	}
}
