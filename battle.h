#pragma once

#include "ship.h"

class battle : public ship
{
private:


public:
	battle();
	~battle();

	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update();
	void render();

	virtual void missileDraw();
	virtual void missileMove();
	virtual void missileFire();

	virtual void keyControl();
};

