#pragma once
#include "Parent_bullet.h"

class FireBall : public Parent_bullet
{

public:
	FireBall();
	~FireBall();

	void update();
	void release();
	void move();

	void PixelCollision(vector<tagBullet>::iterator _viBullet, DetectPixel pixelCollision);



};
