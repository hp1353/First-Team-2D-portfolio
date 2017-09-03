#pragma once

#include "gameNode.h"


enum BOSSMOVE
{
	BOSSUP,
	BOSSDOWN,
	BOSSLEFT,
	BOSSRIGHT,
	BOSSJUMP,
	BOSSGROUND
};

enum BOSSSTATUS
{
	BOSSJUMPER, //보스가 점프하는 패턴
	BOSSWHILL, // 보스톱니바퀴
	BOSSDART //보스가 중앙에서 돌면서 공격
};


struct tagBoss
{
	RECT rc;
	RECT headRc;
	image* img;
	RECT movingRc;
	float x;
	float y;
	float angle;
	float radius;
	float speed;
	float power;
	float gravity;
	float jumpCount;
	int motion;
	bool fire;
	
	animation* ani;
	bool collision;

};

struct tagBossBoll
{
	RECT rc;
	image* img;
	float x;
	float y;
	float angle;
	float radius;
	float speed;
	animation* ani;
	bool fire;
	bool collision;
};

struct tagRect
{
	RECT rc;
	image* img;
	float x;
	float y;
	float speed;
	int count;
	bool turnOn;
};
class Player;

class enemy : public gameNode
{
protected:
	RECT _rc;
	float _x;
	float _y;
	int _width;
	int _height;
	int _maxHP;
	int _currentHP;
	int _damage;
	int _MonsterType;
	int _StackedDamage;
	int _DamageOutTime;
	float _DamageNumUpCount;
	bool _isHitOut;
	bool _isDead;
	float _angle;
	float _radius;


	float _playX;
	float _playY;
	string _hurtSound;
	string _deathSound;



public:
	enemy();
	virtual ~enemy();

	virtual void update(Player* player) {}; //추가잼
	virtual void render() {};
	virtual void erase() {};

	virtual void takeHit(int dmg);
	virtual void checkDead();

	virtual int checkType() { return _MonsterType; }
	virtual int getStageNum() { return 0; }

	virtual void dealDmg(Player* player);

	virtual void kill() { _currentHP = 0; }

	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRect() { return _rc; }
	bool getIsDead() { return _isDead; }
	string getDeathrattle() { return _deathSound; }
   

	int DamageTimeReturn() { return _DamageOutTime;  }
	int StackedDamage() { return _StackedDamage; }
	void OutDamagedNum() { _isHitOut = true; }
	void UnOutDamagedNum() { _isHitOut = false;  _StackedDamage = 0;}
	bool GetOutDamage() { return _isHitOut; }
	int UpDamageNum() { return _DamageNumUpCount; };

	float woodMovementX(int num);
	


};

