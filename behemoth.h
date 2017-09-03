#pragma once

#include "enemy.h"

class behemoth : public enemy
{
private:
	image* _behemothImg;
	animation* _behemothPeace;
	animation* _behemothRage;

	const char* _imgName;

	bool _isRight;
	bool _isRage;

	int _soundCount;
	float _speed;

public:
	behemoth();
	~behemoth();

	HRESULT init(int x, int y, const char* imageName);
	void release();
	void update(Player* player);
	void render();

	void checkRage();
	void move();

	void leftPxl();
	void rightPxl();

	void imgInit();
	void aniInit();
	void aniUpdate();
	void aniRender();
};

