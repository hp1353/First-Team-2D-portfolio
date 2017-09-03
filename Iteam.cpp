#include "stdafx.h"
#include "Iteam.h"

#include "Player.h"

Item::Item()
{
}


Item::~Item()
{
}

HRESULT Item::init(ImageString FileName, int x, int y, int Item)
{
	_FileName = FileName._FileName;
	_ItemImage = IMAGEMANAGER->findImage(_FileName);
	_ItemBox = RectMake(x, y ,IMAGEMANAGER->findImage(_FileName)->getWidth()/2, IMAGEMANAGER->findImage(_FileName)->getHeight());
	
	_spawnTime = TIMEMANAGER->getWorldTime();
	_Sort = Item;
	_isTwinkle = false;

	
	_MaxHpItem = 0;
	switch (_Sort)
	{
		//여기사 수치 조정.
	case I_HEAL_HEALTH: case I_MAX_ROCKET_BULLET :case I_ROCKET_BULLET:
		_ItemPoint = 3;
		break;
	case I_MUCH_HEAL_HEALTH:
		_ItemPoint = 6;
		break;
	case I_EXP:
		_ItemPoint = 1;
		break;
	case I_MUCH_EXP:
		_ItemPoint = 3;
		break;
	}

	_isDropItem = false;

	_count = 0;
	_index = 0;
	_TwinkleCount = 0;
	_TwinkleInteval = 24;
	_angle = -(PI /2 +RND->getFromFloatTo(-0.1f,0.1f));
	_speed = 1.5f;
	_gravity = 0.f;

	return S_OK;
}

HRESULT Item::init(ImageString FileName, int x, int y, int Item, bool DropItem)
{
	this->init(FileName, x, y, Item);

	if (DropItem)
	{
		_DeleteTime = TIMEMANAGER->getWorldTime() + 10.0f;
		_isDropItem = true;
	}
	return S_OK;
}

void Item::release()
{

}

void Item::render()
{
	FrameUpdate();

	if (_isTwinkle)
	{
		_TwinkleCount++;
		if (_TwinkleCount %_TwinkleInteval >= _TwinkleInteval/2 ) return; 
	}

		IMAGEMANAGER->findImage(_FileName)->frameRender(getMemDC(), _ItemBox.left, _ItemBox.top);
}



void Item::FrameUpdate()
{
	
	_count++;
	_ItemImage->setFrameY(0);
	if (_count % 7 == 0)
	{
		_ItemImage->setFrameX(_index);
		_index++;
		if (_index > _ItemImage->getMaxFrameX())
		{
			_index = 0;
		}
	}
}




Pixel Item::PixelDetect(const char* PixelName)
{
	COLORREF color;
	Pixel _isPixel;

	for (int i = _ItemBox.bottom ; i > _ItemBox.bottom - 1; i--)
	{
		color = GetPixel(IMAGEMANAGER->findImage(PixelName)->getMemDC(), _ItemBox.left + (_ItemBox.right - _ItemBox.left) / 2, i);
		if ((color == 0x00ff00)) {
			_isPixel._PBottom = true; break;
		}
		else _isPixel._PBottom = false;
	}


	//탑 검사
	for (int i = _ItemBox.top ; i <  _ItemBox.top + 1; i++)
	{
		color = GetPixel(IMAGEMANAGER->findImage(PixelName)->getMemDC(), _ItemBox.left + (_ItemBox.right - _ItemBox.left) / 2, i);
		if ((color == 0x00ff00)) {
			_isPixel._PTop = true; break;
		}
		else _isPixel._PTop = false;
	}


	//왼쪽 검사
	for (int i = _ItemBox.left - 1; i < _ItemBox.left + 2; i++)
	{
		color = GetPixel(IMAGEMANAGER->findImage(PixelName)->getMemDC(), i, _ItemBox.top + (_ItemBox.bottom - _ItemBox.top) / 2);
		if ((color == 0x00ff00)) {
			_isPixel._PLeft = true; break;
		}
		else _isPixel._PLeft = false;
	}

	//오른쪽 검사
	for (int i = _ItemBox.right + 1; i > _ItemBox.right - 2; i--)
	{
		color = GetPixel(IMAGEMANAGER->findImage(PixelName)->getMemDC(), i, _ItemBox.top + (_ItemBox.bottom - _ItemBox.top) / 2);
		if ((color == 0x00ff00)) {
			_isPixel._PRight = true; break;
		}
		else _isPixel._PRight = false;
	}
	return _isPixel;

}