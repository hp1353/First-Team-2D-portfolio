#include "stdafx.h"
#include "E_Parent_bullet.h"
#include "Player.h"


E_Parent_bullet::E_Parent_bullet()
{
}


E_Parent_bullet::~E_Parent_bullet()
{
}

HRESULT E_Parent_bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

bool E_Parent_bullet::CollisionPlayer(vector<EnemyBullet>::iterator viBullet)
{
	vector<EnemyBullet>::iterator tempBullet = viBullet;

	RECT temp;

		if (IntersectRect(&temp, &viBullet->rc, &_player->getPlayer()->getRect()))
		{
			_player->getPlayer()->minToCHP(2);
			_player->isHit(true);
			return true;
		}
	return false;
}

void E_Parent_bullet::fire(float x, float y, float angle, float speed, int Damage, int Direction, const char* MapName)
{
	//최대 발사 갯수 제한
	if (_bulletMax < _vBullet.size()) return;

	_MapName = MapName;


	EnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(EnemyBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.fire = true;
	bullet._Damage = Damage;
	bullet.angle = angle;
	bullet.bulletFrame = Direction;
	bullet.bulletFrameY = 0;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet._Gravity = 0;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());
	bullet._WorldTime = TIMEMANAGER->getWorldTime();

	_vBullet.push_back(bullet);

}
void E_Parent_bullet::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		//Rectangle(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].rc.right, _vBullet[i].rc.bottom);
		//_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->bulletFrame,0);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].bulletFrame, _vBullet[i].bulletFrameY);
	}
}
void E_Parent_bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}



E_DetectPixel E_Parent_bullet::PixelDetect(vector<EnemyBullet>::iterator viBullet)
{
	E_DetectPixel _isPixel = { false, false, false, false };
	COLORREF color;
	//아래 검사
	for (int i = _viBullet->rc.bottom; i > _viBullet->rc.bottom+1; i++)
	{
		color = GetPixel(IMAGEMANAGER->findImage(_MapName)->getMemDC(), _viBullet->rc.left + (_viBullet->rc.right - _viBullet->rc.left) / 2, i);
		if ((color == 0x00ff00)) {
			_isPixel._PBottom = true; break;
		}
		else _isPixel._PBottom = false;
	}


	//탑 검사
	for (int i = _viBullet->rc.top; i < _viBullet->rc.top + 1; i++)
	{
		color = GetPixel(IMAGEMANAGER->findImage(_MapName)->getMemDC(), _viBullet->rc.left + (_viBullet->rc.right - _viBullet->rc.left) / 2, i);
		if ((color == 0x00ff00)) {
			_isPixel._PTop = true; break;
		}
		else _isPixel._PTop = false;
	}


	//왼쪽 검사
	for (int i = _viBullet->rc.left - 1; i < _viBullet->rc.left + 1; i++)
	{
		color = GetPixel(IMAGEMANAGER->findImage(_MapName)->getMemDC(), i, _viBullet->rc.top + (_viBullet->rc.bottom - _viBullet->rc.top) / 2);
		if ((color == 0x00ff00)) {
			_isPixel._PLeft = true; break;
		}
		else _isPixel._PLeft = false;
	}

	//오른쪽 검사
	for (int i = _viBullet->rc.right + 1; i > _viBullet->rc.right - 1; i--)
	{
		color = GetPixel(IMAGEMANAGER->findImage(_MapName)->getMemDC(), i, _viBullet->rc.top + (_viBullet->rc.bottom - _viBullet->rc.top) / 2);
		if ((color == 0x00ff00)) {
			_isPixel._PRight = true; break;
		}
		else _isPixel._PRight = false;
	}

	return _isPixel;
}

const char* E_Parent_bullet::ImageChange(const char* ImageKey)
{
	_imageName = ImageKey;
	return _imageName;
}