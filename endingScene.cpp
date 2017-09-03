#include "stdafx.h"
#include "endingScene.h"
extern float MusicMasterVol;
extern float SoundMasterVol;

endingScene::endingScene()
{
}


endingScene::~endingScene()
{
}

HRESULT endingScene::init() 
{
	//엔딩이미지 관련
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("에그랩실");
	SOUNDMANAGER->stop("보스브금");
	SOUNDMANAGER->stop("Stage1Intro");
	SOUNDMANAGER->stop("Stage2");
	SOUNDMANAGER->play("credits", MusicMasterVol);
	_endImg = IMAGEMANAGER->findImage("ending");
	_endImgY = 0;
	_endingOn = false;

	return S_OK;

}
void endingScene::release()
{

}
void endingScene::update()
{
	//엔딩이미지 관련
	//if (KEYMANAGER->isOnceDown('T'))
	//{
	//	_endingOn = true;
	//
	//}
 	_endImgY--;
	if (_endImgY < -4400)
	{
		//_endImgY = -4400;
		SCENEMANAGER->changeScene("MainMenu");
	}
}
void endingScene::render()
{
	EFFECTMANAGER->render();

	//엔딩이미지관련
	 _endImg->render(getMemDC(), 0, _endImgY);


}