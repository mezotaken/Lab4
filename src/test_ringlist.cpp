#include "gtest.h"
#include "list.h"
#include <iostream>
TEST(list, 111)
{
	list<int> abc;
	abc.InsertInOrder(6);
	abc.InsertInOrder(4);
	abc.InsertInOrder(5);
	list<int> def;
	def = abc;
}
