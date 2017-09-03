#pragma once

#include "gameNode.h"
#include "TestScene.h"
#include "Parent_Weapone.h"
#include "Base_Weapone.h"
#include "Machine_Weapone.h"

struct rcCamAngle
{
	RECT rc;
	float x;
	float y;
	float movX;
	float movY;
	bool isRight;
	RECT sceneRc;
	float inertia;  //관성력
	float xAngle;
	float yAngle;
};

class cameraAngle : public gameNode
{
private:
	vector<Parent_Weapone*> _vWeapone;
	vector<Parent_Weapone*>::iterator _viWeapone;

	tagWeapone _WeaponeInfo;

	PlayerInfo* _player;
	Player* _PlayerClass;

	Parent_Weapone _Weapone;
	rcCamAngle _cam;

	image* _background;

	RECT testrc;
	image* ExpNumber;
	image* HpNumber;
	image* HpNumber10;
	image* WeaponeIconChange;
	image* WeaponeIcon;

	image* WeaponeBullet;
	image* WeaponeBullet10;
	image* WeaponeBullet100;


	image* WeaponeCurBullet;
	image* WeaponeCurBullet10;
	image* WeaponeCurBullet100;

	int crushcount;
	int allcrushcount;
	bool iscrush;
	int whitehp;

	bool _isVibe;
	int _camVibeCount;

	bool ihaverocket;
	bool ihavemachine;

	bool drawcurbullet;
	bool drawcurbullet10;
	bool drawcurbullet100;

	bool drawmaxbullet;
	bool drawmaxbullet10;
	bool drawmaxbullet100;


public:
	cameraAngle();
	~cameraAngle();

	HRESULT init(PlayerInfo* _Player, Parent_Weapone* Weapone, vector<Parent_Weapone*> vWeapone);
	void release();
	void update();
	void render();

	void camVibeSwitch();
	void cameraVibration();	//카메라 진동
	void crushevent();
	void numbercontrol();

	void GetPlayerInfo(PlayerInfo* _Player, Parent_Weapone* Weapone, vector<Parent_Weapone*> vWeapone)
	{
		_player = _Player;
		_Weapone = *Weapone;
		_vWeapone = vWeapone;
	}

	float getCamX() { return _cam.x; }
	float getCamY() { return _cam.y; }

	void setCamX(int x) { _cam.x = x; }
	void setCamY(int y) { _cam.y = y; }

	void setCamPos();
};

