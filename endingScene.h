#pragma once
#include "gameNode.h"


class endingScene : public gameNode
{
private:

	//�����̹���
	image* _endImg;
	int _endImgY;
	int _endingOn;

public:
	endingScene();
	~endingScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

