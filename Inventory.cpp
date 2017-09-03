#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

HRESULT Inventory::init(float x, float y)
{
	_cam.x = x;
	_cam.y = y;
	
	IMAGEMANAGER->addImage("Inven", "image/UI/Inven.bmp", 480, 292, false, false);
	IMAGEMANAGER->addImage("InvenText", "image/UI/InvenText.bmp", 480, 116, false, false);

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update(float x, float y)
{
	_cam.x = x;
	_cam.y = y;
}

void Inventory::render()
{
	if (KEYMANAGER->isToggle('Q'))
	{
		IMAGEMANAGER->findImage("Inven")->render(getMemDC(), CENTERX - IMAGEMANAGER->findImage("Inven")->getWidth() / 2 + _cam.x , CENTERY - 200 + _cam.y);
		IMAGEMANAGER->findImage("InvenText")->render(getMemDC(), CENTERX - IMAGEMANAGER->findImage("InvenText")->getWidth() / 2 + _cam.x, CENTERY + 100 + _cam.y);
	}

	
}
