#pragma once

#include <iostream>
#include <cassert>
#include <ostream>
#include <string>
#include <cstring>

constexpr int DEFAULT_CAPACITY = 16;
constexpr int INCREASE_COEF = 2;

template<typename Array>
class ArrayIterator
{
public:
	using ValueType = typename Array::Type;

	ArrayIterator(ValueType* ptr, ValueType* end, bool reversed = false) : ptr_(ptr), end_(end), reversed_(reversed)
	{
		//std::cout << "Iterator ctor called\n";
	}

	const ValueType& get() const;
	void set(const ValueType& value);
	void next();
	bool hasNext() const;

private:
	ValueType* ptr_;
	ValueType* end_;
	bool reversed_;
};

template<typename Array>
class ConstArrayIterator
{
public:
	using ValueType = typename Array::Type;

	ConstArrayIterator(ValueType* ptr, ValueType* end, bool reversed = false) : ptr_(ptr), end_(end), reversed_(reversed)
	{
		//std::cout << "cIterator ctor called\n";
	}

	const ValueType& get() const;
	void next();
	bool hasNext() const;

private:
	ValueType* ptr_;
	ValueType* end_;
	bool reversed_;
};

template <typename T>
class Array final
{
public:
	using Type = T;
	using Iterator = ArrayIterator<Array>;
	using ConstIterator = ConstArrayIterator<Array>;

	Array();
	Array(int capacity);
	Array(const Array& lval);
	Array(Array&& rval) noexcept;
	~Array();

	int push_back(const T& value);
	int insert(int index, const T& value);

	void remove(int index);

	const T& operator[](int index) const;
	T& operator[](int index);

	Array& operator=(const Array& lval);
	Array& operator=(Array&& rval) noexcept;

	int size() const;
	int capacity() const;

	Iterator iterator();
	Iterator reverseIterator();

	ConstIterator cIterator() const;
	ConstIterator cReverseIterator() const;

private:
	void clear();
	// TO DO
	void ensureCapacity();

private:
	int capacity_;
	int size_;
	T* data_;
};

template<typename T>
inline Array<T>::Array()
{
	capacity_ = DEFAULT_CAPACITY;
	size_ = 0;
	data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
	//std::cout << "default ctor called\n";
}

template<typename T>
Array<T>::Array(int capacity)
{
	capacity_ = capacity > 0 ? capacity : DEFAULT_CAPACITY;
	size_ = 0;
	data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
	//std::cout << "size ctor called\n";
}

template<typename T>
Array<T>::Array(const Array& lval) //: Array(lval.capacity_)
{
	capacity_ = lval.capacity_ > 0 ? lval.capacity_ : DEFAULT_CAPACITY;
	size_ = lval.size_;
	data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
	for (int i = 0; i < size_; i++) {
		new (data_ + i) T(lval.data_[i]);
	}
	//std::cout << "copy ctor called\n";
}

template<typename T>
Array<T>::Array(Array&& rval) noexcept
{
	data_ = rval.data_;
	capacity_ = rval.capacity_;
	size_ = rval.size_;
	rval.data_ = nullptr;
	rval.capacity_ = 0;
	rval.size_ = 0;
	//std::cout << "move ctor called\n";
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& lval)
{
	if (this != &lval)
	{
		clear();
		free(data_);
		
		capacity_ = lval.capacity_;
		size_ = lval.size_;
		data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));

		for (int i = 0; i < size_; i++)
		{
			new (data_ + i) T(lval.data_[i]);
		}
	}
	//std::cout << "copy assignment called\n";
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& rval) noexcept
{
	if (this != &rval)
	{
		clear();
		free(data_);

		capacity_ = rval.capacity_;
		size_ = rval.size_;
		data_ = rval.data_;

		rval.capacity_ = 0;
		rval.size_ = 0;
		rval.data_ = nullptr;
	}
	//std::cout << "move assignment called\n";
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	//std::cout << "dtor called\n";
	clear();
	if (data_) free(data_);
}

template <typename T>
void Array<T>::clear() {
	for (int i = 0; i < size_; ++i)
	{
		(data_ + i)->~T();
	}
}

template<typename T>
int Array<T>::push_back(const T& value)
{
	//TO DO : ensureCapactiry()
	if (size_ >= capacity_)
	{
		capacity_ = capacity_ * INCREASE_COEF;
		T* newData = static_cast<T*>(malloc(sizeof(T) * capacity_));

		// ask QUESTION: is this cicle needed here
		// ask QUESTION: what about move assignment
		for (int i = 0; i < size(); i++)
		{
			new (newData + i) T(std::move(data_[i]));
			(data_ + i)->~T();
		}
		free(data_);
		data_ = /*std::move*/newData;
	}
	new (data_ + size_) T(value);
	return size_++;
}

template<typename T>
int Array<T>::insert(int index, const T& value)
{
	if (index >= size_ || index < 0) return push_back(value);

	if (size_ == capacity_)
	{
		capacity_ = capacity_ * INCREASE_COEF;
		T* newData = static_cast<T*>(malloc(sizeof(T) * capacity_));

		for (int i = 0; i < index; i++)
		{
			new (newData + i) T(std::move(data_[i]));
			(data_ + i)->~T();
		}
		new (newData + index) T(value);

		for (int i = index + 1; i < size(); i++)
		{
			new (newData + i) T(std::move(data_[i]));
			(data_ + i)->~T();
		}

		free(data_);
		data_ = /*std::move*/newData;
	}
	else
	{
		for (int i = size() - 1; i >= index; i--)
		{
			new (data_ + i + 1) T(std::move(data_[i]));
			(data_ + i)->~T();
		}
		new (data_ + index) T(value);
	}
	return size_++;
}

template<typename T>
void Array<T>::remove(int index)
{
	if (index >= size_ || index < 0) return;

	(data_ + index)->~T();

	for (int i = index; i < size() - 1; i++)
	{
		new (data_ + i) T(std::move(data_[i + 1]));
		(data_ + i + 1)->~T();
	}
	size_--;
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	return data_[index];
}

template<typename T>
T& Array<T>::operator[](int index)
{
	return data_[index];
}

template<typename T>
int Array<T>::size() const
{
	return size_;
}

template<typename T>
int Array<T>::capacity() const
{
	return capacity_;
}

template<typename T>
void Array<T>::ensureCapacity() 
{
	
}

// Iterator stuff //////////////////////////////
template<typename T>
typename Array<T>::Iterator Array<T>::iterator()
{	
	return Iterator(data_, data_ + size_);
}

template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator()
{
	return Iterator(data_ + size_ - 1, data_ - 1, true);
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::cIterator() const
{
	return ConstIterator(data_, data_ + size_);
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::cReverseIterator() const
{
	return ConstIterator(data_ + size_ - 1, data_ - 1, true);
}

template<typename Array>
const typename ArrayIterator<Array>::ValueType& ArrayIterator<Array>::get() const
{
	return *ptr_;
}

template<typename Array>
void ArrayIterator<Array>::set(const ValueType& value)
{
	*ptr_ = value;
}

template<typename Array>
void ArrayIterator<Array>::next()
{
	reversed_ ? --ptr_ : ++ptr_;
}

template<typename Array>
bool ArrayIterator<Array>::hasNext() const
{
	return (ptr_ != end_);
}

template<typename Array>
const typename ConstArrayIterator<Array>::ValueType& ConstArrayIterator<Array>::get() const
{
	return *ptr_;
}

template<typename Array>
void ConstArrayIterator<Array>::next()
{
	reversed_ ? --ptr_ : ++ptr_;
}

template<typename Array>
bool ConstArrayIterator<Array>::hasNext() const
{
	return (ptr_ != end_);
}

//template <typename T>
//std::ostream& operator<<(std::ostream& s, const Array<T>& arr)
//{
//	for (int i = 0; i < arr.size(); i++)
//	{
//		s << arr[i] << " ";
//	}
//	return s;
//}