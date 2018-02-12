#include "gtest.h"
#include "polynom.h"
#include <iostream>
TEST(list, 111)
{
	polynom a("x+1");
	polynom b("2x+1");
	polynom c = -a*b - a;
	std::cout << c <<std::endl;
}
