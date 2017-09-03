#pragma once

#include "enemy.h"

class breakBrick : public enemy
{
private:
	image* _brickImg;
	const char* _pxlImgName;

public:
	breakBrick();
	~breakBrick();

	HRESULT init(int x, int y);
	void release();
	void update(Player* player);
	void render();

	void imgInit();

	void setPxlName(const char* imageName) { _pxlImgName = imageName; };
	const char* getPxlName() { return _pxlImgName; }
};

