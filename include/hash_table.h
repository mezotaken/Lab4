#pragma once
#include "table.h"
#include <string>
#include <random>  
#define LOADFACTOR_LIMIT 0.75

template <typename KeyType> class Hash
{
public:
	static int get(const KeyType& key)
	{
		int res = 0;
		unsigned char* ptr = (unsigned char*)&key;
		for (int i = 0; i < sizeof(key); i++)
			res += ptr[i];
		return res;
	}
};


template<> class Hash<std::string>
{
public:
	static int get(const std::string& key)
	{
		int res = 0;
		for (int i = 0; i < (int)key.length(); i++)
			res += (unsigned char)key[i];
		return res;
	}
};


template<class KeyType, class DataType, class HashGen = Hash<KeyType>>
class hash_table : table <KeyType, DataType>
{
private:
	int used;
	char* exist;
	void Realloc() override;
	int rhash(const KeyType& key, bool fd) const;
public:
	hash_table(int i_size = MIN_SIZE) : table(i_size) { used = 0; exist = new char[i_size](); }
	~hash_table() { delete[] exist; }
	void Insert(const KeyType& key, const DataType& data) override;
	DataType Find(const KeyType& key) const override;
	void Delete(const KeyType& key) override;
};

template <class KeyType, class DataType, class HashGen>
int hash_table<KeyType, DataType, HashGen>::rhash(const KeyType& key, bool fd) const
{
	std::mt19937 gen;
	int ind, val=HashGen::get(key);
	gen.seed(val);
	if (!fd)
		do
			ind = gen() % MaxSize;
		while (exist[ind] == 1 && mt[ind].key != key);
	else
		do
			ind = gen() % MaxSize;
		while (exist[ind] !=0 && mt[ind].key != key);
	return ind;
}

template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Insert(const KeyType& key, const DataType& data)
{
	if ((double)used / MaxSize > LOADFACTOR_LIMIT)
		Realloc();
	int ind = rhash(key,false);
	if (mt[ind].key != key)
	{
		mt[ind] = row<KeyType, DataType>(key, data);
		exist[ind] = 1;
		used++;
	}
	else
		throw "Duplicate key";
}

template <class KeyType, class DataType, class HashGen>
DataType hash_table<KeyType, DataType, HashGen>::Find(const KeyType& key) const
{
	int ind = rhash(key,true);
	if (exist[ind] == 1)
		return mt[ind].data;
	else
		throw "Data doesn't exist";
	
}
template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Delete(const KeyType& key)
{
	int ind = rhash(key, true);
	if (mt[ind].key == key)
		exist[ind] = -1;
	else
		throw "Data doesn't exist";
}


template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Realloc()
{
	int oldSize = MaxSize;
	MaxSize = (int)((MaxSize + 10)*GROWTHCOEF);
	row <KeyType, DataType>* oldmt = mt;
	char* oldEx = exist;
	exist = new char[MaxSize]();
	mt = new row<KeyType, DataType>[MaxSize];
	for (int i = 0; i < oldSize; i++)
		if (oldEx[i] == 1)
			Insert(oldmt[i].key, oldmt[i].data);
	delete[] oldmt;
	delete[] oldEx;
}
