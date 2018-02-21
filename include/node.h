#pragma once

//Шаблон класса Элемент списка
template<class dtype>
class node
{
public:
	dtype data;		//Данные в элементе
	node* next;		//Указатель на следующий эл-т
	bool operator< (const node& n) { return (data<n.data); }	//Операторы 
	bool operator> (const node& n) { return (data>n.data); }	//сравнения
	node(dtype in) { data = in; next = NULL; }					//Конструктор с параметром
	node() { next = NULL; }										//Конструктор по умолчанию
};
