#include "stdafx.h"
#include "Basu_Bullet.h"
extern float MusicMasterVol;
extern float SoundMasterVol;

Basu_Bullet::Basu_Bullet()
{
}


Basu_Bullet::~Basu_Bullet()
{
}

void Basu_Bullet::release()
{

}
void Basu_Bullet::update()
{
	_count++;
	this->move();
}
void Basu_Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//픽셀 충돌 확인.
		E_DetectPixel _Pixel = PixelDetect(_viBullet);

		//프레임 돌리자!!!!!!!! 프레임 돌리는 코드
		if (_count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->bulletImage->setFrameY(_viBullet->bulletFrameY);
			_viBullet->bulletFrame++;
			if (_viBullet->bulletFrame > _viBullet->bulletImage->getFrameX())
				_viBullet->bulletFrame = 0;
		}

		//사거리 체크
		if (_range < MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		//픽셀 체크
		else if (_Pixel._PLeft || _Pixel._PRight || _Pixel._PTop || _Pixel._PBottom)
		{
			SOUNDMANAGER->play("MonsterBulletCollision", SoundMasterVol);
			EFFECTMANAGER->play("적총알충돌", _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);
		}
		// 플레이어와 부딫히면
		else if (CollisionPlayer(_viBullet))
		{
			SOUNDMANAGER->play("MonsterBulletCollision", SoundMasterVol);

			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;

	}
}
