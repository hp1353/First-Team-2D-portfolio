#pragma once

#include "gameNode.h"
#include "effect.h"

class effectTest
{
private:
	effect* _effectSample;

public:
	effectTest();
	~effectTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

