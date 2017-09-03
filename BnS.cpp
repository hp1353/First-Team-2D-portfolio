#include "stdafx.h"
#include "BnS.h"


BnS::BnS()
{
}


BnS::~BnS()
{
}

HRESULT BnS::init()
{
	_swordMan = IMAGEMANAGER->addImage( "bns", "image/올려베기&승천.bmp", 14800, 700, true, 0xff00ff );

	//애니메이션 테스트1
	//디폴트 애니메이션
	_ani1 = new animation;
	_ani1->init( _swordMan->getWidth(), _swordMan->getHeight(), 400, 700 );
	_ani1->setDefPlayFrame( false, true );
	_ani1->setFPS( 11 );

	//애니메이션 테스트2
	_ani2 = new animation;
	_ani2->init( _swordMan->getWidth(), _swordMan->getHeight(), 400, 700 );
	_ani2->setPlayFrame( 15, 30, false, true );
	_ani2->setFPS( 11 );

	//애니메이션 테스트3
	int arrAni[] = {2, 4, 6, 8, 10, 13, 16, 23, 28};
	_ani3 = new animation;
	_ani3->init( _swordMan->getWidth(), _swordMan->getHeight(), 400, 700 );
	_ani3->setPlayFrame( arrAni, _countof(arrAni), TRUE );
	_ani3->setFPS( 11 );

	return S_OK;
}

void BnS::release()
{
}

void BnS::update()
{
	if ( KEYMANAGER->isOnceDown( 'A' ) )
	{
		_ani1->start();
	}

	if ( KEYMANAGER->isOnceDown( 'S' ) )
	{
		_ani2->start();
	}

	if ( KEYMANAGER->isOnceDown( 'D' ) )
	{
		_ani3->start();
	}

	_ani1->frameUpdate( TIMEMANAGER->getElapsedTime() );
	_ani2->frameUpdate( TIMEMANAGER->getElapsedTime() );
	_ani3->frameUpdate( TIMEMANAGER->getElapsedTime() );
}

void BnS::render()
{
	_swordMan->aniRender( getMemDC(), 0, 100, _ani1 );
	_swordMan->aniRender( getMemDC(), 420, 100, _ani2 );
	_swordMan->aniRender( getMemDC(), 840, 100, _ani3 );
}
