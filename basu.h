#pragma once

#include "enemy.h"
#include "E_Parent_bullet.h"
#include "Basu_Bullet.h"

class basu : public enemy
{
private:
	Basu_Bullet *_bullet;
	image* _basuImg;
	animation* _basuNormal;
	animation* _basuFire;

	//LEFT&RIGHT MOVEMENT
	float _xAngle;
	float _xPivot;
	float _xPower;
	//UP&DOWN BOBBING
	float _yAngle;
	float _yPivot;
	float _yPower;

	const char* _imgName;

	bool _isRight;
	bool _isFire;
	int _fireCount;
	int _chargeCount;

public:
	basu();
	~basu();

	HRESULT init(int x, int y, const char* imageName);
	void release();
	void update(Player* player);
	void render();

	void move();
	void fire();

	void imgInit();
	void aniInit();
	void aniUpdate();
	void aniRender();
};

