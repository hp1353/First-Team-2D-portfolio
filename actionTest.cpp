#include "stdafx.h"
#include "actionTest.h"


actionTest::actionTest()
{
}


actionTest::~actionTest()
{
}

HRESULT actionTest::init()
{
	_actionTest = IMAGEMANAGER->addImage( "bullet2", "image/bullet.bmp", 21, 21, true, RGB( 255, 0, 255 ) );
	_actionTest->setX( CENTERX );
	_actionTest->setY( CENTERY );

	actionImage = _actionTest;


	return S_OK;
}

void actionTest::release()
{
	
}

void actionTest::update()
{
	if ( KEYMANAGER->isOnceDown( VK_LBUTTON ) )
	{
		ACTIONMANAGER->moveTo( actionImage, RND->getFromIntTo( 50, WINSIZEX - 50 ),
			RND->getFromIntTo( 60, WINSIZEY - 50 ),
			RND->getFromFloatTo( 5.0f, 10.f ), callback );
	}

	ACTIONMANAGER->update();
}

void actionTest::render()
{
	_actionTest->render( getMemDC() );
}

void actionTest::callback()
{
	ACTIONMANAGER->moveTo( actionImage,
		RND->getFromIntTo( 50, WINSIZEX - 50 ),
		RND->getFromIntTo( 60, WINSIZEY - 50 ),
		RND->getFromFloatTo( 5.0f, 10.f ), callback );
}

