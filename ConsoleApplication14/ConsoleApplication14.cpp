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

	����� �� ������� ��������� � ����� "Exploring C++ 11 Ray Lishner" ���. 453
	��� ��������� �������� ��������� ����� ����� �� �����, ������� ������� ������
	https://books.google.ru/books?id=aMx0AgAAQBAJ&pg=PA453&dq=%22from_string(std:%22&hl=ru&sa=X&ved=0ahUKEwicicvQidDXAhVJOpoKHa_lBvwQ6AEIJjAA#v=onepage&q=%22from_string(std%3A%22&f=false
*/

#include "stdafx.h"
#include <sstream>
#include <exception>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

// �������� ������ ���������� bad_from_string
class bad_from_string : public std::exception
{
public:
	bad_from_string(const char* s) {
	}
	virtual ~bad_from_string()
	{
	}
	//virtual const char* what() const
	//{
	//}
};

// ������� from_string
template<class T>
T from_string(std::string const& s)
{
	// �������� ������ �����
	istringstream inputSS;
	// ����������� ������� ������ �� ���������� ����� ������
	inputSS.str(s);
	// �������� ������ ��������
	inputSS >> std::noskipws;
	
	T val;
	char extra;

	if ( ! (inputSS >> val)) 
		throw bad_from_string("error");
	else if (inputSS >> extra)
		throw bad_from_string("error");
	else
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

