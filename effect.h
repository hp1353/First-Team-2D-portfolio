#pragma once

#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;						   //����Ʈ ��ǥ��ġ ����Ʈ
	int _y;						   //����Ʈ ��ǥ��ġ ž
								   
	image* _effectImage;		   //����Ʈ �̹���
	animation* _effectAnimation;   //����Ʈ �ִϸ��̼�
	BOOL _isRunning;			   //����Ʈ Ȱ��ȭ ����
	float _elapsedTime;			   //����Ʈ ����ð�

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

