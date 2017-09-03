#pragma once
#include "Parent_Weapone.h"

class Fire_Weapone :public Parent_Weapone
{

	FireBall* _Firebullet;
	int RandomFireY;

public:

	HRESULT init(EnemyFullManager* enemyManager);
	void release();
	void update();
	void BulletRender(POINT XY);
	void ChangeDirection(bool Right, int State, POINT XY);

	void Fire(POINT XY, float angle, float speed, int Direction);
	int LvUp();
	int LvDown();
	void BulletImageUpdate();

	void LinkToEnemy(EnemyFullManager* enemyManager);

	Fire_Weapone();
	~Fire_Weapone();
};
