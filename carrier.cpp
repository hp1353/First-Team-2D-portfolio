#include "stdafx.h"
#include "carrier.h"


carrier::carrier()
{
}


carrier::~carrier()
{
}

HRESULT carrier::init( const char * imageName, int x, int y )
{
	ship::init( imageName, x, y );

	return S_OK;
}

void carrier::release()
{
	ship::release();
}

void carrier::update()
{
	ship::update();
}

void carrier::render()
{
	ship::render();
}

void carrier::keyControl()
{
	if ( KEYMANAGER->isStayDown( 'A' ) )
	{
		_angle += 0.06f;
		if ( _angle > PI2 ) _angle -= PI2;
	}
	if ( KEYMANAGER->isStayDown( 'D' ) )
	{
		_angle -= 0.06f;
		if ( _angle < 0 ) _angle += PI2;
	}

	if ( KEYMANAGER->isStayDown( 'W' ) )
	{
		_speed += 0.05f;
	}
	if ( KEYMANAGER->isStayDown( 'S' ) )
	{
		_speed -= 0.05f;
	}
}

void carrier::move()
{
	int frame;
	float angle;

	angle = _angle;

	frame = int( angle / PI16 );
	_image->setFrameX( frame );

	_x += cosf( _angle ) * _speed;
	_y += -sinf( _angle ) * _speed;

	_rc = RectMakeCenter( _x, _y,
		_image->getFrameWidth(),
		_image->getFrameHeight() );
}
