#pragma once

#include "enemy.h"
#include "Skull.h"

class BossBall : public enemy
{
private:
	Skull* _skull;

	image* _eyeOpenImg;
	image* _eyeCloseImg;
	image* _eyeHitImg;
	const char* _imageName;
	bool _isHit;
	float _speed;
	bool _isHurt;

public:
	BossBall();
	~BossBall();

	HRESULT init(int x, int y, float angle, const char* imageName);
	void release();
	void update(Player* player, bool isBoss);
	void render(bool isBoss);

	void pxlCollision();

	void move(float bossBodyX, float bossBodyY);
	void isHit(bool hit);

	void imgInit();

	void setSpeed(float speed) { _speed = speed; }

	void takeHit(int dmg);
};

