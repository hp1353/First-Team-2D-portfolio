#include "stdafx.h"
#include "animation.h"


animation::animation()
	: _frameNum(0)
	, _frameWidth(0)
	, _frameHeight(0)
	, _loop( FALSE )
	, _frameUpdateSec(0)
	, _elapsedSec(0)
	, _nowPlayIdx(0)
	, _play(FALSE)
{
}


animation::~animation()
{
}

HRESULT animation::init( int totalW, int totalH, int frameW, int frameH )
{
	//가로 프레임 수
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();
	for ( int i = 0; i < _frameNumHeight; i++ )
	{
		for ( int j = 0; j < _frameNumWidth; j++ )
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 리스트에 추가
			_frameList.push_back( framePos );
		}
	}

	//기본 프레임으로 셋팅
	setDefPlayFrame();

	return S_OK;
}

void animation::setDefPlayFrame( BOOL reverse, BOOL loop )
{
	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//다시 되돌아 오는 애니메이션이라면...
	if ( reverse )
	{
		//루프 애니메이션이라면...
		if ( _loop )
		{
			//갈때 프레임
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}
			//올때 프레임
			for ( int i = _frameNum - 2; i > 0; i-- )//루프기때문에 마지막 시작 프레임은 빠짐
			{
				_playList.push_back( i );
			}
		}
		//루프 애니메이션이 아니면...
		else
		{
			//갈때 프레임
			for ( int i = 0; i < _frameNum; i++ )
			{
				_playList.push_back( i );
			}

			//올때 프레임
			for ( int i = _frameNum - 2; i >= 0; i-- )//루프가 아니기 때문에 마지막까지 포함
			{
				_playList.push_back( i );
			}
		}
	}
	//다시 되돌아오는 애니메이션이 아니라면....
	else
	{
		//갈때 애니메이션
		for ( int i = 0; i < _frameNum; i++ )
		{
			_playList.push_back( i );
		}
	}
}

void animation::setPlayFrame( int * playArr, int arrLen, BOOL bLoop )
{
	//루프 여부 대입
	_loop = bLoop;

	//플레이 리스트 클리어
	_playList.clear();

	//정직하게 프레임으로 셋팅
	for ( int i = 0; i < arrLen; i++ )
	{
		_playList.push_back( playArr[i] );
	}
}

void animation::setPlayFrame( int start, int end, BOOL reverse, BOOL loop )
{
	//루프 여부 대입
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if ( start == end )
	{
		//시작프레임과 끝프레임이 같은 경우
		_playList.clear();
		stop();	//애니메이션 할 필요가 없음.
		return;
	}

	//시작 프레임이 종료 프레임보다 큰 경우
	if ( start > end )
	{
		//다시 되돌아오는 애니메이션이라면...
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i >= end; i-- )
				{
					_playList.push_back( i );
				}

				for ( int i = end + 1; i < start; i++ )
				{
					_playList.push_back( i );
				}
			}
			else
			{
				for ( int i = start; i >= end; i-- )
				{
					_playList.push_back( i );
				}

				for ( int i = end + 1; i <= start; i++ )
				{
					_playList.push_back( i );
				}
			}
		}
		else
		{
			for ( int i = start; i >= end; i-- )
			{
				_playList.push_back( i );
			}
		}
	}
	// start < end
	else
	{
		//다시 되돌아오는 애니메이션이라면...
		if ( reverse )
		{
			if ( _loop )
			{
				for ( int i = start; i <= end; i++ )
				{
					_playList.push_back( i );
				}

				for ( int i = end - 1; i > start; i-- )
				{
					_playList.push_back( i );
				}
			}
			else
			{
				for ( int i = start; i <= end; i++ )
				{
					_playList.push_back( i );
				}

				for ( int i = end - 1; i >= start; i-- )
				{
					_playList.push_back( i );
				}
			}
		}
		else
		{
			for ( int i = start; i <= end; i++ )
			{
				_playList.push_back( i );
			}
		}
	}

}

void animation::setFPS( int framePerSec )
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate( float elapsedTime )
{
	if ( _play )
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 되었다면...
		if ( _elapsedSec >= _frameUpdateSec )
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;

			if ( _nowPlayIdx == _playList.size() )
			{
				//루프 프레이라면...
				if ( _loop )
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_play = FALSE;
				}
			}
		}
	}
}

void animation::start()
{
	_play = TRUE;
	_nowPlayIdx = 0;
}

void animation::stop()
{
	_play = FALSE;
	_nowPlayIdx = 0;
}

void animation::pause()
{
	_play = FALSE;
}

void animation::resume()
{
	_play = TRUE;
}
