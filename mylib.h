#pragma once 
#include <stdio.h>
#include <conio.h>
#include<ctime> 
#include "windows.h" 
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#include <cstring>

using namespace std;
#define KEY_NONE	-1
#define HEIGHT 29
#define WIDTH 119
wstring _frame = L"┌─┐│└┘";


void SetColor(WORD color) 
{
	HANDLE hConsoleOutput; 
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info; 
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info); 

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
//int inputKey()
//{
//	if (_kbhit()) //true
//	{
//		int key = _getch();
//
//		if (key == 224)
//		{
//			key = _getch();
//			return key + 1000;
//		}
//
//		return key;
//	}
//	else
//	{
//		return KEY_NONE;
//	}
//	return KEY_NONE;
//}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

struct MyWindows {
	int left;
	int top;
	int width;
	int height;
	int background;
	int foreground; 
	MyWindows() {
		left = 0;
		top = 0;
		width = WIDTH;
		height = HEIGHT;
		background = 0; //mau den
		foreground = 7; //mau trang
	}

	MyWindows(int l, int t, int w, int h, int bg, int fg) {
		left = l;
		top = t;
		width = w;
		height = h;
		background = bg;
		foreground = fg;
	}

	void gotoXY(int x, int y) { //di chuyen con tro den vi tri x, y
		COORD coord = { left + x, top + y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}


	wstring ConvertToWString(string st) //chuyen string sang wstring
	{
		using convert_t = std::codecvt_utf8<wchar_t>; //conversion between Unicode and UTF-8
		wstring_convert<convert_t, wchar_t> strconverter; 
		return strconverter.from_bytes(st); //convert string to wstring
	}

	void Write(wstring st, int x, int y, int backgroundColor, int foregroundColor) {
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); 
		int stringlen = st.length();
		const wchar_t* text = st.c_str();
		CHAR_INFO* consoletext = new CHAR_INFO[stringlen];
		COORD a = { stringlen, 1 }, b = { 0, 0 };
		SMALL_RECT c = { left + x, top + y, left + x + stringlen, top + y + 1 };
		WORD wColor = ((backgroundColor & 0x0F) << 4) + (foregroundColor & 0x0F);
		for (int i = 0; i < stringlen; i++)
		{
			consoletext[i].Char.UnicodeChar = text[i];
			consoletext[i].Attributes = wColor;
		}
		WriteConsoleOutput(hout, consoletext, a, b, &c);
	}
	
	void Write(string st, int x, int y, int backgroundColor, int foregroundColor) {
		Write(ConvertToWString(st), x, y, backgroundColor, foregroundColor);
	}


	void drawFrame() { //ve khung 
		Write(_frame.substr(0, 1), 0, 0, background, foreground);
		for (int i = 0; i < width - 2; i++)
		{
			Write(_frame.substr(1, 1), 1 + i, 0, background, foreground); 
		}
		Write(_frame.substr(2, 1), width - 1, 0, background, foreground);

		for (int i = 1; i < height - 1; i++)
		{
			Write(_frame.substr(3, 1), 0, i, background, foreground);
			Write(_frame.substr(3, 1), width - 1, i, background, foreground);
		}

		Write(_frame.substr(4, 1), 0, height - 1, background, foreground);
		for (int i = 0; i < width - 2; i++)
		{
			Write(_frame.substr(1, 1), 1 + i, height - 1, background, foreground);
		}
		Write(_frame.substr(5, 1), width - 1, height - 1, background, foreground);
	}

	void clearConsole() { //xoa man hinh
		for (int row = 1; row < height - 1; row++)
		{
			for (int col = 1; col < width - 1; col++)
			{
				Write(L" ", col, row, background, foreground);
			}
		}
	}

};







