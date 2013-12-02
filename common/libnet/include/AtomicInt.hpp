#pragma once

#include "NetDef.hpp"

#if defined (_WIN32) && _MSC_VER < 1700
NET_BEGIN_NAMESPACE

class NET_DLLREQ AtomicChar
{
public:
	AtomicChar(char value = 0);
	AtomicChar(AtomicChar const &other);
	AtomicChar	&operator=(AtomicChar const &other);
	char		operator+(char value) const;
	char		operator-(char value) const;
	char		operator|(int value) const;
	char		operator&(int value) const;
	char		operator|=(char value);
	char		operator&=(char value);
	char		operator=(char value);
	bool		operator==(char value) const;
	bool		operator!=(char value) const;
	operator	char() const;

private:
	char		_value;
};

class NET_DLLREQ AtomicInt
{
public:
	AtomicInt(int value = 0);
	AtomicInt(AtomicInt const &other);
	AtomicInt &operator=(AtomicInt const &other);

	int			operator+(int value) const;
	int			operator++(int);
	int			operator--(int);
	int			operator-(int value) const;
	int			operator|(int value) const;
	int			operator&(int value) const;
	int			operator+=(int value);
	int			operator-=(int value);
	int			operator|=(int value);
	int			operator&=(int value);
	int			operator=(int value);
	bool		operator==(int value) const;
	bool		operator!=(int value) const;
	operator	int() const;

private:
	LONG		_value;
};
#else
#include <atomic>
typedef std::atomic_int AtomInt;
typedef std::atomic_char AtomChar;
NET_BEGIN_NAMESPACE
	typedef AtomInt AtomicInt;
	typedef AtomChar AtomicChar;
#endif

NET_END_NAMESPACE
