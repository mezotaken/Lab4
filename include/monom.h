#pragma once

//Класс Моном
class monom
{
public:
	double cf;				//Коэффициент перед мономом
	unsigned int abc;		//Свёрнутая степень
	bool operator< (const monom& m) { return (abc<m.abc); }	//Операторы 
	bool operator> (const monom& m) { return (abc>m.abc); }	//сравнения
	monom(double icf = 0, unsigned int iabc = 0) { cf = icf; abc = iabc; }	//Конструктор
	monom& operator=(const monom& src) { cf = src.cf, abc = src.abc; return *this; }		//Оператор присваивания
};