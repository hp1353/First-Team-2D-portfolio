#include "stdafx.h"
#include "angel.h"
#include "Player.h"


angel::angel()
{
}


angel::~angel()
{
}


HRESULT angel::init(int x, int y)
{
	imgInit();
	aniInit();

	_x = (float)x;
	_y = (float)y;
	_width = _angelImg->getFrameWidth();
	_height = _angelImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 10;
	_damage = 4;
	_isDead = false;
	_MonsterType = E_ANGEL;

	_playX = 0;
	_playY = 0;

	_hurtSound = "enemy_hurtSmall";
	_deathSound = "enemy_death1";

	_angle = 0.f;
	_speed = 8.f;
	_distance = 0;

	_isRight = true;
	_isAttack = false;

	_attackCount = 0;

	return S_OK;
}

void angel::release()
{
	SAFE_DELETE(_angelAni);
}

void angel::update(Player* player)
{
	if (_DamageNumUpCount <= 12)
		_DamageNumUpCount += 1;
	checkDead();
	move(player);
	attack(player);
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	dealDmg(player);
	aniUpdate();
}

void angel::render()
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	aniRender();
}

void angel::move(Player* player)
{
	if (_x < player->getPlayer()->getX()) _isRight = true;
	else _isRight = false;

	if (_isAttack) return;

	_angle += 0.01f;
	if (_angle >= PI2) _angle -= PI2;
	
	_distance = MY_UTIL::getDistance(_x, _y, player->getPlayer()->getX(), player->getPlayer()->getY());
	_distance -= 0.1f;
	if (_distance <= 100.f) _distance = 100.f;

	_x = cosf(_angle) * _distance + player->getPlayer()->getX();
	_y = -sinf(_angle) * _distance + player->getPlayer()->getY();

	//공격 여부 확인
	if (_distance > 100.f) return;

	_attackCount++;

	if (_attackCount < 60) return;

	_isAttack = true;
	_attackCount = 0;
	_angle = MY_UTIL::getAngle(_x, _y, player->getPlayer()->getX(), player->getPlayer()->getY());
}

void angel::attack(Player* player)
{
	if (!_isAttack) return;

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;

	float distance = MY_UTIL::getDistance(_x, _y, player->getPlayer()->getX(), player->getPlayer()->getY());

	if (distance < 200) return;

	_isAttack = false;
}

void angel::imgInit()
{
	image* img = IMAGEMANAGER->findImage("angel");
	if (!img) {
		_angelImg = IMAGEMANAGER->addFrameImage("angel", "image/enemy/angel.bmp", 128, 32, 4, 1, true, 0xff00ff);
	}
	else {
		_angelImg = img;
	}
}

void angel::aniInit()
{
	_angelAni = new animation;
	_angelAni->init(_angelImg->getWidth(), _angelImg->getHeight(),
		_angelImg->getFrameWidth(), _angelImg->getFrameHeight());
	_angelAni->setFPS(10);
	_angelAni->start();
}

void angel::aniUpdate()
{
	if (_isRight)
	{
		_angelAni->setPlayFrame(2, 3, false, true);
	}
	else
	{
		_angelAni->setPlayFrame(0, 1, false, true);
	}
	_angelAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void angel::aniRender()
{
	_angelImg->aniRender(getMemDC(), _rc.left, _rc.top, _angelAni);
}