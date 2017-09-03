#pragma once

#include "enemy.h"
#include "BossBall.h"
#include "Wood.h"
#include "Pop.h"
#include "progressBar.h"

class Player;

typedef vector<BossBall*> _arrBall;
typedef vector<BossBall*>::iterator _iterBall;

typedef vector<Wood*> _arrWood;
typedef vector<Wood*>::iterator _iterWood;



class BossBody : public enemy
{
private:
	_arrBall _vBall;
	_arrWood _vWood;

	Pop* _bullet;

	Player* _player;

	image* _bossBodyImg;
	progressBar* _hpbar;

	image* _progressBarForward;
	image* _progressBarBack;

	string _bossImgName;
	const char* _imageName;

	RECT _movRect;
	RECT _headRect;

	BOSSSTATUS _phase;
	BOSSMOVE _motion;

	float _speed;
	float _power;
	float _gravity;

	int _jumpCount;   //점프 쿨타임
	int _transCount; //변신 쿨타임
	int _woodPopCount; //나무판자 팝업 쿨타임
	int _soundCount; //phase2 소리
	int _pattern;

	int _stageNum;
	int boomrndx;
	int boomrndy;
	bool _transed;
	int _spikeY;
	image* hpBarBottom;
	int alphanum;

	bool _isTheEnd;
	bool _isHurt;

public:
	BossBody();
	~BossBody();

	HRESULT init(int x, int y, const char* imageName);
	void release(bool isBoss);
	void update(bool isBoss);
	void render(bool isBoss);
	//
	void phase1();
	void phase2();
	void phase3();
	void phase4();

	//PHASE_1 ACTION
	void jump();
	void phase1_pxlCollision();
	//총알 나중에

	//PHASE_2 ACTION
	void phase2_pxlCollision();
	void phase2_move();
	void phase2_bollCollision();

	//PHASE_3 ACTION
	void bossTrans();
	void ballSpin();
	void woodSpin();


	//
	void bossdead();


	void imgInit();

	void phase1_render();
	void phase2_render();
	void phase3_render();
	void phase4_render();


	//VECTOR함수
	void addBall(int x, int y, float angle);
	void addWood(int x, int y, float angle);
	void clear(bool isBoss);

	_arrBall getVBall() { return _vBall; }
	_arrWood getVWood() { return _vWood; }
	bool getTransed() { return _transed; }

	void takeHit(int dmg);
	void hurt();

	int getStageNum() { return _stageNum; }

	bool isTheEnd() { return _isTheEnd; }


	void setPlayerLink(Player* player) { _player = player; }

	void ProgressBarRender();

};

