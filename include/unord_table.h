#pragma once
#include "table.h"


template<class KeyType, class DataType>
class unord_table : table <KeyType, DataType>
{
private:
	void Realloc() override;
	int CurSize;
public:
	unord_table(int i_size = MIN_SIZE) : table(i_size) {CurSize = 0;}
	~unord_table() {}
	void Insert(const KeyType& key, const DataType& data) override;
	DataType Find(const KeyType& key) const override;
	void Delete(const KeyType& key) override;
};

template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Realloc()
{
	int nSize = (int)((MaxSize + 10)*GROWTHCOEF);
	row <KeyType, DataType>* temp = new row<KeyType, DataType>[nSize];
	for (int i = 0; i < CurSize; i++)
		temp[i] = mt[i];
	delete mt;
	mt = temp;
	MaxSize = nSize;
}

template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Insert(const KeyType& key, const DataType& data)
{
	if (CurSize == MaxSize)
		Realloc();
	mt[CurSize] = row<KeyType,DataType>(key, data);
	CurSize++;
	//Исключение при вставке строки с ключом-дубликатом? O(1) -> O(n)
}

template <class KeyType, class DataType>
DataType unord_table<KeyType, DataType>::Find(const KeyType& key) const
{
	int i = 0;
	while (mt[i].key != key && i<CurSize)
		i++;
	if (i < CurSize)
		return mt[i].data;
	else
		throw "Data doesn't exist";
}

template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Delete(const KeyType& key)
{
	int i = 0;
	while (mt[i].key != key && i<CurSize)
		i++;
	if (i < CurSize)
		if (CurSize > 1)
			mt[i] = mt[--CurSize];
		else
			CurSize = 0;
	else
		throw "Data doesn't exist";
}
