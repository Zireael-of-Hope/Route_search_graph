#pragma once
#include <vector>
using namespace std;

template<class T>
class Queue
{
	vector<T> queue_array;

public:

	Queue() {}
	~Queue() {}

	void push(T value);
	T pop();
	T pop_back();
	bool empty();
	int size();
	T front();
};

template<class T>
inline void Queue<T>::push(T value)
{
	queue_array.push_back(value);
}

template<class T>
inline T Queue<T>::pop()
{
	T el;
	el = queue_array.front();
	queue_array.erase(queue_array.begin());
	return el;
}

template<class T>
inline T Queue<T>::pop_back()
{
	queue_array.pop_back();
	return T();
}

template<class T>
inline bool Queue<T>::empty()
{
	if (queue_array.empty())
		return true;
	else
		return false;
}

template<class T>
inline int Queue<T>::size()
{
	return queue_array.size();
}

template<class T>
inline T Queue<T>::front()
{
	return queue_array.front();
}


