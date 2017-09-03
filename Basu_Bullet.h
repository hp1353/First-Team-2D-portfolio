#pragma once
#include "E_Parent_bullet.h"

class Basu_Bullet :public E_Parent_bullet
{


public:
	Basu_Bullet();
	~Basu_Bullet();

	void release();
	void update();
	void move();
};

