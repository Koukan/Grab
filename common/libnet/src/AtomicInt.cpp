#if defined (_WIN32) && _MSC_VER < 1700
#include <windows.h>
#include <intrin.h>
#include "AtomicInt.hpp"

#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedExchange)

NET_BEGIN_NAMESPACE

AtomicChar::AtomicChar(char value) : _value(value)
{
}

AtomicChar::AtomicChar(AtomicChar const &other) : _value(other._value)
{
}

AtomicChar		&AtomicChar::operator=(AtomicChar const &other)
{
	_value = other._value;
	return *this;
}

char	AtomicChar::operator+(char value) const
{
	return (_value + value);
}

char	AtomicChar::operator-(char value) const
{
	return (_value - value);
}

char	AtomicChar::operator|(int value) const
{
	return (_value | value);
}

char	AtomicChar::operator&(int value) const
{
	return (_value & value);
}

char	AtomicChar::operator|=(char value)
{
	return _InterlockedOr8(&_value, value);
}

char	AtomicChar::operator&=(char value)
{
	return _InterlockedAnd8(&_value, value);
}

char	AtomicChar::operator=(char value)
{
	return _value = value;
}

bool	AtomicChar::operator==(char value) const
{
	return _value == value;
}

bool	AtomicChar::operator!=(char value) const
{
	return !(_value == value);
}

AtomicChar::operator char() const
{
	return _value;
}

AtomicInt::AtomicInt(int value) : _value(value)
{
}

AtomicInt::AtomicInt(AtomicInt const &other) : _value(other._value)
{
}

AtomicInt	&AtomicInt::operator=(AtomicInt const &other)
{
	InterlockedExchange(&_value, other._value);
	return *this;
}

int AtomicInt::operator+(int value) const
{
	return (_value + value);
}

int	AtomicInt::operator++(int)
{
	return InterlockedIncrement(&_value);
}

int	AtomicInt::operator--(int)
{
	return InterlockedDecrement(&_value);
}

int AtomicInt::operator-(int value) const
{
	return (_value - value);
}

int AtomicInt::operator|(int value) const
{
	return (_value | value);
}

int AtomicInt::operator&(int value) const
{
	return (_value & value);
}

int AtomicInt::operator+=(int value)
{
	return InterlockedExchangeAdd(&_value, value);
}

int AtomicInt::operator-=(int value)
{
	return InterlockedExchangeAdd(&_value, -value);
}

int AtomicInt::operator|=(int value)
{
	return _InterlockedOr(&_value, value);
}

int AtomicInt::operator&=(int value)
{
	return _InterlockedAnd(&_value, value);
}

int AtomicInt::operator=(int value)
{
	return InterlockedExchange(&_value, value);
}

bool AtomicInt::operator==(int value) const
{
	return _value == value;	
}

bool AtomicInt::operator!=(int value) const
{
	return !(_value == value);	
}

AtomicInt::operator int() const
{
	return _value;
}

NET_END_NAMESPACE
#endif