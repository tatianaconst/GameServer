#ifndef SARRAY_CPP
#define SARRAY_CPP

#include <cstddef>
#include <iostream>

using namespace std;

#include "sArray.hpp"
template <typename T>
dynamicArray<T>::dynamicArray(int s)
: size(s), count(0)
{
	p = new T[size];
	if (!p) 
		throw "Array Exeption. Wrong allocation";// TODO
}

template <typename T>
dynamicArray<T>::dynamicArray(const dynamicArray& arr)
{
	size = arr.size;
	count = arr.count;
	p = new T[size];
	for (int i = 0; i < count; ++i) {
		p[i] = arr.p[i];
	}
}

template <typename T>
dynamicArray<T>::~dynamicArray()
{
	if (p)
		delete[] p;
}

template <typename T>
void dynamicArray<T>::addBack(T x)
{
	if (count >= size) {
		dynamicArray temp(*this);
		if (p)
			delete[] p;
		size *= 2;
		p = new T[size];
		for (int i = 0; i < temp.count; ++i)
			p[i] = temp.p[i];
	}
	p[count++] = x;
}

template <typename T>
void dynamicArray<T>::delBack()
{
	if (count) {
		p[--count] = NULL;
	}
}

template <typename T>
int dynamicArray<T>::length() const
{
	return size;
}

template <typename T>
int dynamicArray<T>::asize() const
{
	return count;
}

template <typename T>
T dynamicArray<T>::last() const
{
	if (count) 
		return p[count - 1];
}

template <typename T>
void dynamicArray<T>::clear() 
{
	if (p)
		delete[] p;
}

template <typename T>
void dynamicArray<T>::resize(int s) 
{
	if (s > size) {
		dynamicArray temp(*this);
		if (p)
			delete[] p;
		size = s;
		p = new T[size];
		for (int i = 0; i < temp.count; ++i)
			p[i] = temp.p[i];
	}
}

template <typename T>
void dynamicArray<T>::erase(int index) 
{
	if (index < count) {
		dynamicArray temp(*this);
		if (p)
			delete[] p;
		p = new T[size];
		for (int i = 0; i < index; ++i)
			p[i] = temp.p[i];
		for (int i = index + 1; i < count; ++ i)
			p[i] = temp.p[i];
	}
}

template <typename T> 
dynamicArray<T>& dynamicArray<T>::operator=(const dynamicArray& arr)
{
	if (this != arr) {
		size = arr.size;
		count = arr.count;
		if (p) 
			delete[] p;
		p = new T[size];
		for (int i = 0; i < count; ++i) {
			p[i] = arr.p[i];
		}
	}
	return *this;
}

template <typename T>
T dynamicArray<T>::operator[](int index) const
{
	if (index < count && index >= 0) {
		return p[index];
	}
	else
		throw "Array exeption.Wrong index";
}

template <typename T>
dynamicArray<T>& dynamicArray<T>::operator+(const dynamicArray& arr)
{
	dynamicArray temp(*this);
	if (p)
		delete[] p;
	size += arr.size;
	p = new T[size];
	for (int i = 0; i < temp.count; ++i) {
		p[i] = temp.p[i];
	}
	for (int i = 0; i < arr.count; ++i) {
		p[temp.count + i] = arr.p[i];
	}
	return *this;
}

#endif
