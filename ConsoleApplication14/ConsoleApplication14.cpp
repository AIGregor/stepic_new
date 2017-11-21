// ConsoleApplication14.cpp : Defines the entry point for the console application.
//
/*
	� ����������� ���������� ���� ��������� ������� to_string ��� �������������� 
	����� � ������.������ �������� �������������� �� ����� ������� � ��� ������� 
	��������� ���� ���� ���� �������(��������, strtoi ��� int).

	� ������ ������� ��� ������������ �������� ��������� ������� from_string, 
	������� ����� ��������������� ������ � ������ ����.
	
	��� ���������� from_string ������������ ��������������� ������� std::istringstream, 
	������� ������������ ����� ����� ����� �� ������, �.�.��� �������������� ������ � ��� T ������������ 
	��������� �������� ���� T �� ������ ��� ������ ��������� >> .� ������ ����������
	�������������� ������� ������ ������� ���������� bad_from_string, ����� ��������
	��� ����� ����������� ��������������.


	��������:

	��� ����, ����� ��������� ���������� �������, ����������� std::noskipws 
	(��������, ���� ������ � ������ ���������� � ������� ��� ������������� ��������, �� ��� ������ ���� �������).
	
	��� ��������������� ������ what ������ std::exception ����� ��������� 
	������ ����� ��������� �������� ����� noexcept (��� ���� ����� ���������� �����).
	
	�������, ��� ���������� std::string �� ������ �������� ���������� ������ ����� 
	(�.�. ��� ���������� ��������), � ���������� char � ������ �������.
	
	���� eof() � ������� ��������������� ������, ���� �� ������� ��������� ������: 
	���� ��� ������ �� ������ � 5-� ��������� ������ 5 ��������, �� ��� ���� 6-�� 
	(�������������) ������ �������� �� ��������, �� eof() ����� �������� false.
	
	���� �� ���������� ���������� � �������� ������ class, �� �� ��������, 
	��� ����� �������������� �� std::exception � �������� ������ public.
*/

#include "stdafx.h"
#include <sstream>
#include <exception>
#include <string>
#include <iostream>

using namespace std;

// �������� ������ ���������� bad_from_string
class bad_from_string : std::exception
{
public:
	virtual ~bad_from_string()
	{
	}
	virtual const char* what() const
	{

	}
};

// ������� from_string
template<class T>
T from_string(std::string const& s)
{
	// �������� ������ �����
	istringstream inputSS;
	// ����������� ������� ������ �� ���������� ����� ������
	inputSS.str(s);
	T val;

	while (!inputSS.eof()) {	
		try {
			inputSS >> val;
			cout << val;
		}
		catch (bad_from_string const& e) {
			cerr << e.what() << endl;
		}
	}
	cout << endl;
	return val;
};


int main()
{ 
	string s1("123");
	int    a1 = from_string<int>(s1); // a1 = 123
	double b1 = from_string<double>(s1); // b1 = 123.0
	string c1 = from_string<string>(s1); // c1 = "123"

	string s2("12.3");
	int    a2 = from_string<int>(s2); // ����������
	double b2 = from_string<double>(s2); // b2 = 12.3
	string c2 = from_string<string>(s2); // c2 = "12.3"

	string s3("abc");
	int    a3 = from_string<int>(s3); // ����������
	double b3 = from_string<double>(s3); // ����������
	string c3 = from_string<string>(s3); // c3 = "abc"

    return 0;
}

