#include "stdafx.h"
#include "Fire_Weapone.h"


Fire_Weapone::Fire_Weapone()
{

}


Fire_Weapone::~Fire_Weapone()
{

}


HRESULT Fire_Weapone::init(EnemyFullManager* enemyManager)
{
	_Weapone._Atk = 2;
	_Weapone._AtkSpeed = 5;
	_Weapone._CurBullet = 3;
	_Weapone._CurExp = 0;
	_Weapone._isRight = false;
	_Weapone._Lv = 1;

	_Weapone._MaxBullet = 2;
	_Weapone._MaxExp = 7;
	_Weapone._Weapone = FIRE_BALL;
	_Weapone._range = 500;
	_Weapone._WeaponeImage = IMAGEMANAGER->addFrameImage("FireWeapone", "image/Weapone/FireWeapone.bmp", 0, 0, 34, 51, 2, 3, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("LaserWeapone", "image/Weapone/LaserWeapone.bmp", 0, 0, 126, 21, 6, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("SnakeWeapone", "image/Bullet/SnakeWeapone.bmp", 0, 0, 138, 23, 6, 1, true, RGB(255, 0, 255));

	_Firebullet = new FireBall;
	_Firebullet->init("FireBullet1", _Weapone._CurBullet, _Weapone._range, enemyManager);

	return S_OK;
}
void Fire_Weapone::release()
{

}
void Fire_Weapone::update()
{
	_Firebullet->update();
	LvUp();
	LvDown();
	BulletImageUpdate();
}
void Fire_Weapone::BulletRender(POINT XY)
{
	_Firebullet->render();
}

void Fire_Weapone::Fire(POINT XY, float angle, float speed, int Direction)
{


	if (KEYMANAGER->isOnceDown('X') )
	{
		if (_Firebullet->getVBullet().size() < _Weapone._MaxBullet)
		{
			_Firebullet->fire(XY.x, XY.y, angle, speed, _Weapone._Atk, Direction, _pxlMapName, _Weapone._Lv,_Weapone._range);
			EFFECTMANAGER->play("기본총이펙트", XY.x, XY.y);
		}
	}

}

void Fire_Weapone::ChangeDirection(bool Right, int State, POINT XY)
{
	_Weapone._PlayerX = XY.x;
	_Weapone._PlayerY = XY.y;
	_Weapone._isRight = Right;

	switch (State)
	{
	case JUMP: case WALK: case IDLE:
		_FrameY = 0;
		if (Right)
		{
			_FrameX = 1;

			_Weapone._XY.x = XY.x + 7;
			_Weapone._XY.y = XY.y - 5;
		}
		else
		{
			_FrameX = 0;
			_Weapone._XY.x = XY.x - 15;
			_Weapone._XY.y = XY.y - 5;

		}
		break;
	case JUMP_DOWN:
		_FrameY = 1;
		if (Right)
		{
			_FrameX = 1;
			_Weapone._XY.x = XY.x - 7;
			_Weapone._XY.y = XY.y + 5;

		}
		else
		{
			_FrameX = 0;
			_Weapone._XY.x = XY.x - 7;
			_Weapone._XY.y = XY.y + 5;

		}
		break;
	case WALK_UP: case UP:
		_FrameY = 2;
		if (Right)
		{
			_FrameX = 1;
			_Weapone._XY.x = XY.x;
			_Weapone._XY.y = XY.y - 25;

		}
		else
		{
			_FrameX = 0;
			_Weapone._XY.x = XY.x - 7;
			_Weapone._XY.y = XY.y - 25;
		}
		break;
	}

}

int Fire_Weapone::LvUp()
{
	if (_Weapone._MaxExp < _Weapone._CurExp)
	{
		if (_Weapone._Lv < 3)
		{
			_Weapone._Lv += 1;  //무기 레벨업
			_Weapone._MaxExp += 2;  // 무기의 최대 경험치 상승
			_Weapone._CurExp = 0;  //무기의 경험치를 초기화
			_Weapone._speed += 1.0f;

			EFFECTMANAGER->play("LevelUp", _Weapone._PlayerX, _Weapone._PlayerY - 30);
			SOUNDMANAGER->play("레벨업", SoundMasterVol);
			_Weapone._Atk += 1;
			_Weapone._MaxBullet += 1;
		}
		else if (_Weapone._Lv == 3)
		{
			_Weapone._CurExp = _Weapone._MaxExp;
		}
	}

	return _Weapone._Lv;
}

void Fire_Weapone::BulletImageUpdate()
{
	switch (_Weapone._Lv)
	{
	case 1:
		_BulletImageName = _Firebullet->ImageChange("FireBullet1");
		break;
	case 2:
		_BulletImageName = _Firebullet->ImageChange("FireBullet2");
		break;
	case 3:
		_BulletImageName = _Firebullet->ImageChange("FireBullet3");
		break;
	}

}

int Fire_Weapone::LvDown()
{
	if (_Weapone._CurExp < 0 && _Weapone._Lv >= 2)
	{
		EFFECTMANAGER->play("LevelDown", _Weapone._PlayerX, _Weapone._PlayerY - 30);
		SOUNDMANAGER->play("레벨다운", SoundMasterVol);
		_Weapone._Lv -= 1;  //무기 레벨업
		_Weapone._MaxExp -= 2;  // 무기의 최대 경험치 상승
		_Weapone._CurExp = _Weapone._MaxExp;  //무기의 경험치를 초기화  //무기 사정거리 업
		_Weapone._speed -= 1.0;
		_Weapone._Atk -= 1;
		_Weapone._MaxBullet -= 1;
	}
	return _Weapone._Lv;
}

void Fire_Weapone::LinkToEnemy(EnemyFullManager* enemyManager)
{
	_eManager = enemyManager;
	_Firebullet->init(_BulletImageName, _Weapone._CurBullet, _Weapone._range, enemyManager);
}



