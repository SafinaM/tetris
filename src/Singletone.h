#pragma once
#include <memory>

// https://codereview.stackexchange.com/questions/173929/modern-c-singleton-template
template<typename T>
class Singleton {
public:
	static T& instance();
	
	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;

protected:
	struct token {};
	Singleton() {}
};

template<typename T>
T& Singleton<T>::instance()
{
	static const std::unique_ptr<T> instance{new T{token{}}};
	return *instance;
}