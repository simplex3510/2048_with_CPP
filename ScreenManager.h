#pragma once

#include <Windows.h>

#include "SingletonBase.h"

class ScreenManager : public SingletonBase<ScreenManager>
{
public:
	int mScreenIndex = 0;				// ��� ���� �ε��� ����
	HANDLE mScreen[2] = { nullptr, };   // ���� ���ۿ� �迭 (ũ�� 2 = 2��)

	ScreenManager();
	~ScreenManager();

	// ȭ�� ���� �ʱ�ȭ, ������ ���� ���� 2�� ����
	void InitScreen();

	// ���� ����� ���� ȭ�� Ŭ����
	void ClearScreen();

	// Ȱ��ȭ�� ���ۿ� ��Ȱ��ȭ�� ������ ���¸� ��ȯ
	void FlipScreen();

	// ������ 2���� ���۸� ��� ����
	void ReleaseScreen();

	// x, y��ǥ�� string ���
	void PrintScreen(int x, int y, char* string);

	// ȭ�鿡 ����� ���� ���� ����
	void SetColor(unsigned short color);
};