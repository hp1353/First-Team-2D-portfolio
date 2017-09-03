#pragma once

#include "gameNode.h"
#include "action.h"

static image* actionImage = NULL;

class actionTest : public gameNode
{
private:
	image* _actionTest;

public:
	actionTest();
	~actionTest();

	HRESULT init();
	void release();
	void update();
	void render();

	static void callback();

};

