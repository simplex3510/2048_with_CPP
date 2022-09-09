#pragma once

#include <iostream>

//************
// 추상 클래스
//************
template <typename T>
class SingletonBase abstract
{
public:
	SingletonBase<T>();

	static T* getInstance();
	static void delInstance();

private:
	static T* mInstance;
};


template<typename T>
T* SingletonBase<T>::mInstance;

//************
// 함수 구현부
//************

template<typename T>
inline SingletonBase<T>::SingletonBase()
{
	
}

template<typename T>
T* SingletonBase<T>::getInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new T();
	}

	return mInstance;
}

template<typename T>
inline void SingletonBase<T>::delInstance()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}