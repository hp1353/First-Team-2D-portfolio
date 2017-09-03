#pragma once

#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	   //리소스로부터 생성
		LOAD_FILE,		   //파일로부터 생성
		LOAD_EMPTY,		   //걍 생성
		LOAD_END		   
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;

		int currentFrameX;	//현재 프레임 X
		int currentFrameY;	//현재 프레임 Y
		int maxFrameX;		//최대 프레임 X
		int maxFrameY;		//최대 프레임 Y
		int frameWidth;		//프레임당 가로 크기
		int frameHeight;	//프레임당 세로 크기

		BYTE loadType;
		RECT boundingBox;	//이미지에 바로 렉트 씌워줌

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	//생성과 동시에 멤버이니셜 라이즈로 초기화 해주는 변수들
	LPIMAGE_INFO	_imageInfo;		 //이미지 정보
	CHAR*			_fileName;		 //이미지 경로 이름
									 
	BOOL			_trans;			 //투명배경이니?
	COLORREF		_transColor;	 //투명 컬러 색상

	BLENDFUNCTION	_blendFunc;		//알파 블렌드를 위한 정보
	LPIMAGE_INFO	_blendImage;	//알파 블렌드를 사용하기 위한 이미지 정보

public:
	image();
	~image();

	//빈 비트맵 이미지 만든다
	HRESULT init(int width, int height);

	//리로스로부터 읽어온다.
	HRESULT init(const DWORD resID, int width, int height,
		BOOL trans, COLORREF transColor);

	//이미지 파일로 읽어온다.
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans, COLORREF transColor);

	//이미지 파일 + 프레임 파일 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,	BOOL trans, COLORREF transColor);

	//alphaInit
	void alphaInit();

	//삭제
	void release();

	//투명값 활성 && 지정
	void setTransColor(BOOL trans, COLORREF transColor);

	//Render
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	
	//AlphaBlend
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//frameRender
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//알파 프레임렌더
	//void framealphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//loopRender
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	//aniRender
	void aniRender( HDC hdc, int destX, int destY, animation* ani );

	//DC 얻어오기
	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	//좌표 X
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	//좌표 Y
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	//좌표 센터
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//중점 X
	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//중점 Y
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//가로 해상도
	inline int getWidth() { return _imageInfo->width; }

	//세로 해상도
	inline int getHeight() { return _imageInfo->height; }

	//바운딩 박스
	inline RECT boundingBox()
	{
		RECT rc = { int(_imageInfo->x), int(_imageInfo->y), 
			int(_imageInfo->x) + _imageInfo->frameWidth,
			int(_imageInfo->y) + _imageInfo->frameHeight };
		return rc;
	}

	//프레임
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};



