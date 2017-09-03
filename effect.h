#pragma once

#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;						   //이펙트 좌표위치 레프트
	int _y;						   //이펙트 좌표위치 탑
								   
	image* _effectImage;		   //이펙트 이미지
	animation* _effectAnimation;   //이펙트 애니메이션
	BOOL _isRunning;			   //이펙트 활성화 여부
	float _elapsedTime;			   //이펙트 경과시간

public:
	effect();
	~effect();

	virtual HRESULT init( image* effectImage, int frameW, int frameH, int fps, float elapsedTime );
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void startEffect( int x, int y );
	virtual void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

