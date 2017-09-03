#include "stdafx.h"
#include "enemy.h"
#include "Player.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

void enemy::takeHit(int dmg)
{
	SOUNDMANAGER->play(_hurtSound, 1.f);
	_currentHP -= dmg;
	_StackedDamage += dmg;

	_DamageOutTime = TIMEMANAGER->getWorldTime()+1;
	_isHitOut = true;
	_DamageNumUpCount = 0;
}

void enemy::checkDead()
{
	if (_currentHP <= 0)
	{
		_isDead = true;
	}
}



void enemy::dealDmg(Player* player)
{
	if (player->isInvunerable()) return;

	RECT temp = RectMake(0, 0, 0, 0);

	if (IntersectRect(&temp, &_rc, &(player->getPlayer()->getRect())))
	{
		player->getPlayer()->minToCHP(_damage);

		if (_x < player->getPlayer()->getX())
		{
			player->getPlayer()->setIsRight(false);
		}
		else if (_x > player->getPlayer()->getX())
		{
			player->getPlayer()->setIsRight(true);
		}

		player->isHit(true);
	}
}

float enemy::woodMovementX(int num)
{
	float x = cosf(_angle) * _radius + BOSSCENTERX;
	x += (float)num;
	return x;
}