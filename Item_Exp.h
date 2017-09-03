#pragma once
#include "Iteam.h"

class Item_Exp :public Item
{

public:
	Item_Exp();
	~Item_Exp();

	void ItemUse(int i);
	void Move(const char* _PixelMap);
	void PixelCollision(Pixel pixelCollision);
};
