#include "stdafx.h"
#include "FireBall.h"


FireBall::FireBall()
{
}


FireBall::~FireBall()
{
}

void FireBall::release()
{

}

void FireBall::update()
{
	_count++;
	this->move();
}

void FireBall::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->_BulletType = FIRE_BALL;
		_viBullet->_Gravity += 0.1f;

		
		_viBullet->rc.left += cosf(_viBullet->angle) * (_viBullet->speed);
		_viBullet->rc.right = _viBullet->rc.left + 22;

		_viBullet->rc.top += -sinf(_viBullet->angle) * (_viBullet->speed) + _viBullet->_Gravity;
		_viBullet->rc.bottom = _viBullet->rc.top + 24;

		DetectPixel _pixel = PixelDetect(_viBullet);
		PixelCollision(_viBullet, _pixel);

		
		_viBullet->count++;
		if (_viBullet->count % 3 == 2 && _viBullet->_WeaponLv == 2)
		{
			EFFECTMANAGER->play("FireLv2", _viBullet->rc.left + (_viBullet->rc.right - _viBullet->rc.left)/2, _viBullet->rc.top + (_viBullet->rc.bottom - _viBullet->rc.top)/2);
			_viBullet->count = 0;
		}
		else if (_viBullet->count % 3 == 2 && _viBullet->_WeaponLv == 3)
		{
			EFFECTMANAGER->play("FireLv3", _viBullet->rc.left + (_viBullet->rc.right - _viBullet->rc.left) / 2, _viBullet->rc.top + (_viBullet->rc.bottom - _viBullet->rc.top) / 2);
			_viBullet->count = 0;
		}


		if (_count % 2 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->bulletFrame++;
			if (_viBullet->bulletFrame > _viBullet->bulletImage->getFrameX())
				_viBullet->bulletFrame = 0;
		}
	


		if (CollisionEnemy(_viBullet))
		{
			_viBullet = _vBullet.erase(_viBullet);
			//exit(0);
		}
		else if (_viBullet->_WorldTime + 2.0f <= TIMEMANAGER->getWorldTime() )
		{
			EFFECTMANAGER->play("±âº»ÃÑÀÌÆåÆ®", _viBullet->rc.left, _viBullet->rc.top);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;
		
		
	}
}


void FireBall::PixelCollision(vector<tagBullet>::iterator _viBullet, DetectPixel pixelCollision)
{
	
	if (pixelCollision._PBottom)
	{
		if (!SOUNDMANAGER->isPlaySound("FireBallWall"))
		SOUNDMANAGER->play("FireBallWall", 1.0f);
		_viBullet->_Gravity = 0.f;
		_viBullet->rc.bottom = _viBullet->rc.bottom - 5;
		_viBullet->rc.top = _viBullet->rc.bottom - 24;
		_viBullet->angle = 2 * PI - _viBullet->angle;
	}
	else if (pixelCollision._PTop)
	{
		if (!SOUNDMANAGER->isPlaySound("FireBallWall"))
		SOUNDMANAGER->play("FireBallWall", 1.0f);
		_viBullet->rc.top = _viBullet->rc.top + 5;
		_viBullet->rc.bottom = _viBullet->rc.top + 24;
	}

	if (pixelCollision._PLeft)
	{
		if(!SOUNDMANAGER->isPlaySound("FireBallWall"))
		SOUNDMANAGER->play("FireBallWall", 1.0f);
		_viBullet->rc.left = _viBullet->rc.left + 5;
		_viBullet->rc.right = _viBullet->rc.left + 22;
		_viBullet->angle = PI - _viBullet->angle;
	
	}
	else if (pixelCollision._PRight)
	{
		if (!SOUNDMANAGER->isPlaySound("FireBallWall"))
		SOUNDMANAGER->play("FireBallWall", 1.0f);
		_viBullet->rc.right = _viBullet->rc.left - 5;
		_viBullet->rc.left = _viBullet->rc.right - 22;
	_viBullet->angle = PI - _viBullet->angle;
	}


}

