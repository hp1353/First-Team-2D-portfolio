#include "stdafx.h"
#include "Item_Exp.h"
extern float MusicMasterVol;
extern float SoundMasterVol;

Item_Exp::Item_Exp()
{
}


Item_Exp::~Item_Exp()
{
}

void Item_Exp::ItemUse(int i)
{
	SOUNDMANAGER->play("경험치습득", SoundMasterVol);
	_playerInfo->getVWeapone()[_playerInfo->getPlayer()->_WeaponeIndex]->GetExp(i);
	_playerInfo->PlusNumShowOn(i);
	//_playerInfo->PlusNumTimeSave();
	//_

}

void Item_Exp::Move(const char* _PixelMap)
{
	_gravity += 0.2f;


	_ItemBox.left += cosf(_angle) * (_speed);
	_ItemBox.right = _ItemBox.left + 22;

	_ItemBox.top += -sinf(_angle) * (_speed) + _gravity;
	_ItemBox.bottom = _ItemBox.top + 24;

	Pixel _pixel = PixelDetect(_PixelMap);
	PixelCollision( _pixel);
}

void Item_Exp::PixelCollision(Pixel pixelCollision)
{

	if (pixelCollision._PBottom)
	{
		if (!SOUNDMANAGER->isPlaySound("경험치 아이템 팅기는 소리") && 
			MY_UTIL::getDistance(_playerInfo->getPlayer()->getX(), _playerInfo->getPlayer()->getY(), _ItemBox.left,_ItemBox.top) <= 300)
			SOUNDMANAGER->play("경험치 아이템 팅기는 소리", SoundMasterVol);
		_gravity = 0.f;
		_ItemBox.bottom = _ItemBox.bottom - 5;
		_ItemBox.top = _ItemBox.bottom - 24;
		_angle = 2 * PI - _angle;
	}
	else if (pixelCollision._PTop)
	{
		if (!SOUNDMANAGER->isPlaySound("경험치 아이템 팅기는 소리") &&
			MY_UTIL::getDistance(_playerInfo->getPlayer()->getX(), _playerInfo->getPlayer()->getY(), _ItemBox.left, _ItemBox.top) <= 300)
			SOUNDMANAGER->play("경험치 아이템 팅기는 소리", SoundMasterVol);
		_ItemBox.top = _ItemBox.top + 5;
		_ItemBox.bottom = _ItemBox.top + 24;
	}

	if (pixelCollision._PLeft)
	{
		if (!SOUNDMANAGER->isPlaySound("경험치 아이템 팅기는 소리") &&
			MY_UTIL::getDistance(_playerInfo->getPlayer()->getX(), _playerInfo->getPlayer()->getY(), _ItemBox.left, _ItemBox.top) <= 300)
			SOUNDMANAGER->play("경험치 아이템 팅기는 소리", SoundMasterVol);
		_ItemBox.left = _ItemBox.left + 5;
		_ItemBox.right = _ItemBox.left + 22;
		_angle = PI - _angle;

	}
	else if (pixelCollision._PRight)
	{
		if (!SOUNDMANAGER->isPlaySound("경험치 아이템 팅기는 소리") &&
			MY_UTIL::getDistance(_playerInfo->getPlayer()->getX(), _playerInfo->getPlayer()->getY(), _ItemBox.left, _ItemBox.top) <= 300)
			SOUNDMANAGER->play("경험치 아이템 팅기는 소리", SoundMasterVol);
		_ItemBox.right = _ItemBox.left - 5;
		_ItemBox.left = _ItemBox.right - 22;
		_angle = PI - _angle;
	}
}