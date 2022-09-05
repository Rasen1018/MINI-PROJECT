#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <iomanip>

using namespace std;

class Primary {
public:
	Primary() {}

	static void switchInput(int& num, char& one) // 숫자 1자리만 받는 함수
	{
		while (1) { one = _getch(); if (one >= '0' && one <= '9') break; printf("\b"); }
		num = one - '0';
	}

	static int integerInput(int& num, int& flag) // 정수만 받는 함수
	{
		cin >> num;
		if (!cin) {
			cout << endl << "!! 숫자만 입력하세요 !!" << endl << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return 0;
		}
		else {
			flag = 1;
			return flag;
		}
	}
};

// 	while (1) { one = _getch(); if (one >= '0' && one <= '9') break; printf("\b "); }
//num = one - '0';

//필요한 헤더파일 모음