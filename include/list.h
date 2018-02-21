#pragma once
#include "node.h"

//---------------Шаблон класса Циклический список с головой---------------//
template<class dtype>
class list
{
private:
	node<dtype>* head;									//Указатель на голову
	void Clean();										//Служебный метод, очистка списка
public:
	list();												//Конструктор по умолчанию
	~list();											//Деструктор
	list(const list<dtype>& src);						//Конструктор копирования
	list<dtype>& operator=(const list<dtype>& src);		//Перегрузка оператора присваивания
	void InsertInOrder(dtype elem);						//Вставка в упорядоченный список
	node<dtype>* GetHead() const { return head; }		//Получить указатель на голову
	bool operator==(const list<dtype>& rlst) const;								//Операторы
	bool operator!=(const list<dtype>& rlst) const { return !(*this == rlst); }	//Сравнения
};
//------------------------------------------------------------------------//

//-----------------------Очистка списка-----------------------------------//
template <class dtype>
void list<dtype>::Clean()
{
	node<dtype>* curr = head->next;
		while (curr != head)
		{
			node<dtype>* temp = curr->next;
			delete curr;
			curr = temp;
		}
		head->next = head;
}

//-----------------------Конструктор по умолчанию-------------------------//
template <class dtype>
list<dtype>::list()
{
	head = new node<dtype>;
	head->next = head;
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
	node<dtype>* pcur = head;
	while (psrc->next != src.head)
	{
		psrc = psrc->next;
		pcur->next = new node<dtype>(psrc->data);
		pcur = pcur->next;
	} 
	pcur->next = head;
}

//----------------------Оператор присваивания-----------------------------//
template <class dtype>
list<dtype>& list<dtype>::operator=(const list<dtype>& src)
{
	Clean();
	node<dtype>* psrc = src.head;
	node<dtype>* pcur = head;
	while (psrc->next != src.head)
	{
		psrc = psrc->next;
		pcur->next = new node<dtype>(psrc->data);
		pcur = pcur->next;
	}
	pcur->next = head;
	return *this;
}

//------------------Вставка в упорядоченный список------------------------//
template <class dtype>
void list<dtype>::InsertInOrder(dtype elem)
{
	node<dtype>* temp = new node<dtype>(elem);
	node<dtype>* curr = head;

	while ((*(curr->next) < *temp) && curr->next != head)
		curr = curr->next;
	node<dtype>* pn = curr->next;
	curr->next = temp;
	curr->next->next = pn;
}

//----------------Оператор сравнения--------------------------------------//
template<class dtype>
bool list<dtype>::operator==(const list<dtype>& rlst) const
{
	bool res = true;
	if (this != &rlst)
	{
		node<dtype>* pr = rlst.head->next;
		node<dtype>* pl = head->next;
		while (pr->data == pl->data && pl != head && pr != rlst.head)
		{
			pr = pr->next;
			pl = pl->next;
		}
		if (pl != head || pr != rlst.head)
			res = false;
	}
	return res;
}
