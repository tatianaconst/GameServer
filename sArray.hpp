#ifndef SARRAY_HPP
#define SARRAY_HPP


template <typename T>
class dynamicArray
{
	int size;
	int count;
	T *p;
public:

	dynamicArray(int s = 10);
	dynamicArray(const dynamicArray& arr);
	~dynamicArray();


	void addBack(T x);
	void delBack();
	int length() const;
	int asize() const;
	T last() const;
	void clear();
	void resize(int s);
	void erase(int index);

	dynamicArray& operator=(const dynamicArray& arr);
	T operator [] (int index) const;
	dynamicArray& operator+(const dynamicArray& arr);
};

#endif

