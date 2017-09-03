#pragma once

#include "enemy.h"

class basil : public enemy
{
private:
	image* _basilImg;
	animation* _basilAni;

	const char* _imgName;

	float _pivot;
	float _speed;
	bool _isRight;

public:
	basil();
	~basil();

	HRESULT init(int x, int y, const char* imageName);
	void release();
	void update(Player* player);
	void render();

	void move();

	void leftPxl();
	void rightPxl();

	void imgInit();
	void aniInit();
	void aniUpdate();
	void aniRender();
};

