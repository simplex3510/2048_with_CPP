#pragma once
#pragma warning (disable:4996)

#include "ScreenManager.h"

/*
static�� ��� ���
 1. ���α׷��� ����Ǵ� ���ȿ� ����ؼ� �����ؾ� �� ������ �ʿ�
 2. �� ������ �����ϴ� ������ �ϳ��� �Լ� �� ��

 static ���� ������ ���
 1. ����ƽ ���� ������ �ش� ���� �������� �����ϱ� ���� �����.

    => �� �Ʒ��� �� ������ �׻� �����Ǹ�, screen.c ������ �����Ѵ�.
*/

/* HANDLE�� �ǹ� *******************************************************************************\
* 1. �ü���� �����ϱ� ���ؼ� �����͸� ����� �� ����                                         *
* 2. ������ ��ſ� 'HANDLE(�ڵ�)'�̶�� ������ �����.                                          *
* 3. �ڵ��� �ü�� ���ο� �ִ� � ���ҽ��� �ּҸ� ������ ġȯ�� ���̴�.                     *
* 4. HANDLE = unsigned int                                                                      *
*  => �� �ڵ��� �ü�� ���ҽ��� �����ϰ� �����ϱ� ���ؼ� ������ ��� ������ �� �ִ� ����       *
\***********************************************************************************************/

ScreenManager::ScreenManager() : SingletonBase()
{
    std::cout << "ScreenManager instance was created." << std::endl;
}

ScreenManager::~ScreenManager() { }

// ��ũ�� �ʱ�ȭ(�ʱ� ����)
void ScreenManager::screenInit()
{
    system("Test2048");             // �ܼ�â �̸� ����
    system("mode con cols=100 lines=50");       // cols(����), line(����)

    // ȭ�� ���� ���� �� ����
    // �Ű� ���� = (�ܼ� ȭ�� ���ۿ� ���� �׼���, ���� ���� ����, ����� ����, ������ �ܼ� ȭ�� ���� ����, Reserved; should be NULL.)
    mScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    mScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    CONSOLE_CURSOR_INFO consoleCursorInfo;      // �ܼ��� Ŀ���� ���� ������ ���� ���� ����

    //Ŀ�� ���� ���� - �����
    consoleCursorInfo.dwSize = 1;               // Ŀ���� ä������ ���� ���� ����(1~100) - 1��ŭ
    consoleCursorInfo.bVisible = false;         // ȭ�� ǥ�� ���� - �� ��

    // ������ ��ũ�� ���ۿ� ������ Ŀ���� ������ ����.
    // ���� �Ѵ� consoleCursorInfo ������ ���� ���� - Ŀ�� ��� �� ��
    SetConsoleCursorInfo(mScreen[0], &consoleCursorInfo);
    SetConsoleCursorInfo(mScreen[1], &consoleCursorInfo);
}

// ���� ����(��ȯ)
void ScreenManager::screenFlipping()
{
    // ���޹��� ���۸� ȭ�鿡 ���
    SetConsoleActiveScreenBuffer(mScreen[mScreenIndex]);

    // �ٸ� ���� ����� ���� �ε��� �� ��ȯ
    mScreenIndex = mScreenIndex == 0 ? 1 : 0;
}

// ��ũ�� Ŭ����
void ScreenManager::screenClear()
{
    // COORD�� ��ǥ���� ������ �� �ִ� ����ü
    COORD Coor = { 0,0 };
    // dw���� ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������
    DWORD dw;
    // ���ۿ�, (����)�� ä���, 80*25 ��ŭ, (0, 0)(Coor)���� �����Ͽ�
    FillConsoleOutputCharacter(mScreen[mScreenIndex], ' ', 123 * 33, Coor, &dw);

}

// ȭ�� ����
void ScreenManager::screenRelease()
{
    /* �ڵ� ������ ���Ͽ�
    * 1. �ڵ� ������ ������� �ʴ� �ڵ��� �������� ���� �� �߻�
    * 2. ������ ����Ʈ���� ������ �� �����̴�.
    * 3. Ư�� �Ⱓ���� ����, �ݺ������� �Ͼ�� ��� -> �ټ��� �ڵ���� ��� ������ ǥ�õǰ� ����� �� ���Ե� -> �ᱹ ���� ������ �浹�� ����Ŵ
    */


    // ���� 2�� �� �ݱ�
    CloseHandle(mScreen[0]);
    CloseHandle(mScreen[1]);
}

// ������ ��ǥ�� string�� ���
void ScreenManager::screenPrint(int x, int y, char* string)
{
    // dw���� ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������
    DWORD dw;
    // Ŀ���� ��ġ
    COORD CursorPosition = { x, y };

    // Ŀ�� ��ġ���� ���ڿ� ����ϱ� ���� Ŀ�� ��ġ ����
    // Ŀ���� ����� ����, ��ǥ ����
    SetConsoleCursorPosition(mScreen[mScreenIndex], CursorPosition);

    // ���ڿ��� ȭ�鿡 ���
    // ���� ����, ����� ��Ʈ��, ��Ʈ�� ����, dw������, �񵿱� ����� �̻��
    WriteFile(mScreen[mScreenIndex], string, strlen(string), &dw, NULL);
}

// ���� ����
void ScreenManager::setColor(unsigned short color)
{
    // ���� ����, ���� ����
    SetConsoleTextAttribute(mScreen[mScreenIndex], color);
}