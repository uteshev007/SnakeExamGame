#pragma once
//
// ���� ���������, Header file
//  Win10.h 
//
using namespace std;
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>  // ��� _getch(), _getche(), _kbhit()
#include <io.h>     // �������������� ����-�����
#include <time.h>
#include <ctime>



// ���������� ����������� ����
enum _COLOR {
	BLACK,    // = 0
	BLUE,     // 1 = BLACK + 1
	GREEN,    // 2 = BLUE  + 1
	AQUA,     // 3 = GREEN + 1
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};

// ������������ ����� ������ ����������
// ������������ ������������ � ������ KEY
enum _KEY {
	ESC = 27,				// ESC
	ENTER = 13,			// ����
	SPACE = 32,     // ������
	TAB = 9,				// ������� ���������
	BACKSPACE = 8,
	PLUS = 43, MINUS = 45,

	// �������� ��� ��������� ������
	CURSOR1 = 0, CURSOR2 = 224,

	// ���� ������ ���������� ��������
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77,

	INS = 82, DEL = 83,
	HOME = 71, END = 79,
	PG_UP = 73, PG_DOWN = 81,

	F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10, // CURSOR1, 59-68
	F11 = 133, F12 = 134, // CURSOR2, 133-134
};


// ������������� ������� ��� ����� �����
void SetColor(int colBkgr, int colSym) {
	int wAttributes = colBkgr * 16 + colSym;
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle
	SetConsoleTextAttribute(hOUTPUT, wAttributes);
}

void SetColor(WORD wAttributes) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOUTPUT, wAttributes); // Get console handle
}

// ������� ��� ��������� ������� ������� ������
void SetPos(int Row, int Col) {
	COORD cd;
	cd.X = Col;
	cd.Y = Row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

// ������� ��� ������� �������
void CursorHide(BOOL bVisible = FALSE, DWORD dwSize = 10) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle
	// Hide console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = dwSize;
	cursorInfo.bVisible = bVisible;
	SetConsoleCursorInfo(hOUTPUT, &cursorInfo);
}

// �-��� ��������� ������� � ������ �������
void SetConsoleMode(int nFont, int Lines, int Columns) {
	CONSOLE_FONT_INFOEX cfon{};
	ZeroMemory(&cfon, sizeof(CONSOLE_FONT_INFOEX));
	cfon.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfon.nFont = nFont;
	cfon.FontFamily = 0;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfon);
	char str[100];
	sprintf_s(str, "mode con cols=%d lines=%d", Columns, Lines);
	system(str); //system("mode con cols=80 lines=50");
	system("cls");
	CursorHide(0, 10);
}

// �-��� ����������� �������� ������� ����������� ����
void GetConsoleSize(int& Width, int& Height) {
	CONSOLE_SCREEN_BUFFER_INFOEX sb{ sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &sb);
	Width = sb.srWindow.Right - sb.srWindow.Left + 1;
	Height = sb.srWindow.Bottom - sb.srWindow.Top + 1;
	/*
	std::cout << "CONSOLE_SCREEN_BUFFER_INFOEX::" << std::endl
		<< " cbSize   = " << sb.cbSize << std::endl
		<< " dwSize.X = " << sb.dwSize.X << std::endl
		<< " dwSize.Y = " << sb.dwSize.Y << std::endl
		<< " dwCursorPosition.X = " << sb.dwCursorPosition.X << std::endl
		<< " dwCursorPosition.Y = " << sb.dwCursorPosition.Y << std::endl
		<< " wAttributes     = " << sb.wAttributes << std::endl
		<< " srWindow.Left   = " << sb.srWindow.Left   << std::endl
		<< " srWindow.Top    = " << sb.srWindow.Top    << std::endl
		<< " srWindow.Right  = " << sb.srWindow.Right  << std::endl
		<< " srWindow.Bottom = " << sb.srWindow.Bottom << std::endl
		<< " dwMaximumWindowSize.X = " << sb.dwMaximumWindowSize.X << std::endl
		<< " dwMaximumWindowSize.Y = " << sb.dwMaximumWindowSize.Y << std::endl
		<< " wPopupAttributes = " << sb.wPopupAttributes << std::endl
		<< " bFullscreenSupported = " << sb.bFullscreenSupported << std::endl;
	std::cout << " ColorTable[16]:\n    N: A  R  G  B\n";
	for(size_t i = 0; i < sizeof(sb.ColorTable)/sizeof(sb.ColorTable[0]); i++) {
		unsigned char *pdw = (unsigned char*)(sb.ColorTable+i);
		printf("   %2d: %02X %02X %02X %02X\n", i, pdw[3], pdw[0], pdw[1], pdw[2] );
		//std::cout << std::hex << sb.ColorTable[i] << " ";
	}
	std::cout << std::dec << std::endl;
	*/
}

// �-��� ��������� ������� ����������� ����
void SetConsoleSize(int Width, int Height)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX sb{ sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
	GetConsoleScreenBufferInfoEx(hCon, &sb);
	sb.dwSize.X = Width;
	sb.dwSize.Y = Height;
	sb.srWindow.Left = sb.srWindow.Top = 0;
	sb.srWindow.Right = ((Width > sb.dwMaximumWindowSize.X) ? sb.dwMaximumWindowSize.X : Width);
	sb.srWindow.Bottom = ((Height > sb.dwMaximumWindowSize.Y) ? sb.dwMaximumWindowSize.Y : Height);
	SetConsoleScreenBufferInfoEx(hCon, &sb);
}

void SetConsoleSize(SIZE szConsWin) {
	SetConsoleSize(szConsWin.cx, szConsWin.cy);
}
