#pragma once
#include "node.h"

//---------------Шаблон класса Циклический список с головой---------------//
template<class dtype>
class list
{
private:
	node<dtype>* head;													//Указатель на голову
	node<dtype>* curr;													//Указатель на текущий элемент
	void Clean();														//Служебный метод, очистка списка
public:
	list();																//Конструктор по умолчанию
	~list();															//Деструктор
	list(const list<dtype>& src);										//Конструктор копирования
	list<dtype>& operator=(const list<dtype> &src);						//Перегрузка оператора присваивания
	void Reset() { curr = head; }										//Установка curr на голову
	bool IsEnded() const { return curr->next == head; }					//Проверка на нахождение *curr в конце списка
	void GetNext() { curr = curr->next; }								//Смещение curr на следующий элемент
	void InsertInOrder(dtype elem);										//Вставка в упорядоченный список
};
//------------------------------------------------------------------------//




//-----------------------Очистка списка-----------------------------------//
template <class dtype>
void list<dtype>::Clean()
{
	Reset();
	if (!IsEnded())
	{
		GetNext();
		while (curr != head)
		{
			node<dtype>* temp = curr->next;
			delete curr;
			curr = temp;
		}
		head->next = head;
	}
}

//-----------------------Конструктор по умолчанию-------------------------//
template <class dtype>
list<dtype>::list()
{
	head = new node<dtype>;
	head->next = head;
	Reset();
}

//--------------------------------Деструктор------------------------------//
template <class dtype>
list<dtype>::~list()
{
	Clean();
	delete head;
}

//----------------------Конструктор копирования---------------------------//
template <class dtype>
list<dtype>::list(const list<dtype>& src) : list()
{
	node<dtype>* psrc = src.head;
	node<dtype>* temp = head;
	while (psrc->next != src.head)
	{
		psrc = psrc->next;
		temp->next = new node<dtype>(psrc->data);
		temp = temp->next;
	}
	temp->next = head;
}

//----------------------Оператор присваивания-----------------------------//
template <class dtype>
list<dtype>& list<dtype>::operator=(const list<dtype>& src)
{
	Clean();
	node<dtype>* psrc = src.head;
	node<dtype>* temp = head;
	while (psrc->next != src.head)
	{
		psrc = psrc->next;
		temp->next = new node<dtype>(psrc->data);
		temp = temp->next;
	}
	temp->next = head;
	return *this;
}

//------------------Вставка в упорядоченный список------------------------//
template <class dtype>
void list<dtype>::InsertInOrder(dtype elem)
{
	node<dtype>* temp = new node<dtype>(elem);
	Reset();

	while ((*(curr->next) < *temp) && !IsEnded())
			GetNext();
	node<dtype>* pn = curr->next;
	curr->next = temp;
	curr->next->next = pn;
}
