#pragma once
#pragma warning (disable:4996)

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
	void screenInit();

	// ���� ����� ���� ȭ�� Ŭ����
	void screenClear();

	// Ȱ��ȭ�� ���ۿ� ��Ȱ��ȭ�� ������ ���¸� ��ȯ
	void screenFlipping();

	// ������ 2���� ���۸� ��� ����
	void screenRelease();

	// x, y��ǥ�� string ���
	void screenPrint(int x, int y, char* string);

	// ȭ�鿡 ����� ���� ���� ����
	void setColor(unsigned short color);
};