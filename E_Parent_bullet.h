#pragma once

#include "gameNode.h"

#include "effect.h"
#include <vector>

class Player;

struct EnemyBullet
{
	image* bulletImage;
	RECT rc;
	
	int radius;
	int _Damage;

	float angle;
	float x, y;
	float fireX, fireY;
	float speed;
	float _Gravity;
	float _WorldTime;

	bool fire;
	int count; //프레임 돌릴 거
	int bulletFrame;
	int bulletFrameY;

};

struct E_DetectPixel
{
	bool _PRight;
	bool _PLeft;
	bool _PTop;
	bool _PBottom;
};

class E_Parent_bullet : public gameNode
{
protected:
	vector<EnemyBullet> _vBullet;
	vector<EnemyBullet>::iterator _viBullet;

	const char* _imageName;
	const char* _MapName;

	Player* _player;

	effect* _MissileEffect;
	image* _mapPxl;

	float _range;

	int _bulletMax;
	int _count;

public:
	E_Parent_bullet();
	~E_Parent_bullet();

	// 가상화 시켜서 다른 자식에서 쓸 함수
	//=================================
	virtual void release() {};
	virtual void update() {};
	virtual void move() {};

	// ================================


	virtual HRESULT init(const char* imageName, int bulletMax, float range);

	//불렛 이미지 바꾸고 싶다면 쓰라~
	virtual const char* ImageChange(const char* ImageKey);

	//플리어와 총알의 충돌
	virtual bool CollisionPlayer(vector<EnemyBullet>::iterator viBullet);

	//발사!!! 다이렉션은 아무렇게나 넣어도 노상관!!
	virtual void fire(float x, float y, float angle, float speed, int Damage, int Direction, const char* MapName);
	virtual void render();

	//벡터 몇번째 불릿 지울래?
	virtual void removeBullet(int arrNum);

	//픽셀 감지 함수
	virtual E_DetectPixel PixelDetect(vector<EnemyBullet>::iterator viBullet);

	virtual vector<EnemyBullet> getVBullet() { return _vBullet; }
	virtual vector<EnemyBullet>::iterator getVIBullet() { return _viBullet; }

	virtual void LinkToEnemy(Player *player) { _player = player; }
};

