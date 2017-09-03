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
	//�����̹��� ����
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("���׷���");
	SOUNDMANAGER->stop("�������");
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
	//�����̹��� ����
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

	//�����̹�������
	 _endImg->render(getMemDC(), 0, _endImgY);


}