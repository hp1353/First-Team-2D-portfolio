#pragma once
#include "Parent_Weapone.h"

class Base_Weapone :public Parent_Weapone
{
	bullet* _Basebullet;

public:

	HRESULT init(EnemyFullManager* enemyManager);
	void release();
	void update();
	void BulletRender(POINT XY);
	void ChangeDirection(bool Right, int State, POINT XY);
	void Fire( POINT XY, float angle, float speed, int Direction);
	int LvUp();
	int LvDown();
	void BulletImageUpdate();

	void LinkToEnemy(EnemyFullManager* enemyManager);

	Base_Weapone();
	~Base_Weapone();
};

