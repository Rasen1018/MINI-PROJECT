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

	static void switchInput(int& num, char& one) // ���� 1�ڸ��� �޴� �Լ�
	{
		while (1) { one = _getch(); if (one >= '0' && one <= '9') break; printf("\b"); }
		num = one - '0';
	}

	static int integerInput(int& num, int& flag) // ������ �޴� �Լ�
	{
		cin >> num;
		if (!cin) {
			cout << endl << "!! ���ڸ� �Է��ϼ��� !!" << endl << endl;
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

//�ʿ��� ������� ����