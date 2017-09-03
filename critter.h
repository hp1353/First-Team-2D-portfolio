#pragma once

#include "enemy.h"
#include <vector>

enum CRITTERSTATE
{
	REST,
	ALERT,
	GROUND,
	slimeJUMP
};

class critter : public enemy
{
private:
	image* _critterImg;

	const char* _imgName;

	CRITTERSTATE _state;
	bool _isAlert;
	bool _isAggro;
	bool _isRight;

	float _power;
	float _gravity;
	int _jumpCounter;

	vector<enemy*> _arrBox;

public:
	critter();
	~critter();

	HRESULT init(int x, int y, const char* imageName, vector<enemy*> arrBox);
	void release();
	void update(Player* player);
	void render();

	void checkAlert();
	void jump();
	void airUpdate();

	void bottomPxl();
	void leftPxl();
	void rightPxl();
	void topPxl();

	void CheckRectHit();

	void imgInit();
	void frameRender();
};

