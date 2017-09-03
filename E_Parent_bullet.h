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
	int count; //������ ���� ��
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

	// ����ȭ ���Ѽ� �ٸ� �ڽĿ��� �� �Լ�
	//=================================
	virtual void release() {};
	virtual void update() {};
	virtual void move() {};

	// ================================


	virtual HRESULT init(const char* imageName, int bulletMax, float range);

	//�ҷ� �̹��� �ٲٰ� �ʹٸ� ����~
	virtual const char* ImageChange(const char* ImageKey);

	//�ø���� �Ѿ��� �浹
	virtual bool CollisionPlayer(vector<EnemyBullet>::iterator viBullet);

	//�߻�!!! ���̷����� �ƹ����Գ� �־ ����!!
	virtual void fire(float x, float y, float angle, float speed, int Damage, int Direction, const char* MapName);
	virtual void render();

	//���� ���° �Ҹ� ���﷡?
	virtual void removeBullet(int arrNum);

	//�ȼ� ���� �Լ�
	virtual E_DetectPixel PixelDetect(vector<EnemyBullet>::iterator viBullet);

	virtual vector<EnemyBullet> getVBullet() { return _vBullet; }
	virtual vector<EnemyBullet>::iterator getVIBullet() { return _viBullet; }

	virtual void LinkToEnemy(Player *player) { _player = player; }
};

