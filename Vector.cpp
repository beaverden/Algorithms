#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template <class T>
class Vector
{
public:

	Vector()
	{
		elements = new T[10];
		array_capacity = 10;
		array_size = 0;
	}

	~Vector() {}

	int size() const
	{
		return array_size;
	}
	
	int capacity() const
	{
		return array_capacity;
	}

	/*
		Creates a new dynamic array, copies all the elements from the old one to the new one and removes the old array.
		@param capacity of the new array
	*/
	void resize(int capacity)
	{
		T * newArray = new T[capacity];
		for (int i = 0; i < array_size; i++)
		{
			newArray[i] = this->elements[i];
		}
		this->array_capacity = capacity;
		delete[] this->elements;
		this->elements = newArray;
	}

	/*
		@param the position of the new element
		@param value to be pushed at this position
	*/
	void insert(int position, T val)
	{
		if (array_size == array_capacity)
		{
			resize(array_capacity * 2);
		}
		for (int i = array_size; i > position; i--)
		{
			this->elements[i] = this->elements[i - 1];
		}
		this->elements[position] = val;
		array_size++;
	}

	/*
		@param value to be pushed as the last element
	*/
	void push_back(T val)
	{
		insert(array_size, val);
	}

	/*
		@param position of the element to be removed, has to be in the existing range [0, array_size)
	*/
	void remove(int position)
	{
		if (array_size == 0)
		{
			throw std::out_of_range("Empty array");
		}
		if (position < 0 || position >= array_size)
		{
			throw std::out_of_range("No such index");
		}

		for (int i = position; i < array_size - 1; i++)
		{
			this->elements[i] = this->elements[i + 1];		}
		array_size--;
		if (array_size > 0 && array_size < array_capacity / 4)
		{
			resize(array_capacity / 2);
		}
	}

	/*
		Removes the last element of the array
	*/
	void pop_back()
	{
		remove(array_size - 1);
	}

	/*
		@param const subscript index
		@return the element at the position [index] in the elements array
	*/
	T& operator[](const int index)
	{
		if (index >= array_size || index < 0)
		{
			throw std::out_of_range("No such index");
		}
		
		return this->elements[index];
	}

	T& operator[](const int index) const
	{
		if (index >= array_size || index < 0)
		{
			throw std::out_of_range("No such index");
		}

		return this->elements[index];
	}

	bool empty()
	{
		return (array_size == 0);
	}

	/*
		Clears the vector and re-creates it
	*/
	void clear()
	{
		delete[] elements;
		elements = new T[10];
		array_size = 0;
		array_capacity = 10;
	}

private:
	T * elements;
	int array_size;
	int array_capacity;
};

#endif /* VECTOR_H */