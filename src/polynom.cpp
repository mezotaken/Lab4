#include "polynom.h"
using namespace std;
//Конструктор по строке
polynom::polynom(string ipm)
{
	int d[3] = { 100,10,1 };
	while (ipm.length())
	{
		string part;
		monom temp;
		int pos = 1; 
		while (pos < ipm.length() && ipm[pos] != '+' && ipm[pos] != '-')
			pos++;
		part = ipm.substr(0, pos);
		ipm.erase(0, pos);
		pos = 0;
		while (part[pos] != 'x' && part[pos] != 'y' && part[pos] != 'z' && pos < part.length())
			pos++;

		string coef = part.substr(0,pos);
		if (coef == "+" || coef.length() == 0)
			temp.cf = 1;
		else if (coef == "-")
			temp.cf = -1;
		else temp.cf = stod(coef);

		if (abs(temp.cf) > EPS)
		{
			part.erase(0, pos);
			part += ' ';

			for (int i = 0; i < 3; i++)
			{
				pos = part.find((char)(OFFSET + i));
				if (pos > -1)
				{
					if (part[pos + 1] != '^')
						part.insert(pos + 1, "^1");
					temp.abc += d[i] * stoi(part.substr(pos + 2, 1));
					part.erase(pos, 3);
				}
			}

			pmlist.InsertInOrder(temp);
		}
	}
	
}

//Оператор сложения полиномов
polynom polynom::operator+(const polynom& pmr) const
{
	polynom res;
	node<monom>* pmlh = pmlist.GetHead();
	node<monom>* pmrh = pmr.pmlist.GetHead();
	node<monom>* resh = res.pmlist.GetHead();
	node<monom>* cl = pmlh->next;
	node<monom>* cr = pmrh->next;
	while (cl != pmlh && cr != pmrh)
	{
		if (cl->data < cr->data)
		{
			resh->next = new node<monom>(cl->data);
			cl = cl->next;
			resh = resh->next;
		}
		else if (cl->data > cr->data)
		{
			resh->next = new node<monom>(cr->data);
			cr = cr->next;
			resh = resh->next;
		}
		else
		{
			double coef = cl->data.cf + cr->data.cf;
			if (abs(coef) > EPS)
			{
				resh->next = new node<monom>(monom(coef, cl->data.abc));
				resh = resh->next;
			}
			cl = cl->next;
			cr = cr->next;
		}
	}
	while (cl != pmlh)
	{
		resh->next = new node<monom>(cl->data);
		cl = cl->next;
		resh = resh->next;
	}
	while (cr != pmrh)
	{
		resh->next = new node<monom>(cr->data);
		cr = cr->next;
		resh = resh->next;
	}
	resh->next = res.pmlist.GetHead();
	return res;
}

//Умножение на константу
polynom polynom::operator*(const double mp) const
{
	polynom res;
	if (abs(mp) > EPS)
	{
		res = *this;
		node<monom>* curr = res.pmlist.GetHead()->next;
		while (curr != res.pmlist.GetHead())
		{
			curr->data.cf *= mp;
			curr = curr->next;
		}
	}
	return res;
}

//Оператор умножения полиномов
polynom polynom::operator*(const polynom& pml) const
{
	polynom res;
	node<monom>* curr = pml.pmlist.GetHead()->next;
	while (curr != pml.pmlist.GetHead())
	{
		polynom temp(*this);
		node<monom>* pos = temp.pmlist.GetHead()->next;
		while (pos != temp.pmlist.GetHead())
		{
			pos->data.cf *= curr->data.cf;
			int nabc = pos->data.abc + curr->data.abc;
			if (nabc / 100 < 10 && nabc / 10 % 10 < 10 && nabc % 10 < 10)
				pos->data.abc = nabc;
			else
				throw "Too large exponent";
			pos = pos->next;
		}
		res = res + temp;
		curr = curr->next;
	}
	return res;
}

//Оператор вставки в поток
ostream& operator<<(ostream &ostr,const polynom& pm)
{
	node<monom>* curr = pm.pmlist.GetHead();
	node<monom>* head = curr;
	while (curr->next != head)
	{
		curr = curr->next;
		monom temp = curr->data;

		if (abs(temp.cf - 1) > EPS && abs(temp.cf + 1) > EPS || temp.abc == 0)
			ostr << temp.cf;
		else if (abs(temp.cf + 1) < EPS && abs(temp.cf - 1) > EPS)
			ostr << '-';
		int p = temp.abc / 100;
		if(p>1)
			ostr << "x^" << p;
		else if (p == 1) ostr << "x";
		p = temp.abc / 10 % 10;
		if(p>1)
			ostr << "y^" << p;
		else if (p == 1) ostr << "y";
		p = temp.abc % 10;
		if(p>1)
			ostr<< "z^" << p;
		else if (p == 1) ostr << "z";
		if(curr->next != head && curr->next->data.cf>0)
			ostr << "+";
	}
	return ostr;
}
