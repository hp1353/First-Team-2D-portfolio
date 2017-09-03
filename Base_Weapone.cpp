#include "stdafx.h"
#include "Base_Weapone.h"


Base_Weapone::Base_Weapone()
{
}


Base_Weapone::~Base_Weapone()
{
}


HRESULT Base_Weapone::init(EnemyFullManager* enemyManager)
{
	_Weapone._Atk = 1;
	_Weapone._AtkSpeed = 5;
	_Weapone._CurBullet = 50;
	_Weapone._CurExp = 0;
	_Weapone._isRight = false;
	_Weapone._Lv = 1;
	_Weapone._MaxBullet = 100;
	_Weapone._MaxExp = 7;
	_Weapone._Weapone = BASE_GUN;
	_Weapone._range = 120;
	_Weapone._WeaponeImage = IMAGEMANAGER->addFrameImage("BaseWeapone", "image/Weapone/BaseWeapone.bmp", 0, 0, 34, 42, 2, 3, true, RGB(255, 0, 255));


	_Basebullet = new bullet;
	_Basebullet->init("BaseBullet1", _Weapone._CurBullet, _Weapone._range, enemyManager);
	_BulletImageName = "BaseBullet1";

	return S_OK;
}
void Base_Weapone::release()
{

}
void Base_Weapone::update()
{
	_Basebullet->update();
	LvUp();
	LvDown();
	BulletImageUpdate();
}
void Base_Weapone::BulletRender(POINT XY)
{
	_Basebullet->render();
}

void Base_Weapone::Fire(POINT XY, float angle, float speed, int Direction)
{
	if (KEYMANAGER->isOnceDown('X') && BulletMinus() >= 0)
	{
		_Weapone._CurBullet += 1;
		SOUNDMANAGER->play("MachineGun", SoundMasterVol);
		_Basebullet->fire(XY.x, XY.y, angle, speed, _Weapone._Atk, Direction, _pxlMapName, _Weapone._Lv, _Weapone._range);
		EFFECTMANAGER->play("기본총이펙트", XY.x, XY.y);
	}

}

void Base_Weapone::BulletImageUpdate()
{
	switch (_Weapone._Lv)
	{
	case 1:
		_BulletImageName = _Basebullet->ImageChange("BaseBullet1");
		break;
	case 2:
		_BulletImageName = _Basebullet->ImageChange("BaseBullet2");
		break;
	case 3:
		_BulletImageName = _Basebullet->ImageChange("BaseBullet3");
		break;
	}

}

void Base_Weapone::ChangeDirection(bool Right, int State, POINT XY)
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

int Base_Weapone::LvUp()
{
	if (_Weapone._MaxExp < _Weapone._CurExp)
	{
		if (_Weapone._Lv < 3)
		{
			EFFECTMANAGER->play("LevelUp", _Weapone._PlayerX, _Weapone._PlayerY - 30);
			SOUNDMANAGER->play("레벨업", SoundMasterVol);
			_Weapone._Lv += 1;  //무기 레벨업
			_Weapone._MaxExp += 2;  // 무기의 최대 경험치 상승
			_Weapone._CurExp = 0;  //무기의 경험치를 초기화
			_Weapone._range += 90;  //무기 사정거리 업
			_Weapone._speed += 0;

			if (_Weapone._Lv == 2)
			{
				_Weapone._Atk += 1;

			}
			else if (_Weapone._Lv == 3)
			{
				_Weapone._Atk += 2;

			}
		}
		else if (_Weapone._Lv == 3)
		{
			_Weapone._CurExp = _Weapone._MaxExp;
		}
	}
	return _Weapone._Lv;
}

int Base_Weapone::LvDown()
{
	if (_Weapone._CurExp < 0 && _Weapone._Lv >= 2)
	{
		EFFECTMANAGER->play("LevelDown", _Weapone._PlayerX, _Weapone._PlayerY - 30);
		SOUNDMANAGER->play("레벨다운", SoundMasterVol);
		_Weapone._Lv -= 1;  //무기 레벨업
		_Weapone._MaxExp -= 2;  // 무기의 최대 경험치 상승
		_Weapone._CurExp = _Weapone._MaxExp;  //무기의 경험치를 초기화
		_Weapone._range -= 90;  //무기 사정거리 업
		_Weapone._speed += 0;

		if (_Weapone._Lv == 1)
		{
			_Weapone._Atk -= 1;
		}
		else if (_Weapone._Lv == 2)
		{
			_Weapone._Atk -= 2;

		}

	}
	return _Weapone._Lv;
}


void Base_Weapone::LinkToEnemy(EnemyFullManager* enemyManager)
{
	_eManager = enemyManager;
	_Basebullet->init(_BulletImageName, _Weapone._CurBullet, _Weapone._range, enemyManager);

}