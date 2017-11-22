// ConsoleApplication14.cpp : Defines the entry point for the console application.
//
/*
	В стандартной библиотеке есть семейство функций to_string для преобразования 
	чисел в строки.Однако обратное преобразование не такое удобное — для каждого 
	числового типа есть своя функция(например, strtoi для int).

	В данном задании вам предлагается написать шаблонную функцию from_string, 
	которая умеет преобразовывать строку в разные типы.
	
	Для реализации from_string предлагается воспользоваться классом std::istringstream, 
	который представляет собой поток ввода из строки, т.е.для преобразования строки в тип T предлагается 
	прочитать значение типа T из потока при помощи оператора >> .В случае неудачного
	преобразования функция должна бросать исключение bad_from_string, класс которого
	вам нужно реализовать самостоятельно.


	Указания:

	Для того, чтобы учитывать пробельные символы, используйте std::noskipws 
	(например, если строка с числом начинается с пробела или заканчивается пробелом, то это должно быть ошибкой).
	
	При переопределении метода what класса std::exception после сигнатуры 
	метода нужно указывать ключевое слово noexcept (про него будет рассказано позже).
	
	Помните, что считывание std::string из потока означает считывание одного слова 
	(т.е. без пробельных символов), а считывание char — одного символа.
	
	Флаг eof() у потоков устанавливается только, если не удалось прочитать символ: 
	если при чтении из потока с 5-ю символами прочли 5 символов, но при этом 6-ой 
	(отсутствующий) символ прочесть не пытались, то eof() будет выдавать false.
	
	Если Вы определили исключение с ключевым словом class, но не забудьте, 
	что нужно унаследоваться от std::exception с ключевым словом public.

	Нашел не большую подсказку в книге "Exploring C++ 11 Ray Lishner" стр. 453
	Как оказалось пришлось потратить время чтобы ее найти, поэтому сохраню ссылку
	https://books.google.ru/books?id=aMx0AgAAQBAJ&pg=PA453&dq=%22from_string(std:%22&hl=ru&sa=X&ved=0ahUKEwicicvQidDXAhVJOpoKHa_lBvwQ6AEIJjAA#v=onepage&q=%22from_string(std%3A%22&f=false
*/

#include "stdafx.h"
#include <sstream>
#include <exception>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

// описание класса исключения bad_from_string
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

// функция from_string
template<class T>
T from_string(std::string const& s)
{
	// создание оптока ввода
	istringstream inputSS;
	// копирование входной строки во внутренний буфер потока
	inputSS.str(s);
	// Удаление лишних пробелов
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
	int    a2 = from_string<int>(s2); // исключение
	double b2 = from_string<double>(s2); // b2 = 12.3
	string c2 = from_string<string>(s2); // c2 = "12.3"

	string s3("abc");
	int    a3 = from_string<int>(s3); // исключение
	double b3 = from_string<double>(s3); // исключение
	string c3 = from_string<string>(s3); // c3 = "abc"

    return 0;
}

