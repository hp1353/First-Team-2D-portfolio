#pragma once

#include "enemy.h"

class angel : public enemy
{
private:
	image* _angelImg;
	animation* _angelAni;

	float _speed;
	float _distance;

	bool _isRight;
	bool _isAttack;

	int _attackCount;

public:
	angel();
	~angel();

	HRESULT init(int x, int y);
	void release();
	void update(Player* player);
	void render();

	void move(Player* player);
	void attack(Player* player);

	void imgInit();
	void aniInit();
	void aniUpdate();
	void aniRender();
};

