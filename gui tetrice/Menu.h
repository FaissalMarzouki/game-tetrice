#pragma once
#include <iostream>
#include <conio.h>
#include<Windows.h>


class Menu
{
public:
	const static int timer_x = 7, timer_y = 7;
	int size;
	Menu(std::string options[], int size);
	int get_choice();
	static void gotoxy(int x, int y, std::string s);
	static void gotoxy(int x, int y, char s);

};