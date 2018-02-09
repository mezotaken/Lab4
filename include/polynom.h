#pragma once

#include <iostream>
#include <string>
#include "monom.h"
#include "list.h"
#define EPS 1e-15
#define OFFSET 120

class polynom
{
private:
	list<monom> pmlist;
public:
	polynom(const std::string ipm = "");
	friend std::ostream& operator<<(std::ostream &ostr,const polynom &pm);
};