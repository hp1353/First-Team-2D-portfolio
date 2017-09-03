#include "stdafx.h"
#include "EnemyFullManager.h"
#include "ItemManager.h"



EnemyFullManager::EnemyFullManager()
{
}


EnemyFullManager::~EnemyFullManager()
{
}

HRESULT EnemyFullManager::init(const char* imageName)
{
	_imgName = imageName;

	return S_OK;
}

void EnemyFullManager::release()
{
	clearEnemy();
	clearBrick();
}

void EnemyFullManager::update(Player* player)
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->checkType() == E_BOSS || _vEnemy[i]->checkType ()== E_BALL || _vEnemy[i]->checkType() == E_BALL || _vEnemy[i]->checkType() == E_WOOD) continue;
		
		_vEnemy[i]->update(player);

		if (!_vEnemy[i]->getIsDead()) continue;

		SOUNDMANAGER->play(_vEnemy[i]->getDeathrattle(), 1.1f);
		EFFECTMANAGER->play("먼지", _vEnemy[i]->getRect().left, _vEnemy[i]->getRect().top);
		EFFECTMANAGER->play("먼지", _vEnemy[i]->getRect().right, _vEnemy[i]->getRect().top);
		EFFECTMANAGER->play("먼지", _vEnemy[i]->getRect().left, _vEnemy[i]->getRect().bottom);
		EFFECTMANAGER->play("먼지", _vEnemy[i]->getRect().right, _vEnemy[i]->getRect().bottom);
		EFFECTMANAGER->play("먼지", _vEnemy[i]->getX(), _vEnemy[i]->getY());


		if (_vEnemy[i]->checkType() != E_BRICK || _vEnemy[i]->checkType() != E_BOSS || _vEnemy[i]->checkType() != E_BALL || _vEnemy[i]->checkType() != E_WOOD)
		{
			_ItemManager->MonsterDropItem(_vEnemy[i]->getRect().left + ((_vEnemy[i]->getRect().right - _vEnemy[i]->getRect().left) / 2) - 10,
				_vEnemy[i]->getRect().top + ((_vEnemy[i]->getRect().bottom - _vEnemy[i]->getRect().top) / 2) - 10, _vEnemy[i]->checkType());


			eraseEnemy(i);
		}
	}
}

void EnemyFullManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		if (_vEnemy[i]->checkType() == E_BOSS || _vEnemy[i]->checkType() == E_BALL || _vEnemy[i]->checkType() == E_WOOD) continue;
		_vEnemy[i]->render();
		DamageRender(i);
	}
	
}

void EnemyFullManager::addEnemy(int x, int y, int EnemyType, bool Right, float power)
{
	switch (EnemyType)
	{
	case E_CRITTER:
		_critter = new critter;
		_critter->init(x, y, _imgName, _vBrick);
		_vEnemy.push_back(_critter);
		break;
	case E_BAT:
		_bat = new bat;
		_bat->init(x, y, RND->getFromFloatTo(0, 2 * PI), power);
		_vEnemy.push_back(_bat);
		break;
	case E_BASIL:
		_basil = new basil;
		_basil->init(x, y, _imgName);
		_vEnemy.push_back(_basil);
		break;
	case E_BEETLE:
		_beetle = new beetle;
		_beetle->init(x, y, Right, _imgName);
		_vEnemy.push_back(_beetle);
		break;
	case E_BASU:
		_basu = new basu;
		_basu->init(x, y, _imgName);
		_vEnemy.push_back(_basu);
		break;
	case E_BEHEMOTH:
		_behemoth = new behemoth;
		_behemoth->init(x, y, _imgName);
		_vEnemy.push_back(_behemoth);
		break;
	case E_ANGEL:
		_angel = new angel;
		_angel->init(x, y);
		_vEnemy.push_back(_angel);
		break;
	case E_ZOMBIE:
		_dragon = new ZombieDragon;
		_dragon->init(x, y, _imgName);
		_vEnemy.push_back(_dragon);
		break;
		//개구리 추가
		break;
	case E_BRICK:
		_Brick = new breakBrick;
		_Brick->init(x, y);
		_vBrick.push_back(_Brick);
		_vEnemy.push_back(_Brick);
		//에네미 벡터에 넣든 브릭 함수에 넣든 자유
		break;
	}
}

void EnemyFullManager::addBoss(enemy* boss)
{
	_vEnemy.push_back(boss);
}

void EnemyFullManager::addBall(BossBody* boss)
{
	for (int i = 0; i < boss->getVBall().size(); i++)
	{
		_vEnemy.push_back(boss->getVBall()[i]);
	}
}

void EnemyFullManager::addWood(BossBody* boss)
{
	for (int i = 0; i < boss->getVWood().size(); i++)
	{
		_vBrick.push_back(boss->getVWood()[i]);
	}
}

void EnemyFullManager::eraseEnemy(int arrNum)
{
	if (_vEnemy[arrNum]->checkType() == E_BOSS || _vEnemy[arrNum]->checkType() == E_BALL || _vEnemy[arrNum]->checkType() == E_BALL || _vEnemy[arrNum]->checkType() == E_WOOD) return;
	_vEnemy[arrNum]->release();
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

void EnemyFullManager::clearEnemy()
{
	
	_iterEnemy _viEnemy = _vEnemy.begin();
	for (; _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		
		(*_viEnemy)->release();
		SAFE_DELETE((*_viEnemy));
	}
	_vEnemy.clear();
}

void EnemyFullManager::eraseBrick(int arrNum)
{

	_vBrick[arrNum]->release();
	SAFE_DELETE(_vBrick[arrNum]);
	_vBrick.erase(_vBrick.begin() + arrNum);
}

void EnemyFullManager::clearBrick()
{
	_vBrick.clear();
}

void EnemyFullManager::DamageRender(int i)
{
	if (!_vEnemy[i]->GetOutDamage()) return;


			if (_vEnemy[i]->StackedDamage() > 9)
			{
				IMAGEMANAGER->findImage("DamageNum")->frameRender(getMemDC(), _vEnemy[i]->getX()-16, _vEnemy[i]->getRect().top - _vEnemy[i]->UpDamageNum(),11,0);
				IMAGEMANAGER->findImage("DamageNum")->setFrameX(_vEnemy[i]->StackedDamage() / 10);
				IMAGEMANAGER->findImage("DamageNum")->frameRender(getMemDC(), _vEnemy[i]->getX(), _vEnemy[i]->getRect().top- _vEnemy[i]->UpDamageNum());
				IMAGEMANAGER->findImage("DamageNum")->setFrameX(_vEnemy[i]->StackedDamage() % 10);
				IMAGEMANAGER->findImage("DamageNum")->frameRender(getMemDC(), _vEnemy[i]->getX()+16, _vEnemy[i]->getRect().top - _vEnemy[i]->UpDamageNum());
			}
			if (_vEnemy[i]->StackedDamage() <= 9 && _vEnemy[i]->StackedDamage() > 0)
			{
				IMAGEMANAGER->findImage("DamageNum")->frameRender(getMemDC(), _vEnemy[i]->getX() - 16, _vEnemy[i]->getRect().top - _vEnemy[i]->UpDamageNum(), 11, 0);
				IMAGEMANAGER->findImage("DamageNum")->setFrameX(_vEnemy[i]->StackedDamage() % 10);
				IMAGEMANAGER->findImage("DamageNum")->frameRender(getMemDC(), _vEnemy[i]->getX() , _vEnemy[i]->getRect().top- _vEnemy[i]->UpDamageNum());
			}
		
		if(_vEnemy[i]->DamageTimeReturn()  + 0.5f < TIMEMANAGER->getWorldTime())
		{
			_vEnemy[i]->UnOutDamagedNum();
		}
}

int EnemyFullManager::CheckAngelNum()
{
     _AngelNum = 0;
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->checkType() == E_ANGEL) _AngelNum++;
	}
	return _AngelNum;
}


void EnemyFullManager::AllKillAngel()
{
	_AngelNum = 0;
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->checkType() == E_ANGEL)
			_vEnemy[i]->takeHit(20);
	}
}