#include "polynom.h"
#include <algorithm>
using namespace std;

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
		if (pos == 0 || pos == 1)
		{
			temp.cf = 1;
			if (part[0] == '-')
				temp.cf = -1;
		}
		else
			temp.cf = stod(part.substr(0, pos));
		part.erase(0, pos);
		part += ' ';

		for (int i = 0; i < 3; i++)
		{
			pos = part.find((char)(OFFSET+i));
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

ostream& operator<<(ostream &ostr,const polynom &pm)
{
	node<monom>* curr = pm.pmlist.GetHead();
	node<monom>* head = curr;
	while (curr->next != head)
	{
		curr = curr->next;
		monom temp = curr->data;

		if (abs(temp.cf - 1) > EPS)
			ostr<< temp.cf;
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
		ostr << "+";
	}
	ostr << endl;
	return ostr;
}
