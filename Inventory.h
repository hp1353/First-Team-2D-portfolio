#pragma once
#include"gameNode.h"
#include"cameraAngle.h"

class Inventory : public gameNode 
{
private:
	
	
public:
	Inventory();
	~Inventory();
	rcCamAngle _cam;
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update(float x, float y);
	virtual void render();

	//void GetCam(rcCamAngle _rcCam) { _cam = _rcCam; }
};

