#include "stdafx.h"
#include "bullets.h"

extern float MusicMasterVol;
extern float SoundMasterVol;

//=========================== missile ================================


//=========================== bullet ================================

bullet::bullet()
{
}

bullet::~bullet()
{
}

void bullet::release()
{

}

void bullet::update()
{
	_count++;
	this->move();
}

void bullet::move()
{
	//º¤ÅÍ¿¡ ÀÖ´Â ³à¼®µé ¿òÁ÷¿©ÁÖÀÚ
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		DetectPixel _Pixel = PixelDetect(_viBullet);
		if (_viBullet ->_range < MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			EFFECTMANAGER->play("±âº»ÃÑÀÌÆåÆ®", _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else if (_Pixel._PLeft || _Pixel._PRight || _Pixel._PTop || _Pixel._PBottom)
		{
			SOUNDMANAGER->play("ÃÑ¾Ëº®Ãæµ¹", SoundMasterVol);
			EFFECTMANAGER->play("ÃÑÃæµ¹ÀÌÆåÆ®", _viBullet->x, _viBullet->y);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else if (CollisionEnemy(_viBullet))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;
       
	
	}
}

