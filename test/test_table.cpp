#include <gtest.h>
#include <string>
#include <iostream>
#include "ord_table.h"
#include "unord_table.h"
#include "hash_table.h"
using namespace std;



//Тесты на возможность создания
//TEST(lists, can_create_empty_unord_table)
//{
//	ASSERT_NO_THROW(unord_table<int,int> t);
//}
//
//TEST(lists, can_create_ord_empty_table)
//{
//	ASSERT_NO_THROW(ord_table<int, int> t);
//}
//
//TEST(lists, can_create_hash_empty_table)
//{
//	ASSERT_NO_THROW(hash_table<int, int> t);
//}



//Набор таблиц для тестирования
class TestingSetTables: public ::testing::Test {
protected:
	unord_table<int, int> Uemp;
	unord_table<int, int> Ufil;
	ord_table<int, int> Oemp;
	ord_table<int, int> Ofil;
	hash_table<int, int> Hemp;
	hash_table<int, int> Hfil;
public:
	TestingSetTables() :Uemp(10), Ufil(10), Oemp(10), Ofil(10), Hemp(10), Hfil(10)
	{
		Ufil.Insert(11,22);
		Ufil.Insert(5,10);
		Ufil.Insert(7,3);

		Ofil.Insert(11, 22);
		Ofil.Insert(5, 10);
		Ofil.Insert(7, 3);

		Hfil.Insert(11, 22);
		Hfil.Insert(5, 10);
		Hfil.Insert(7, 3);
	}
	~TestingSetTables() {}
};

//Проверка Insert Find Delete в парах для всех таблиц

TEST_F(TestingSetTables, insert_find_in_unord_empty_table)
{
	Uemp.Insert(15, 30);
	Uemp.Insert(4, 22);
	EXPECT_EQ(30, Uemp.Find(15));
	EXPECT_EQ(22, Uemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_unord_empty_table)
{
	Uemp.Insert(15, 30);
	Uemp.Insert(4, 22);
	Uemp.Delete(15);
	Uemp.Delete(4);
	EXPECT_EQ(0,Uemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_unord_empty_table)
{
	Ufil.Delete(5);
	Ufil.Delete(11);
	EXPECT_EQ(3, Ufil.Find(7));
	EXPECT_EQ(1, Ufil.GetCurSize());
}

TEST_F(TestingSetTables, insert_find_in_ord_empty_table)
{
	Oemp.Insert(15, 30);
	Oemp.Insert(4, 22);
	EXPECT_EQ(30, Oemp.Find(15));
	EXPECT_EQ(22, Oemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_ord_empty_table)
{
	Oemp.Insert(15, 30);
	Oemp.Insert(4, 22);
	Oemp.Delete(15);
	Oemp.Delete(4);
	EXPECT_EQ(0, Oemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_ord_empty_table)
{
	Ofil.Delete(5);
	Ofil.Delete(11);
	EXPECT_EQ(3, Ofil.Find(7));
	EXPECT_EQ(1, Ofil.GetCurSize());
}

TEST_F(TestingSetTables, insert_find_in_hash_empty_table)
{
	Hemp.Insert(15, 30);
	Hemp.Insert(4, 22);
	EXPECT_EQ(30, Hemp.Find(15));
	EXPECT_EQ(22, Hemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_hash_empty_table)
{
	Hemp.Insert(15, 30);
	Hemp.Insert(4, 22);
	Hemp.Delete(15);
	Hemp.Delete(4);
	EXPECT_EQ(0, Hemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_hash_empty_table)
{
	Hfil.Delete(5);
	Hfil.Delete(11);
	EXPECT_EQ(3, Hfil.Find(7));
	EXPECT_EQ(1, Hfil.GetCurSize());
}
//--------------------------------