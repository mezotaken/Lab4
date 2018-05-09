﻿#pragma once
#include <cmath>
#include <iostream>
#define MIN_SIZE 50
#define GROWTHCOEF 1.7

template <class KeyType, class DataType>
struct row
{
	KeyType key;
	DataType* data;
	row(const KeyType& i_key, const DataType& i_data) { key = i_key; data = new DataType(i_data); }
	row() { key = KeyType(); data = nullptr; }
	row(const row& src) { key = src.key; data = new DataType(*(src.data)); }
	row& operator=(const row& src) { key = src.key; delete data; data = new DataType(*(src.data));  return *this; }
	~row() { delete data; }
};


template<class KeyType, class DataType>
class table
{
protected:
	row <KeyType, DataType>* mt;
	int MaxSize;
	int CurSize;
	virtual void Realloc() = 0;
	int Curr;
public:
	table(int i_size = MIN_SIZE);
	virtual ~table() { delete[] mt; }

	virtual void Insert(const KeyType& key, const DataType& data) = 0;
	virtual DataType Find(const KeyType& key) const = 0;
	virtual void Delete(const KeyType& key) = 0;

	virtual void Reset() = 0;
	virtual bool IsEnded() = 0; 
	virtual void Move() = 0;
	virtual row<KeyType, DataType> GetCurr() const = 0;
	int GetCurSize() const { return CurSize; }
	int GetMaxSize() const { return MaxSize; }
	bool IsEmpty() const { return CurSize == 0; }
	
};


template <class KeyType, class DataType>
table<KeyType, DataType>::table(int i_size)
{
	CurSize = 0;
	MaxSize = i_size;
	mt = new row<KeyType, DataType>[MaxSize];
}
