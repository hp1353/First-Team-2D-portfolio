#pragma once

#include "Parent_bullet.h"


class bullet : public Parent_bullet
{

public:
	bullet();
	~bullet();

	void release();
	void update();
	void move();
};

