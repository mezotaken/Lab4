#pragma once
#include <cmath>
#define MIN_SIZE 50
#define GROWTHCOEF 1.7

template <class KeyType, class DataType>
struct row
{
	KeyType key;
	DataType data;
	row(const KeyType& i_key, const DataType& i_data) { key = i_key; data = i_data; }
	row() { key = KeyType(); data = DataType(); }
};


template<class KeyType, class DataType>
class table
{
protected:
	row <KeyType, DataType>* mt;
	int MaxSize;
	virtual void Realloc() = 0;
public:
	table(int i_size = MIN_SIZE);
	virtual ~table() { delete[] mt; }
	virtual void Insert(const KeyType& key, const DataType& data) = 0;
	virtual DataType Find(const KeyType& key) const = 0;
	virtual void Delete(const KeyType& key) = 0;
};


template <class KeyType, class DataType>
table<KeyType, DataType>::table(int i_size)
{
	MaxSize = i_size;
	mt = new row<KeyType, DataType>[MaxSize];
}
