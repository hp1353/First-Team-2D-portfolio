#include "stdafx.h"
#include "cameraAngle.h"


cameraAngle::cameraAngle()
{
}


cameraAngle::~cameraAngle()
{
}

HRESULT cameraAngle::init(PlayerInfo* _Player, Parent_Weapone* Weapone, vector<Parent_Weapone*> vWeapone)
{
	_player = _Player;
	setCamPos();
	//�ȵǸ� ���ӳ�� ������
	_cam.rc = RectMake(_cam.x, _cam.y, WINSIZEX, WINSIZEY);
	_cam.inertia = 0;
	//_cam.isRight = _player.isRight;

	//_cam.sceneRc = IMAGEMANAGER->findImage("background1")->boundingBox();
	//else if (SCENEMANAGER->CurrentScene("eggHatchery")) _cam.sceneRc = IMAGEMANAGER->findImage("BackGround2")->boundingBox();

	_isVibe = false;
	_camVibeCount = 0;
	_cam.xAngle = PI / 2;
	_cam.yAngle = 0.f;
	//_cam.movX = _cam.x;
	//_cam.movY = _cam.y;

	//�Ʒ��� ui �κ�
	ExpNumber = IMAGEMANAGER->addFrameImage("ExpNumber", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	HpNumber = IMAGEMANAGER->addFrameImage("HpNumber", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	HpNumber10 = IMAGEMANAGER->addFrameImage("HpNumber10", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	WeaponeIcon = IMAGEMANAGER->addFrameImage("WeaponeIcon", "image/UI/WeaponeIcon.bmp", 224, 32, 7, 1, true, RGB(255, 0, 255));
	WeaponeIconChange = IMAGEMANAGER->addFrameImage("WeaponeIconChange", "image/UI/WeaponeIcon.bmp", 224, 32, 7, 1, true, RGB(255, 0, 255));

	WeaponeBullet = IMAGEMANAGER->addFrameImage("WeaponeBullet", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	WeaponeBullet10 = IMAGEMANAGER->addFrameImage("WeaponeBullet10", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	WeaponeBullet100 = IMAGEMANAGER->addFrameImage("WeaponeBullet100", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));

	WeaponeCurBullet = IMAGEMANAGER->addFrameImage("WeaponeCurBullet", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	WeaponeCurBullet10 = IMAGEMANAGER->addFrameImage("WeaponeCurBullet10", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));
	WeaponeCurBullet100 = IMAGEMANAGER->addFrameImage("WeaponeCurBullet100", "image/UI/Number.bmp", 160, 17, 10, 1, true, RGB(255, 242, 0));


	drawmaxbullet = true;
	drawcurbullet10 = false;
	drawcurbullet100 = false;
	drawmaxbullet = true;
	drawmaxbullet10 = false;
	drawmaxbullet100 = false;

	_player = _Player;
	vWeapone = _vWeapone;
	_Weapone = *Weapone;

	ihavemachine = false;
	ihaverocket = false;

	whitehp = (85 * _player->_CurHP / _player->_MaxHP);
	return S_OK;
}

void cameraAngle::release()
{


}

void cameraAngle::update()
{
	//	(1) _player._isPixelL	���� �� �ε��� ����
	//		_player._isPixelR	������ �� �ε��� ���� �� ��!
	if (SCENEMANAGER->CurrentScene("TestScene"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("background1")->boundingBox();
	}
	else if (SCENEMANAGER->CurrentScene("eggHatchery"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("background2")->boundingBox();
	}
	else if (SCENEMANAGER->CurrentScene("stage0"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("background0")->boundingBox();
	}
	else if (SCENEMANAGER->CurrentScene("eggLab"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("backgroundEggLab")->boundingBox();
	}
	else if (SCENEMANAGER->CurrentScene("eggHatchery2"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("background3")->boundingBox();
	}
	else if (SCENEMANAGER->CurrentScene("boss"))
	{
		_cam.sceneRc = IMAGEMANAGER->findImage("stage_finalFront")->boundingBox();
	}

	if (KEYMANAGER->isOnceDown('W'))
	{
		camVibeSwitch();
	}

	switch (_player->_motion)
	{
	case WALK_UP: case WALK:
		if (!_player->_isPixelR && !_player->_isPixelL)
		{
			if (_player->_isRight)	//���������� ���� ��
			{
				if (_player->x - (5 * WINSIZEX / 12) + 4 < _cam.movX) //�������� ���� �� ���󰡴� ���
				{
					_cam.movX -= 1.f;
				}
				else if (_player->x - (5 * WINSIZEX / 12) - 4 > _cam.movX) //�������� Ŭ �� ���󰡴� ���
				{
					if (_cam.inertia <= _player->_Inertia + 1.f)
					{
						_cam.inertia += 0.25f;
						if (_cam.inertia > _player->_Inertia + 1.f) _cam.inertia = _player->_Inertia;
					}
					if (_player->_motion == JUMP_DOWN) _cam.movX += _cam.inertia + 1.f;
					//else _cam.movX += _cam.inertia + 0.8f;
					else _cam.movX += _cam.inertia;
				}
				else if (_player->x - (5 * WINSIZEX / 12) - 4 <= _cam.movX && _cam.movX <= _player->x - (5 * WINSIZEX / 12) + 4) //�����ȿ� ���� �� �����ϴ� ���
				{
					_cam.movX = _player->x - (5 * WINSIZEX / 12);
					_cam.inertia = 0.f;
				}
			}
			else					//�������� ���� ��
			{
				if (_player->x - (7 * WINSIZEX / 12) - 4 > _cam.movX)
				{
					_cam.movX += 1.f;
				}
				else if (_player->x - (7 * WINSIZEX / 12) + 4 < _cam.movX)
				{
					if (_cam.inertia >= _player->_Inertia - 1.f)
					{
						_cam.inertia -= 0.25f;
						if (_cam.inertia < _player->_Inertia - 1.f) _cam.inertia = _player->_Inertia;
					}
					if (_player->_motion == JUMP_DOWN) _cam.movX += (_cam.inertia - 1.f);
					else _cam.movX += (_cam.inertia - 0.8f);
				}
				else if (_player->x - (7 * WINSIZEX / 12) - 4 <= _cam.movX && _cam.movX <= _player->x - (7 * WINSIZEX / 12) + 4)
				{
					_cam.movX = _player->x - (7 * WINSIZEX / 12);
					_cam.inertia = 0.f;
				}
				// if (_player.x - ((7 * WINSIZEX / 12)) - 4 < _cam.x && _cam.x <= _player.x - ((7 * WINSIZEX / 12)) + 4)
				//{
				//	_cam.x = _player.x - ((7 * WINSIZEX / 12));
				//	_cam.inertia = 0.f;
				//}
			}
			break;
		}
	case JUMP: case JUMP_DOWN:
		if (_player->_isRight)	//���������� ���� ��
		{
			if (_cam.movX < _player->x - WINSIZEX / 3.5 - 4)
			{
				_cam.movX += 3.f;	//������ ī�޶�ޱ��� ���������� �Ѿƿ�
			}
			else if (_cam.movX > _player->x - WINSIZEX / 3.5 + 4)
			{
				_cam.movX -= 3.f;
			}
		}
		else					//�������� ���� ��
		{
			if (_player->x - ((WINSIZEX / 3 * 2) + 20) + 4 < _cam.movX)
			{
				_cam.movX -= 3.f;	//������ ī�޶�ޱ��� �������� �Ѿƿ�
			}
			else if (_player->x - ((WINSIZEX / 3 * 2) + 20) - 4 > _cam.movX)
			{
				_cam.movX += 3.f;
			}
		}
		break;
	case DIE:
		if (_player->_isRight)	//���������� ���� ��
		{
			if (_cam.movX < _player->x - WINSIZEX / 3.5 - 4)
			{
				/*if (_cam.inertia <= _player._Inertia + 1.f)
				{
				_cam.inertia += 0.3f;
				if (_cam.inertia > _player._Inertia + 1.f) _cam.inertia = _player._Inertia;
				}*/
				_cam.movX += 3.f;	//������ ī�޶�ޱ��� ���������� �Ѿƿ�

				if (_cam.movX > _player->x - (WINSIZEX / 3.5 * 2) + 4)
				{
					_cam.movX -= 1.5f;	//ī�޶�ޱ� ���� ��ȯ�� ���󰡴� �ӵ� ����
				}
			}
			else if (_cam.movX > _player->x - WINSIZEX / 3.5 + 4)
			{
				_cam.movX -= 3.f;
			}
			else if (_player->x - WINSIZEX / 3.5 - 4 <= _cam.movX && _cam.movX <= _player->x - WINSIZEX / 3.5 + 4)
			{
				_cam.movX = _player->x - WINSIZEX / 3.5;
				_cam.inertia = 0.f;
			}
		}
		else					//�������� ���� ��
		{
			if (_player->x - ((WINSIZEX / 3 * 2) + 20) + 4 < _cam.movX)
			{
				/*if (_cam.inertia >= _player._Inertia - 1.f) {
				_cam.inertia -= 0.3f;
				if (_cam.inertia < _player._Inertia - 1.f) _cam.inertia = _player._Inertia - 1.f;
				}*/
				_cam.movX -= 3.f;	//������ ī�޶�ޱ��� �������� �Ѿƿ�

				if (_cam.movX > _player->x - ((WINSIZEX / 3 * 2) + 20) + 4)
				{
					_cam.movX += 1.5f;	//ī�޶�ޱ� ���� ��ȯ�� ���󰡴� �ӵ� ����
				}
			}
			else if (_player->x - ((WINSIZEX / 3 * 2) + 20) - 4 > _cam.movX)
			{
				_cam.movX += 3.f;
			}
			else if (_player->x - ((WINSIZEX / 3 * 2) + 20) - 4 <= _cam.movX && _cam.movX <= _player->x - ((WINSIZEX / 3 * 2) + 20) + 4)
			{
				_cam.movX = _player->x - ((WINSIZEX / 3 * 2) + 20);
				_cam.inertia = 0.f;
			}
		}

		if (_cam.movY < _player->y - WINSIZEY / 2 - 5)
		{
			_cam.movY += (1.5f + _player->_JumpPower + _player->_gravity);	//������ �Ʒ��� ƨ�� �� ��
		}
		else if (_cam.movY > _player->y - WINSIZEY / 2 + 5)
		{
			if (_player->_isRight) _cam.movY -= (1.f + cosf(PI / 4) * _player->_Inertia);
			else _cam.movY -= (1.5f + cosf(PI / 4 * 3) * _player->_Inertia);	//�Ʒ��� ���� ƨ�� �� ��
		}
		else if (_cam.movY >= _player->y - WINSIZEY / 2 - 5 && _cam.movY <= _player->y - WINSIZEY / 2 + 5)
		{
			_cam.movY = _player->y - WINSIZEY / 2;
		}
		break;
	default:
		if (_player->_isRight)	//���������� ���� ��
		{
			if (_cam.movX < _player->x - WINSIZEX / 3.5 - 4)
			{
				/*if (_cam.inertia <= _player._Inertia + 1.f)
				{
				_cam.inertia += 0.3f;
				if (_cam.inertia > _player._Inertia + 1.f) _cam.inertia = _player._Inertia;
				}*/
				_cam.movX += 3.f;	//������ ī�޶�ޱ��� ���������� �Ѿƿ�

				if (_cam.movX > _player->x - (WINSIZEX / 3.5 * 2) + 4)
				{
					_cam.movX -= 1.5f;	//ī�޶�ޱ� ���� ��ȯ�� ���󰡴� �ӵ� ����
				}
			}
			else if (_cam.movX > _player->x - WINSIZEX / 3.5 + 4)
			{
				_cam.movX -= 3.f;
			}
			else if (_player->x - WINSIZEX / 3.5 - 4 <= _cam.movX && _cam.movX <= _player->x - WINSIZEX / 3.5 + 4)
			{
				_cam.movX = _player->x - WINSIZEX / 3.5;
				_cam.inertia = 0.f;
			}
		}
		else					//�������� ���� ��
		{
			if (_player->x - ((WINSIZEX / 3 * 2) + 20) + 4 < _cam.movX)
			{
				/*if (_cam.inertia >= _player._Inertia - 1.f) {
				_cam.inertia -= 0.3f;
				if (_cam.inertia < _player._Inertia - 1.f) _cam.inertia = _player._Inertia - 1.f;
				}*/
				_cam.movX -= 3.f;	//������ ī�޶�ޱ��� �������� �Ѿƿ�

				if (_cam.movX > _player->x - ((WINSIZEX / 3 * 2) + 20) + 4)
				{
					_cam.movX += 1.5f;	//ī�޶�ޱ� ���� ��ȯ�� ���󰡴� �ӵ� ����
				}
			}
			else if (_player->x - ((WINSIZEX / 3 * 2) + 20) - 4 > _cam.movX)
			{
				_cam.movX += 3.f;
			}
			else if (_player->x - ((WINSIZEX / 3 * 2) + 20) - 4 <= _cam.movX && _cam.movX <= _player->x - ((WINSIZEX / 3 * 2) + 20) + 4)
			{
				_cam.movX = _player->x - ((WINSIZEX / 3 * 2) + 20);
				_cam.inertia = 0.f;
			}
		}
		break;
	}
	//���� �ö󰡴� �� 0.12
	//�׷���Ƽ 0.2

	//������ ���� ��
	if (_player->_isUp)
	{
		//_cam.y = _player.y - (WINSIZEY / 4) * 3;
		if ((_player->y - (WINSIZEY / 4) * 3) - 5 < _cam.movY &&
			_cam.movY < (_player->y - (WINSIZEY / 4) * 3) + 5)
		{
			_cam.movY = _player->y - (WINSIZEY / 4) * 3;
		}
		else if (_cam.movY >= (_player->y - (WINSIZEY / 4) * 3) + 5)
		{
			_cam.movY -= 1.5f;	//���� �� ��
		}
		else if (_cam.movY <= (_player->y - (WINSIZEY / 4) * 3) - 5)
		{
			_cam.movY += 4.f;	//ĳ���� ���� ���� �� ��
								//_cam.movY += _player->y;
		}
	}
	//�Ʒ����� ���� ��
	else if (_player->_isDown)
	{
		//_cam.y = _player.y - WINSIZEY / 4;
		if (_cam.movY < _player->y - WINSIZEY / 4 + 5 &&
			_cam.movY > _player->y - (WINSIZEY / 4) - 5)
		{
			_cam.movY = _player->y - WINSIZEY / 4;
		}
		else if (_cam.movY <= _player->y - (WINSIZEY / 4) - 5)
		{
			_cam.movY += (1.5f + _player->_JumpPower + _player->_gravity);	//�Ʒ��� �� ��
		}
		else if (_cam.movY >= _player->y - (WINSIZEY / 4) + 5)
		{
			_cam.movY -= 4.f;
			//_cam.movY -= _player->y;
		}
	}
	else
	{
		if (_cam.movY < _player->y - WINSIZEY / 2 - 5)
		{
			_cam.movY += (1.5f + _player->_JumpPower + _player->_gravity);	//������ �Ʒ��� ƨ�� �� ��
		}
		else if (_cam.movY > _player->y - WINSIZEY / 2 + 5)
		{
			if (_player->_isRight) _cam.movY -= (1.f + cosf(PI / 4) * _player->_Inertia);
			else _cam.movY -= (1.5f + cosf(PI / 4 * 3) * _player->_Inertia);	//�Ʒ��� ���� ƨ�� �� ��
		}
		else if (_cam.movY >= _player->y - WINSIZEY / 2 - 5 && _cam.movY <= _player->y - WINSIZEY / 2 + 5)
		{
			_cam.movY = _player->y - WINSIZEY / 2;
		}
	}
	//���� �� ����
	if (_cam.movY < _cam.sceneRc.top)
	{
		_cam.movY = _cam.sceneRc.top;
	}
	else if (_cam.movY > _cam.sceneRc.bottom - WINSIZEY)
	{
		_cam.movY = _cam.sceneRc.bottom - WINSIZEY;
	}
	//�¿� �� ����
	if (_cam.movX < _cam.sceneRc.left)
	{
		_cam.movX = _cam.sceneRc.left;
	}
	else if (_cam.movX > _cam.sceneRc.right - WINSIZEX)
	{
		_cam.movX = _cam.sceneRc.right - WINSIZEX;
	}

	crushevent();
	numbercontrol();

	cameraVibration();
	_cam.x = cosf(_cam.xAngle) * 4 + _cam.movX;
	_cam.y = -sinf(_cam.yAngle) * 5 + _cam.movY;
}

void cameraAngle::render()
{
	//��׶��� �������

	//Rectangle(getMemDC(), _player->_rc.left, _player->_rc.top, _player->_rc.right, _player->_rc.bottom);	//�׽�Ʈ��Ʈ �������

	//ī�޶�ޱ� ��� ��������
	//if (_player.x < WINSIZEX / 2)
	//	this->getBackBuffer()->render(getMemDC());
	//if (_player.x >= WINSIZEX / 2 && _player.x < 3378 - WINSIZEX / 2)
	//	this->getBackBuffer()->render(getMemDC(), 0, 0, _player.x - WINSIZEX / 2, 0, WINSIZEX, WINSIZEY);


	//if (_player.x >= 3378 - WINSIZEX / 2)
	//	this->getBackBuffer()->render(getMemDC(), 0, 0, 3378 - WINSIZEX, 0, WINSIZEX, WINSIZEY);

	//���Ŵ��� ���,cpp�� bool �Լ� �߰�������
	if (!iscrush)//�浹 �ƴҶ� ���������ʰ� �״�ΰ�� ���
	{
		IMAGEMANAGER->findImage("UIExpEmpty")->render(getMemDC(), 85 + _cam.x, 70 + _cam.y);
		IMAGEMANAGER->findImage("UIHpEmpty")->render(getMemDC(), 85 + _cam.x, 90 + _cam.y);
		IMAGEMANAGER->findImage("WeaponLv")->render(getMemDC(), 35 + _cam.x, 70 + _cam.y);
		IMAGEMANAGER->findImage("ExpNumber")->frameRender(getMemDC(), 70 + _cam.x, 70 + _cam.y);
		IMAGEMANAGER->findImage("CurrentHp")->render(getMemDC(), 37 + _cam.x, 90 + _cam.y);
		IMAGEMANAGER->findImage("HpNumber")->frameRender(getMemDC(), 70 + _cam.x, 90 + _cam.y);
		if (_player->_CurHP >= 10)
			IMAGEMANAGER->findImage("HpNumber10")->frameRender(getMemDC(), 55 + _cam.x, 90 + _cam.y);
		IMAGEMANAGER->findImage("Null")->render(getMemDC(), 95 + _cam.x, 40 + _cam.y);
		if (crushcount < 60)
			IMAGEMANAGER->findImage("CrushHp")->render(getMemDC(), 85 + _cam.x, 92 + _cam.y, 0, 0, whitehp, 13);
		IMAGEMANAGER->findImage("UIHpFull")->render(getMemDC(), 85 + _cam.x, 92 + _cam.y, 0, 0, 85 * _player->_CurHP / _player->_MaxHP, 13);
		IMAGEMANAGER->findImage("UIExpFull")->render(getMemDC(), 85 + _cam.x, 72 + _cam.y, 0, 0, 85 * _Weapone.GetWeaponeInfo()._CurExp / _Weapone.GetWeaponeInfo()._MaxExp, 13);
		IMAGEMANAGER->findImage("WeaponeIconChange")->frameRender(getMemDC(), 35 + _cam.x, 40 + _cam.y);
		if (!ihavemachine && !ihaverocket)
			IMAGEMANAGER->findImage("BulletNull")->render(getMemDC(), 115 + _cam.x, 40 + _cam.y);


		else
		{
			IMAGEMANAGER->findImage("WeaponeCurBullet")->frameRender(getMemDC(), 150 + _cam.x, 37 + _cam.y);
			for (int i = 0; i < _vWeapone.size(); i++)
			{
				if (drawcurbullet10)
					IMAGEMANAGER->findImage("WeaponeCurBullet10")->frameRender(getMemDC(), 135 + _cam.x, 37 + _cam.y);
			}
			for (int i = 0; i < _vWeapone.size(); i++)
			{
				if (drawcurbullet100)
					IMAGEMANAGER->findImage("WeaponeCurBullet100")->frameRender(getMemDC(), 120 + _cam.x, 37 + _cam.y);
			}


			IMAGEMANAGER->findImage("WeaponeBullet")->frameRender(getMemDC(), 150 + _cam.x, 54 + _cam.y);

			for (int i = 0; i < _vWeapone.size(); i++)
			{
				if (drawmaxbullet10)
					IMAGEMANAGER->findImage("WeaponeBullet10")->frameRender(getMemDC(), 135 + _cam.x, 54 + _cam.y);
			}

			for (int i = 0; i < _vWeapone.size(); i++)
			{
				if (drawmaxbullet100)
					IMAGEMANAGER->findImage("WeaponeBullet100")->frameRender(getMemDC(), 120 + _cam.x, 54 + _cam.y);
			}
		}
		for (int i = 0; i < _vWeapone.size(); i++)
		{
			WeaponeIcon->setFrameX(_vWeapone[i]->GetWeaponeInfo()._Weapone);
			IMAGEMANAGER->findImage("WeaponeIcon")->frameRender(getMemDC(), 165 + 35 * i + _cam.x, 40 + _cam.y);
		}


	}
	else if (iscrush) //�浹�϶� ������
	{
		if (allcrushcount % 4 == 1)
		{
			IMAGEMANAGER->findImage("UIExpEmpty")->render(getMemDC(), 85 + _cam.x, 70 + _cam.y);
			IMAGEMANAGER->findImage("UIHpEmpty")->render(getMemDC(), 85 + _cam.x, 90 + _cam.y);
			IMAGEMANAGER->findImage("WeaponLv")->render(getMemDC(), 35 + _cam.x, 70 + _cam.y);
			IMAGEMANAGER->findImage("ExpNumber")->frameRender(getMemDC(), 70 + _cam.x, 70 + _cam.y);
			IMAGEMANAGER->findImage("CurrentHp")->render(getMemDC(), 37 + _cam.x, 90 + _cam.y);
			IMAGEMANAGER->findImage("HpNumber")->frameRender(getMemDC(), 70 + _cam.x, 90 + _cam.y);
			if (_player->_CurHP >= 10)
				IMAGEMANAGER->findImage("HpNumber10")->frameRender(getMemDC(), 55 + _cam.x, 90 + _cam.y);
			IMAGEMANAGER->findImage("Null")->render(getMemDC(), 95 + _cam.x, 40 + _cam.y);
			if (crushcount < 60)
				IMAGEMANAGER->findImage("CrushHp")->render(getMemDC(), 85 + _cam.x, 92 + _cam.y, 0, 0, whitehp, 13);
			IMAGEMANAGER->findImage("UIHpFull")->render(getMemDC(), 85 + _cam.x, 92 + _cam.y, 0, 0, 85 * _player->_CurHP / _player->_MaxHP, 13);
			IMAGEMANAGER->findImage("UIExpFull")->render(getMemDC(), 85 + _cam.x, 72 + _cam.y, 0, 0, 85 * _Weapone.GetWeaponeInfo()._CurExp / _Weapone.GetWeaponeInfo()._MaxExp, 13);
			IMAGEMANAGER->findImage("WeaponeIconChange")->frameRender(getMemDC(), 35 + _cam.x, 40 + _cam.y);
			if (!ihavemachine && !ihaverocket)
				IMAGEMANAGER->findImage("BulletNull")->render(getMemDC(), 115 + _cam.x, 40 + _cam.y);
			else
			{
				IMAGEMANAGER->findImage("WeaponeCurBullet")->frameRender(getMemDC(), 150 + _cam.x, 37 + _cam.y);
				for (int i = 0; i < _vWeapone.size(); i++)
				{
					if (drawcurbullet10)
						IMAGEMANAGER->findImage("WeaponeCurBullet10")->frameRender(getMemDC(), 135 + _cam.x, 37 + _cam.y);
				}
				for (int i = 0; i < _vWeapone.size(); i++)
				{
					if (drawcurbullet100)
						IMAGEMANAGER->findImage("WeaponeCurBullet100")->frameRender(getMemDC(), 120 + _cam.x, 37 + _cam.y);
				}


				IMAGEMANAGER->findImage("WeaponeBullet")->frameRender(getMemDC(), 150 + _cam.x, 54 + _cam.y);

				for (int i = 0; i < _vWeapone.size(); i++)
				{
					if (drawmaxbullet10)
						IMAGEMANAGER->findImage("WeaponeBullet10")->frameRender(getMemDC(), 135 + _cam.x, 54 + _cam.y);
				}

				for (int i = 0; i < _vWeapone.size(); i++)
				{
					if (drawmaxbullet100)
						IMAGEMANAGER->findImage("WeaponeBullet100")->frameRender(getMemDC(), 120 + _cam.x, 54 + _cam.y);
				}
			}
			for (int i = 0; i < _vWeapone.size(); i++)
			{
				WeaponeIcon->setFrameX(_vWeapone[i]->GetWeaponeInfo()._Weapone);
				IMAGEMANAGER->findImage("WeaponeIcon")->frameRender(getMemDC(), 165 + 35 * i + _cam.x, 40 + _cam.y);
			}
		}


	}




}
//ī�޶� ����
void cameraAngle::camVibeSwitch()
{
	_isVibe = true;
}

void cameraAngle::cameraVibration()
{
	if (!_isVibe) return;

	_camVibeCount++;

	_cam.xAngle += 0.8f;
	if (_cam.xAngle > PI2) _cam.xAngle -= PI2;
	_cam.yAngle += 0.2f;
	if (_cam.yAngle > PI2) _cam.yAngle -= PI2;

	//_cam.x = cosf(_cam.xAngle) * 4 + _cam.movX; 
	//_cam.y = -sinf(_cam.yAngle) * 5 + _cam.movY;

	if (_camVibeCount >= 90) {
		_isVibe = false;
		_camVibeCount = 0;
		_cam.xAngle = PI / 2;
		_cam.yAngle = 0.f;
	}
}

void cameraAngle::crushevent()
{
	if (_player->_iscrush)
	{
		iscrush = true;
	}

	if (iscrush)
	{
		crushcount++;//�Ͼ��ü�� ������
		allcrushcount++; //��üui ������
		IMAGEMANAGER->addImage("CrushHp", "image/UI/CrushHp.bmp", _player->_CurHP / _player->_MaxHP, 13, false, false);
		if (crushcount > 120)
		{
			whitehp = (85 * _player->_CurHP / _player->_MaxHP); //�浹ī��Ʈ 200�Ѿ�� �Ͼ��ü�¿� ����ü���� �޾ƿ´�
			iscrush = false; //�ʱ�ȭ
			crushcount = 0;
		}
	}
	else
	{
		whitehp = (85 * _player->_CurHP / _player->_MaxHP);
	}

}

void cameraAngle::numbercontrol()
{

	ExpNumber->setFrameX(_Weapone.GetWeaponeInfo()._Lv);//���緹�� ���������� ����
	ExpNumber->setFrameY(0);
	//HpNumber->setFrameX(_player->_CurHP % 10); //����ü�� ������
	HpNumber->setFrameY(0);
	if (_player->_MaxHP > 50) _player->_MaxHP = 50;
	if (_player->_CurHP > _player->_MaxHP) _player->_CurHP = _player->_MaxHP;
	if (_player->_CurHP <= 0)HpNumber->setFrameX(0);

	for (int i = 0; i < 10; i++)
	{
		if (_player->_CurHP % 10 == i)HpNumber->setFrameX(i);

	}
	for (int j = 0; j < 10; j++)
	{
		if (_player->_CurHP / 10 % 10 == j)HpNumber10->setFrameX(j);
	}

	//for (int i = 0; i < _vWeapone.size(); i++)
	if (ihavemachine || ihaverocket)
	{


		if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._CurBullet >= 100) drawcurbullet100 = true;
		else drawcurbullet100 = false;
		if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._CurBullet >= 10) drawcurbullet10 = true;
		else drawcurbullet10 = false;

		if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._MaxBullet >= 100) drawmaxbullet100 = true;
		else drawmaxbullet100 = false;
		if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._MaxBullet >= 10) drawmaxbullet10 = true;
		else drawmaxbullet10 = false;


	}
	if (ihavemachine || ihaverocket)
	{
		for (int j = 0; j < 10; j++)
		{


			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._MaxBullet % 10 == j) WeaponeBullet->setFrameX(j);
			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._MaxBullet / 10 % 10 == j) WeaponeBullet10->setFrameX(j);
			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._MaxBullet / 100 % 10 == j) WeaponeBullet100->setFrameX(j);

			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._CurBullet % 10 == j) WeaponeCurBullet->setFrameX(j);
			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._CurBullet / 10 % 10 == j) WeaponeCurBullet10->setFrameX(j);
			if (_vWeapone[_player->_WeaponeIndex]->GetWeaponeInfo()._CurBullet / 100 % 10 == j) WeaponeCurBullet100->setFrameX(j);

			// i ��° ���������� �����Ѿ˿� 10�������������� j �̸� �����Ѿ��� �����ڸ����� j �� ����
		}
	}

	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("BaseWeapone"))
	{
		ihaverocket = false;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(0);
	}
	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("FireWeapone"))
	{
		ihaverocket = false;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(2);
	}
	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("LaserWeapone"))
	{
		ihaverocket = false;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(6);
	}
	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("MachineWeapone"))
	{
		ihavemachine = true;
		ihaverocket = false;
		WeaponeIconChange->setFrameX(1);
	}
	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("RocketWeapone"))
	{
		ihaverocket = true;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(3);
	}
	if (_Weapone.GetWeaponeInfo()._WeaponeImage == IMAGEMANAGER->findImage("SnakeWeapone"))
	{
		ihaverocket = false;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(5);
	}
	if (_player->_HaveWeapone == 4)
	{
		ihaverocket = false;
		ihavemachine = false;
		WeaponeIconChange->setFrameX(4);
	}
}

void cameraAngle::setCamPos()
{
	if (_player->_isRight) _cam.x = _player->_rc.left + (25 / 2) - WINSIZEX / 3.5;
	//else  _cam.x = _player->_rc.left + (25 / 2) - (WINSIZEX / 3 * 2 + 20);	//���� ���� ���� ��
	else  _cam.x = _player->_rc.left + (25 / 2) - WINSIZEX / 3.5;
	_cam.y = _player->_rc.top + (25 / 2) - WINSIZEY / 2;
	_cam.movX = _cam.x;
	_cam.movY = _cam.y;
}