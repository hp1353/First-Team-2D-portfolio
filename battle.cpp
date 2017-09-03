#include "stdafx.h"
#include "battle.h"


battle::battle()
{
}


battle::~battle()
{
}

HRESULT battle::init( const char* imageName, int x, int y )
{
	ship::init( imageName, x, y );

	//_missile = new missilePF;
	//_missile->init( "missilePF", 30, 600 );

	this->setAngle( DATABASE->getElementData( "battle" )->angle );

	return S_OK;
}

void battle::release()
{
	//_missile->release();
	//SAFE_DELETE( _missile );

	ship::release();
}

void battle::update()
{
	missileMove();
	ship::update();
}

void battle::render()
{
	missileDraw();
	ship::render();
}

void battle::missileDraw()
{
	//_missile->render();
}

void battle::missileMove()
{
	////_missile->update();
}

void battle::missileFire()
{
	float x = _x + cosf( _angle ) * 50;
	float y = _y + -sinf( _angle ) * 50;

	//_missile->fire( x, y, _angle, 500.f );
}

void battle::keyControl()
{
	ship::keyControl();

	//미사일만 따로
	if ( KEYMANAGER->isStayDown( 'B' ) )
	{
		missileFire();
	}
}
