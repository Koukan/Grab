#pragma once

#include <functional>
#include <type_traits>
#include "NetDef.hpp"
#include "PoolObject.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ Task : public Net::PoolObject
{
public:
	Task(){}
	virtual ~Task(){}
	virtual void	operator()() = 0;
};

class NET_DLLREQ FunctionTask : public Task
{
public:
	FunctionTask(std::function<void ()> function)
		: _function(function)
	{
	}

	template <typename T>
	FunctionTask(T &instance, void (T::*method)())
		: _function(std::bind(method, &instance))
	{
	}

	// One Arg
	template <typename T, typename A>
	FunctionTask(T &instance, void (T::*method)(A), A a)
		: _function(std::bind(method, &instance, a))
	{
	}

	template <typename T, typename A>
	FunctionTask(T &instance, void (T::*method)(A&), A &a)
		: _function(std::bind(method, &instance, std::ref(a)))
	{
	}

	/*template <typename T, typename A>
	FunctionTask(T &instance, void (T::*method)(A const &), A const &a)
		: _function(std::bind(method, &instance, std::cref(a)))
	{
	}*/

	// Two Args
	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A, B), A a, B b)
		: _function(std::bind(method, &instance, a, b))
	{
	}

	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A&, B), A &a, B b)
		: _function(std::bind(method, &instance, std::ref(a), b))
	{
	}

	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A, B&), A a, B &b)
		: _function(std::bind(method, &instance, a, std::ref(b)))
	{
	}

	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A&, B&), A &a, B &b)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b)))
	{
	}

	// Const Reference
	/*template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A const &, B), A const &a, B b)
		: _function(std::bind(method, &instance, std::cref(a), b))
	{
	}

	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A, B const &), A a, B const &b)
		: _function(std::bind(method, &instance, a, std::cref(b)))
	{
	}

	template <typename T, typename A, typename B>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &), A const &a, B const &b)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b)))
	{
	}*/


	// Three args
	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B, C), A a, B b, C c)
		: _function(std::bind(method, &instance, a, b, c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A&, B, C), A &a, B b, C c)
		: _function(std::bind(method, &instance, std::ref(a), b, c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B&, C), A a, B &b, C c)
		: _function(std::bind(method, &instance, a, std::ref(b), c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B, C&), A a, B b, C &c)
		: _function(std::bind(method, &instance, a, b, std::ref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C), A &a, B &b, C c)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A&, B, C&), A &a, B b, C &c)
		: _function(std::bind(method, &instance, std::ref(a), b, std::ref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B&, C&), A a, B &b, C &c)
		: _function(std::bind(method, &instance, a, std::ref(b), std::ref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C&), A &a, B &b, C &c)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), std::ref(c)))
	{
	}

	// Const Reference
	/*template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C), A const &a, B b, C c)
		: _function(std::bind(method, &instance, std::cref(a), b, c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C), A a, B const &b, C c)
		: _function(std::bind(method, &instance, a, std::cref(b), c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B, C const &), A a, B b, C const &c)
		: _function(std::bind(method, &instance, a, b, std::cref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C), A const &a, B const &b, C c)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), c))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C const &), A const &a, B b, C const &c)
		: _function(std::bind(method, &instance, std::cref(a), b, std::cref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C const &), A a, B const &b, C const &c)
		: _function(std::bind(method, &instance, a, std::cref(b), std::cref(c)))
	{
	}

	template <typename T, typename A, typename B, typename C>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C const &), A const &a, B const &b, C const &c)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), std::cref(c)))
	{
	}*/

	// Four args
	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C, D), A a, B b, C c, D d)
		: _function(std::bind(method, &instance, a, b, c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B, C, D), A &a, B b, C c, D d)
		: _function(std::bind(method, &instance, std::ref(a), b, c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B&, C, D), A a, B &b, C c, D d)
		: _function(std::bind(method, &instance, a, std::ref(b), c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C&, D), A a, B b, C &c, D d)
		: _function(std::bind(method, &instance, a, b, std::ref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C, D&), A a, B b, C c, D &d)
		: _function(std::bind(method, &instance, a, b, c, std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C, D), A &a, B &b, C c, D d)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B, C&, D), A &a, B b, C &c, D d)
		: _function(std::bind(method, &instance, std::ref(a), b, std::ref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B, C, D&), A &a, B b, C c, D &d)
		: _function(std::bind(method, &instance, std::ref(a), b, c, std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B&, C&, D), A a, B &b, C &c, D d)
		: _function(std::bind(method, &instance, a, std::ref(b), std::ref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B&, C, D&), A a, B &b, C c, D &d)
		: _function(std::bind(method, &instance, a, std::ref(b), c, std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C&, D&), A a, B b, C &c, D &d)
		: _function(std::bind(method, &instance, a, b, std::ref(c), std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C&, D), A &a, B &b, C &c, D d)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), std::ref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C, D&), A &a, B &b, C c, D &d)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), c, std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B&, C&, D&), A a, B &b, C &c, D &d)
		: _function(std::bind(method, &instance, a, std::ref(b), std::ref(c), std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B, C&, D&), A &a, B b, C &c, D &d)
		: _function(std::bind(method, &instance, std::ref(a), b, std::ref(c), std::ref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A&, B&, C&, D&), A &a, B &b, C &c, D &d)
		: _function(std::bind(method, &instance, std::ref(a), std::ref(b), std::ref(c), std::ref(d)))
	{
	}

	// Const Reference
	/*template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C, D), A const &a, B b, C c, D d)
		: _function(std::bind(method, &instance, std::cref(a), b, c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C, D), A a, B const &b, C c, D d)
		: _function(std::bind(method, &instance, a, std::cref(b), c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C const &, D), A a, B b, C const &c, D d)
		: _function(std::bind(method, &instance, a, b, std::cref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C, D const &), A a, B b, C c, D const &d)
		: _function(std::bind(method, &instance, a, b, c, std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C, D), A const &a, B const &b, C c, D d)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), c, d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C const &, D), A const &a, B b, C const &c, D d)
		: _function(std::bind(method, &instance, std::cref(a), b, std::cref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C, D const &), A const &a, B b, C c, D const &d)
		: _function(std::bind(method, &instance, std::cref(a), b, c, std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C const &, D), A a, B const &b, C const &c, D d)
		: _function(std::bind(method, &instance, a, std::cref(b), std::cref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C, D const &), A a, B const &b, C c, D const &d)
		: _function(std::bind(method, &instance, a, std::cref(b), c, std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B, C const &, D const &), A a, B b, C const &c, D const &d)
		: _function(std::bind(method, &instance, a, b, std::cref(c), std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C const &, D), A const &a, B const &b, C const &c, D d)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), std::cref(c), d))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C, D const &), A const &a, B const &b, C c, D const &d)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), c, std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A, B const &, C const &, D const &), A a, B const &b, C const &c, D const &d)
		: _function(std::bind(method, &instance, a, std::cref(b), std::cref(c), std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B, C const &, D const &), A const &a, B b, C const &c, D const &d)
		: _function(std::bind(method, &instance, std::cref(a), b, std::cref(c), std::cref(d)))
	{
	}

	template <typename T, typename A, typename B, typename C, typename D>
	FunctionTask(T &instance, void (T::*method)(A const &, B const &, C const &, D const &), A const &a, B const &b, C const &c, D const &d)
		: _function(std::bind(method, &instance, std::cref(a), std::cref(b), std::cref(c), std::cref(d)))
	{
	}*/

	virtual ~FunctionTask()
	{
	}

	void			operator()() override
	{
		_function();
	}

private:
	std::function<void ()>	_function;
};

NET_END_NAMESPACE
