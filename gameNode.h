#pragma once

#include "image.h"
//#include "MainMenu.h"

enum ITEM
{
	I_MAXHEALTH,
	I_W_MACHINE,
	I_W_FIRE,
	I_W_ROCKET,
	I_W_KNIFE,
	I_W_SNAKE,
	I_W_LASER,
	I_HEAL_HEALTH,
	I_MUCH_HEAL_HEALTH,
	I_ROCKET_BULLET,
	I_MAX_ROCKET_BULLET,
	I_EXP,
	I_MUCH_EXP


};

enum KeyInput
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_A,
	K_S,
	K_Z,
	K_X,
};

enum Motion
{
	WALK,
	WALK_UP,
	JUMP,
	IDLE,
	UP,
	JUMP_DOWN,
	EXAM,
	DIE,
	WATERDIE
};

enum SaveStage
{
	STAGE_EGG1,
	STAGE_EGG2
};


enum BULLETDIRECTION
{
	B_LEFT,
	B_RIGHT,
	B_DOWN,
	B_UP,

};

enum WEAPONE
{
	BASE_GUN,
	MACHINE_GUN,
	FIRE_BALL,
	ROCKET,
	KNIFE,
	SNAKE,
	LASER
};
enum ENEMY
{
	E_CRITTER,
	E_BASU,
	E_BEETLE,
	E_BEHEMOTH,
	E_BAT,
	E_BASIL,
	E_ANGEL,
	E_FROG,
	E_BRICK,
	E_BOSS,
	E_BALL,
	E_WOOD,
	E_ZOMBIE
};
struct tagWeapone
{
	image* _WeaponeImage;
	int _Weapone;
	int _Direction;
	POINT _XY;


	int _VectorSize;
	int _VectorCurIndex;
	string _WeaponeImageStr;

	int _PlayerX, _PlayerY;

	bool _isRight;


	int _Lv;
	int _CurExp;
	int _MaxExp;

	int _CurBullet;
	int _MaxBullet;

	int _Atk;
	int _AtkSpeed;

	float _range;
	float _speed;
};


struct PlayerInfo {
	RECT _rc;
	image* _image;
	Motion _motion;
	int _HaveWeapone;
	int x, y;

	int _Lv;
	int _MaxHP;
	int _CurHP;
	int _MaxEXP;
	int _CurEXP;
	int _WeaponeIndex;
	int _SaveX, _SaveY;
	int _SaveStagestr;
	int _Damage;


	bool _isJump; // 점프 상태이니
	bool _isAir;  // 공중에 있니 점프말고
	bool _isRight; // 너 오른쪽이니
	bool _isUp; //위 보고 있니
	bool _isDown; // 아래 보고 있니
	bool _isIwantStop; //관성 받고서 멈추고 싶니?
	bool _isWater;
	bool _isDrown;
	bool _isPixelL;
	bool _isPixelR;
	bool _isPixelCollision;
	bool _iscrush;
	bool _istopcrush;
	bool _isBossStage;
	bool _isGetZetPack;

	bool _isGetBase;
	bool _isGetMachine;
	bool _isGetRocket;
	bool _isGetFire;
	bool _isGetKnife;
	bool _isGetSnake;
	bool _isGetLaser;

	bool _isMaxHp1;
	bool _isMaxHp2;
	bool _isMaxHp3;

	float _air;
	float _gravity;  //중력
	float _Inertia;  //관성력
	float _InertiaMax;
	float _JumpPower; // 점프력
	float _knockBack;
	bool _isDie;
	bool _isWaterDie;

	int _CameraX; //카메라용
	int _CameraY;

	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	void addToX(int num) { x += num; }
	void minToX(int num) { x -= num; }
	void addToCHP(int num) { _CurHP += num; }
	void minToCHP(int num) { _CurHP -= num; _Damage = num; } //j222hk: 플레이어 피를 깍기 위한 함수, enemy와 상속 및 매니저 클래스에서 사옹됨.
	void fullHeal() { _CurHP = _MaxHP; }
	void addToMHP(int num) { _MaxHP += num; }
	void setIsRight(bool isRight) { _isRight = isRight; } //j222hk
	int getX() { return x; }
	int getY() { return y; }
	int getCHP() { return _CurHP; }
	int getMHP() { return _MaxHP; }
	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }
	Motion getMotion() { return _motion; }
};

struct ImageString
{
	const char* _FileName;
	const char* _EventBox;
	const char* _Text1;
	const char* _Text2;
};


static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", 5262, 1556);
class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	
	virtual void render();

	

	
	

	image* getBackBuffer() { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

