#pragma once

#include "gameNode.h"
#include "animation.h"

class BnS : public gameNode
{
	image* _swordMan;

	//애니메이션 테스트 할 검사 종류
	animation* _ani1;
	animation* _ani2;
	animation* _ani3;

public:
	BnS();
	~BnS();

	HRESULT init();
	void release();
	void update();
	void render();
};

