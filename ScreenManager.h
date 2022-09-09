#pragma once

#include <Windows.h>

#include "SingletonBase.h"

class ScreenManager : public SingletonBase<ScreenManager>
{
public:
	int mScreenIndex = 0;				// 출력 버퍼 인덱스 변수
	HANDLE mScreen[2] = { nullptr, };   // 더블 버퍼용 배열 (크기 2 = 2개)

	ScreenManager();
	~ScreenManager();

	// 화번 버퍼 초기화, 전위와 후위 버퍼 2개 생성
	void InitScreen();

	// 다음 장면을 위한 화면 클리어
	void ClearScreen();

	// 활성화된 버퍼와 비활성화된 버퍼의 상태를 전환
	void FlipScreen();

	// 생성한 2개의 버퍼를 모두 해제
	void ReleaseScreen();

	// x, y와표에 string 출력
	void PrintScreen(int x, int y, char* string);

	// 화면에 출력할 문자 색상값 지정
	void SetColor(unsigned short color);
};