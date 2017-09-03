#pragma once
#include "gameNode.h"
#include "cameraAngle.h"
#include "Player.h"


extern float MusicMasterVol;
extern float SoundMasterVol;

struct Pixel
{
	bool _PRight;
	bool _PLeft;
	bool _PTop;
	bool _PBottom;
};


class Item : public gameNode
{
protected:
	image* _ItemImage;

	ImageString _StringPackage;

	
	float _spawnTime;
	float _DeleteTime;
	float _angle;
	float _speed;
	float _gravity;

	int _MaxHpItem;

	int _TwinkleCount;
	int _TwinkleInteval;

	int _count;
	int _index;
	int _TextNullCount;
	int _Nully;
	float _Alpha;

	int _ItemPoint;
	int _MaxHpindex;
	const char* _FileName;
	const char* _PixelName;

	RECT _ItemBox;
	RECT _temp;
	RECT _TextNull;
	int _Sort;

	Player* _playerInfo;

	rcCamAngle _cam;

	bool _isDropItem;
	bool _isText;
	bool _isTwinkle;

	bool _isPM;


	vector<Item> _vItem;
	vector<Item>::iterator _viItem;
public:
	Item();
	~Item();

	//부모에서 구현했으므로 자식에서는 이 함수를 다시 쓸 필요 없음.
	virtual HRESULT init(ImageString FileName, int x, int y, int Item);
	virtual HRESULT init(ImageString FileName, int x, int y, int Item, bool DropItem);
	virtual void FrameUpdate();
	virtual void render();

	virtual void release();

	
	virtual RECT GetRect() { return _ItemBox;  }
	virtual int GetSortItem() { return _Sort; }
	virtual int GetItemPoint() { return _ItemPoint; }
	virtual float DeleteItemTime() { return _DeleteTime; }
	virtual bool isDropItem() { return _isDropItem; }
	virtual void TwinkleOn() { _isTwinkle = true;  }
	virtual ImageString GetImageString() { return _StringPackage;  }
	virtual Pixel PixelDetect(const char* PixelName);
	virtual void LinkToPlayer(Player* _player) { _playerInfo = _player; }

	//자식에게 줄 가상 함수
	virtual void ItemUse(int i) {};
	virtual void ItemUse() {};
	virtual void PixelCollision(RECT box, Pixel pixelCollision) {};
	virtual void Move(const char* _PixelMap) {};

	void SetIndex(int i) { _MaxHpindex = i; }




};

