#include <gtest.h>
#include <string>
#include "ord_table.h"
#include "unord_table.h"
#include "hash_table.h"
#include <iostream>
#include <random>  
using namespace std;

TEST(table,test)
{
	hash_table<string, int> A(8);
	A.Insert("w",15);
	A.Insert("z", 23);
	A.Insert("k", 100);
	A.Insert("D", 15566);
	A.Delete("w");
	cout<<A.Find("D");
	cout << A.Find("z");
	cout << A.Find("k"); 
	cout << A.Find("w");
}