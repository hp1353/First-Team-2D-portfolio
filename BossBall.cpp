#include "stdafx.h"
#include "BossBall.h"


BossBall::BossBall()
{
}


BossBall::~BossBall()
{
}

HRESULT BossBall::init(int x, int y, float angle, const char* imageName)
{
	imgInit();

	_x = cosf(_angle) * _radius + x;
	_y = -sinf(_angle) * _radius + y;
	_width = _eyeOpenImg->getFrameWidth();
	_height = _eyeOpenImg->getFrameHeight();
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	_currentHP = _maxHP = 20;
	_damage = 5;
	_isDead = false;
	_MonsterType = E_BALL;
	_playX = 0;
	_playY = 0;

	_imageName = imageName;
	_hurtSound = "enemy_hurt";

	_isHit = false;
	_angle = angle;
	_speed = 0.03f;
	_radius = 160;

	_skull = new Skull;
	_skull->init("effect_skul", 0, BOSSCENTERY * 2);

	return S_OK;
}

void BossBall::release()
{

}

void BossBall::update(Player* player, bool isBoss)
{
	_rc = RectMakeCenter((int)_x, (int)_y, _width, _height);
	pxlCollision();
	_skull->LinkToEnemy(player);
	_skull->update();
	dealDmg(player);
	checkDead();
	if (_isDead) _hurtSound = "enemy_block";
	else _hurtSound = "enemy_hurt";
}

void BossBall::pxlCollision()
{
	image* img = IMAGEMANAGER->findImage(_imageName);

	//BOTTOM
	
		COLORREF color = GetPixel(img->getMemDC(), _x, _rc.bottom);
		if (color == 0x00ff00) {
			EFFECTMANAGER->play("effect_dustBig", _x + 40, _y + 45);
			EFFECTMANAGER->play("effect_dustBig", _x - 40, _y + 45);
			EFFECTMANAGER->play("effect_dust", _x + 27, _y + 10);
			EFFECTMANAGER->play("effect_dust", _x - 27, _y + 10);
		}

			//TOP

			color = GetPixel(img->getMemDC(), _x, _rc.top);
			if (color == 0x00ff00) {
				EFFECTMANAGER->play("effect_dustUP", _x, _y);
				EFFECTMANAGER->play("effect_dustUP", _x, _y);
				EFFECTMANAGER->play("effect_dustUP", _x, _y);
				EFFECTMANAGER->play("effect_dustUP", _x, _y);

				//"ÇØ°ñ"ÃÑ¾Ë fire() ÇÔ¼ö
				_skull->fire(_x, _y, PI / 2 + PI, 5.f, 5, 0, _imageName);
			}

				//LEFT

				color = GetPixel(img->getMemDC(), _rc.left, _y);
				if (color == 0x00ff00) {
					EFFECTMANAGER->play("effect_dustBig", _x - 25, _y);
					EFFECTMANAGER->play("effect_dust", _x - 25, _y - 35);
					EFFECTMANAGER->play("effect_dustUP", _x - 25, _y + 35);
				}

				//RIGHT

				color = GetPixel(img->getMemDC(), _rc.right, _y);
				if (color == 0x00ff00) {
					EFFECTMANAGER->play("effect_dustBig", _x + 35, _y);
					EFFECTMANAGER->play("effect_dust", _x + 25, _y - 35);
					EFFECTMANAGER->play("effect_dustUP", _x + 30, _y + 35);

				}
	}
		
void BossBall::render(bool isBoss)
{
	if (!_isDead) {
		if (!_isHurt) _eyeOpenImg->render(getMemDC(), _rc.left, _rc.top);
		else {
			_eyeHitImg->render(getMemDC(), _rc.left, _rc.top);
			_isHurt = false;
		}
		
	}
	else {
		_eyeCloseImg->render(getMemDC(), _rc.left, _rc.top);
	}
	_skull->render();
	
}

void BossBall::move(float bossBodyX, float bossBodyY)
{
	_angle += _speed;

	_x = bossBodyX + cosf(_angle) * _radius;
	_y = bossBodyY + -sinf(_angle) * _radius;
}

void BossBall::isHit(bool isHit)
{
	if (isHit == true) _isHit = true;
	else _isHit = false;
}

void BossBall::imgInit()
{
	image* img = IMAGEMANAGER->findImage("boss_bollTop");
	if (!img) {
		_eyeOpenImg = IMAGEMANAGER->addImage("boss_bollTop", "image/boss/boss_bollTop.bmp", 78, 78, true, 0xff00ff);
	}
	else {
		_eyeOpenImg = img;
	}

	img = IMAGEMANAGER->findImage("boss_bollBtm");
	if (!img) {
		_eyeCloseImg = IMAGEMANAGER->addImage("boss_bollTop", "image/boss/boss_bollBtm.bmp", 78, 78, true, 0xff00ff);
	}
	else {
		_eyeCloseImg = img;
	}

	img = IMAGEMANAGER->findImage("boss_bollHit");
	if (!img) {
		_eyeHitImg = IMAGEMANAGER->addImage("boss_bollHit", "image/boss/boss_bollHit.bmp", 78, 78, true, 0xff00ff);
	}
	else {
		_eyeHitImg = img;
	}
}

void BossBall::takeHit(int dmg)
{
	SOUNDMANAGER->play(_hurtSound, 1.f);
	_currentHP -= dmg;
	_StackedDamage += dmg;

	_DamageOutTime = TIMEMANAGER->getWorldTime() + 1;
	_isHitOut = true;
	_DamageNumUpCount = 0;

	_isHurt = true;
}