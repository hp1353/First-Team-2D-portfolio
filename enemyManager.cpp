#include "stdafx.h"
#include "enemyManager.h"
#include "Player.h"


//enemyManager::enemyManager()
//{
//}
//
//
//enemyManager::~enemyManager()
//{
//}

//BASIL MANAGER
basilManager::basilManager()
{
}

basilManager::~basilManager()
{
}

HRESULT basilManager::init()
{
	return S_OK;
}

void basilManager::release()
{
	clearBasil();
}

void basilManager::update(Player* player)
{
	for (int i = 0; i < _vBasil.size(); i++)
	{
		_vBasil[i]->update(player);
	}
}

void basilManager::render()
{
	for (int i = 0; i < _vBasil.size(); i++)
	{
		_vBasil[i]->render();
	}
}

void basilManager::addBasil(int x, int y)
{
	basil* temp = new basil;
	temp->init(x, y);
	_vBasil.push_back(temp);
}

void basilManager::eraseBasil(int arrNum)
{
	_vBasil[arrNum]->release();
	SAFE_DELETE(_vBasil[arrNum]);
	_vBasil.erase(_vBasil.begin() + arrNum);
}

void basilManager::clearBasil()
{
	_iterBasil _viBasil = _vBasil.begin();
	for (; _viBasil != _vBasil.end(); ++_viBasil)
	{
		(*_viBasil)->release();
		SAFE_DELETE((*_viBasil));
	}
	_vBasil.clear();
}

//BASU MANAGER
basuManager::basuManager()
{
}

basuManager::~basuManager()
{
}

HRESULT init()
{
	return S_OK;
}

void basuManager::release()
{
	clearBasu();
}

void basuManager::update(Player* player)
{
	for (int i = 0; i < _vBasu.size(); i++)
	{
		_vBasu[i]->update(player);

		if (!_vBasu[i]->getIsDead()) continue;

		eraseBasu(i);
		//여기에 죽을 때 효과 넣음
	}
}

void basuManager::render()
{
	for (int i = 0; i < _vBasu.size(); i++)
	{
		_vBasu[i]->render();
	}
}

void basuManager::addBasu(int x, int y)
{
	basu* temp = new basu;
	temp->init(x, y);
	_vBasu.push_back(temp);
}

void basuManager::eraseBasu(int arrNum)
{
	_vBasu[arrNum]->release();
	SAFE_DELETE(_vBasu[arrNum]);
	_vBasu.erase(_vBasu.begin() + arrNum);
}

void basuManager::clearBasu()
{
	_iterBasu _viBasu = _vBasu.begin();
	for (; _viBasu != _vBasu.end(); ++_viBasu)
	{
		(*_viBasu)->release();
		SAFE_DELETE((*_viBasu));
	}
	_vBasu.clear();
}

//BAT MANAGER
batManager::batManager()
{
}

batManager::~batManager()
{
}

HRESULT batManager::init()
{
	return S_OK;
}

void batManager::release()
{
	clearBat();
}

void batManager::update(Player* player)
{
	for (int i = 0; i < _vBat.size(); i++)
	{
		_vBat[i]->update(player);
		
		if (!_vBat[i]->getIsDead()) continue;

		eraseBat(i);
		//여기에 죽을 때 효과 넣음
	}
}

void batManager::render()
{
	for (int i = 0; i < _vBat.size(); i++)
	{
		_vBat[i]->render();
	}
}

void batManager::addBat(int x, int y, float angle, float power)
{
	bat* temp = new bat;
	temp->init(x, y, angle, power);
	_vBat.push_back(temp);
}

void batManager::eraseBat(int arrNum)
{
	_vBat[arrNum]->release();
	SAFE_DELETE(_vBat[arrNum]);
	_vBat.erase(_vBat.begin() + arrNum);
}

void batManager::clearBat()
{
	_iterBat _viBat = _vBat.begin();
	for (; _viBat != _vBat.end(); ++_viBat)
	{
		(*_viBat)->release();
		SAFE_DELETE((*_viBat));
	}
	_vBat.clear();
}

//BEETLE
beetleManager::beetleManager()
{

}

beetleManager::~beetleManager()
{

}

HRESULT beetleManager::init()
{
	return S_OK;
}

void beetleManager::release()
{
	clearBeetle();
}

void beetleManager::update(Player* player)
{
	for (int i = 0; i < _vBeetle.size(); i++)
	{
		_vBeetle[i]->update(player);

		if (!_vBeetle[i]->getIsDead()) continue;

		eraseBeetle(i);
		//여기에 죽을 때 효과 넣음
	}
}

void beetleManager::render()
{
	for (int i = 0; i < _vBeetle.size(); i++)
	{
		_vBeetle[i]->render();
	}
}

void beetleManager::addBeetle(int x, int y, bool isRight)
{
	beetle* temp = new beetle;
	temp->init(x, y, isRight);
	_vBeetle.push_back(temp);
}

void beetleManager::eraseBeetle(int arrNum)
{
	_vBeetle[arrNum]->release();
	SAFE_DELETE(_vBeetle[arrNum]);
	_vBeetle.erase(_vBeetle.begin() + arrNum);
}

void beetleManager::clearBeetle()
{
	_iterBeetle _viBeetle = _vBeetle.begin();
	for (; _viBeetle != _vBeetle.end(); ++_viBeetle)
	{
		(*_viBeetle)->release();
		SAFE_DELETE((*_viBeetle));
	}
	_vBeetle.clear();
}

//BEHEMOTH MANAGER
behemothManager::behemothManager()
{
}

behemothManager::~behemothManager()
{
}

HRESULT behemothManager::init()
{
	return S_OK;
}

void behemothManager::release()
{
	clearBehemoth();
}

void behemothManager::update(Player* player)
{
	for (int i = 0; i < _vBehemoth.size(); i++)
	{
		_vBehemoth[i]->update(player);

		if (!_vBehemoth[i]->getIsDead()) continue;

		eraseBehemoth(i);
		//여기에 죽을 때 효과 넣음
	}
}

void behemothManager::render()
{
	for (int i = 0; i < _vBehemoth.size(); i++)
	{
		_vBehemoth[i]->render();
	}
}

void behemothManager::addBehemoth(int x, int y)
{
	behemoth* temp = new behemoth;
	temp->init(x, y);
	_vBehemoth.push_back(temp);
}

void behemothManager::eraseBehemoth(int arrNum)
{
	_vBehemoth[arrNum]->release();
	SAFE_DELETE(_vBehemoth[arrNum]);
	_vBehemoth.erase(_vBehemoth.begin() + arrNum);
}

void behemothManager::clearBehemoth()
{
	_iterBehemoth _viBehemoth = _vBehemoth.begin();
	for (; _viBehemoth != _vBehemoth.end(); ++_viBehemoth)
	{
		(*_viBehemoth)->release();
		SAFE_DELETE((*_viBehemoth));
	}
	_vBehemoth.clear();
}


//CRITTER MANAGER
critterManager::critterManager()
{
}

critterManager::~critterManager()
{
}

HRESULT critterManager::init()
{
	return S_OK;
}

void critterManager::release()
{
	clearCritter();
}

void critterManager::update(Player* player)
{
	for (int i = 0; i < _vCritter.size(); i++)
	{
		_vCritter[i]->update(player);

		if (!_vCritter[i]->getIsDead()) continue;

		eraseCritter(i);
		//여기에 죽을 때 효과 넣음
	}
}

void critterManager::render()
{
	for (int i = 0; i < _vCritter.size(); i++)
	{
		_vCritter[i]->render();
	}
}

void critterManager::addCritter(int x, int y)
{
	critter* temp = new critter;
	temp->init(x, y);
	_vCritter.push_back(temp);
}

void critterManager::eraseCritter(int arrNum)
{
	_vCritter[arrNum]->release();
	SAFE_DELETE(_vCritter[arrNum]);
	_vCritter.erase(_vCritter.begin() + arrNum);
}

void critterManager::clearCritter()
{
	_iterCritter _viCritter = _vCritter.begin();
	for (; _viCritter != _vCritter.end(); ++_viCritter)
	{
		(*_viCritter)->release();
		SAFE_DELETE((*_viCritter));
	}
	_vCritter.clear();
}
