#pragma once

#include "enemy.h"

enum BEETLESTATE
{
	WALL,
	FLY
};

class beetle : public enemy
{
private:
	image* _beetleImg;
	animation* _beetleAni;

	const char* _imgName;

	BEETLESTATE _state;
	int _idleCounter;
	float _speed;
	bool _isRight;

public:
	beetle();
	~beetle();

	HRESULT init(int x, int y, bool isRight, const char* imageName);
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

