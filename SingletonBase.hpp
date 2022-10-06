#pragma once

// ***********
// �߻� Ŭ����
// ***********

template <typename T>
class SingletonBase abstract
{
public:
	static T* getInstance();
	static void delInstance();

protected:
	SingletonBase();
	~SingletonBase();

private:
	static T* instance;
};


// ***********
// �Լ� ������
// ***********

template <typename T>
T* SingletonBase<T>::instance = nullptr;

template <typename T>
SingletonBase<T>::SingletonBase() { }

template<typename T>
SingletonBase<T>::~SingletonBase() { instance = nullptr; }

template <typename T>
T* SingletonBase<T>::getInstance()
{
	if (instance == nullptr)
	{
		instance = new T();
	}

	return instance;
}

template<typename T>
inline void SingletonBase<T>::delInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
