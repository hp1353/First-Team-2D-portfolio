#pragma once

#include "enemy.h"

class bat : public enemy
{
private:
	image* _batImg;
	animation* _batFly;

	float _posY;
	float _flyPower;
	bool _isRight;

public:
	bat();
	~bat();

	HRESULT init(int x, int y, float angle, float flyPower);
	void release();
	void update(Player* player);
	void render();

	void fly();
	void checkDirection();

	void imgInit();
	void aniInit();
	void aniUpdate();
	void aniRender();
};

