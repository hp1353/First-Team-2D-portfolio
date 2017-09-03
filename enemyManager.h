#pragma once

#include "gameNode.h"
#include <vector>
#include "basil.h"
#include "basu.h"
#include "bat.h"
#include "beetle.h"
#include "behemoth.h"
#include "critter.h"


//class enemyManager
//{
//private:
//
//public:
//	enemyManager();
//	~enemyManager();
//};

class basilManager
{
private:
	typedef vector<basil*> _arrBasil;
	typedef vector<basil*>::iterator _iterBasil;

	_arrBasil _vBasil;

public:
	basilManager();
	~basilManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addBasil(int x, int y);
	void eraseBasil(int arrNum);
	void clearBasil();

	_arrBasil getVBasil() { return _vBasil; }
};

class basuManager
{
private:
	typedef vector<basu*> _arrBasu;
	typedef vector<basu*>::iterator _iterBasu;

	_arrBasu _vBasu;

public:
	basuManager();
	~basuManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addBasu(int x, int y);
	void eraseBasu(int arrNum);
	void clearBasu();

	_arrBasu getVBasu() { return _vBasu; }
};

class batManager
{
private:
	typedef vector<bat*> _arrBat;
	typedef vector<bat*>::iterator _iterBat;

	_arrBat _vBat;

public:
	batManager();
	~batManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addBat(int x, int y, float angle, float power);
	void eraseBat(int arrNum);
	void clearBat();

	_arrBat getVBat() { return _vBat; }
};

class beetleManager
{
private:
	typedef vector<beetle*> _arrBeetle;
	typedef vector<beetle*>::iterator _iterBeetle;

	_arrBeetle _vBeetle;

public:
	beetleManager();
	~beetleManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addBeetle(int x, int y, bool isRight);
	void eraseBeetle(int arrNum);
	void clearBeetle();

	_arrBeetle getVBeetle() { return _vBeetle; }
};

class behemothManager
{
private:
	typedef vector<behemoth*> _arrBehemoth;
	typedef vector<behemoth*>::iterator _iterBehemoth;

	_arrBehemoth _vBehemoth;

public:
	behemothManager();
	~behemothManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addBehemoth(int x, int y);
	void eraseBehemoth(int arrNum);
	void clearBehemoth();

	_arrBehemoth getVBehemoth() { return _vBehemoth; }
};

class critterManager
{
private:
	typedef vector<critter*> _arrCritter;
	typedef vector<critter*>::iterator _iterCritter;

	_arrCritter _vCritter;

public:
	critterManager();
	~critterManager();

	HRESULT init();
	void release();
	void update(Player* player);
	void render();

	void addCritter(int x, int y);
	void eraseCritter(int arrNum);
	void clearCritter();

	_arrCritter getVCritter() { return _vCritter; }
};

