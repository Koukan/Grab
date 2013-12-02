#pragma once

#include <map>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

template <typename ClonableObject>
struct DefaultClone
{
	static ClonableObject*	addClone(ClonableObject const &obj)
	{
		return obj.clone();
	}

	static ClonableObject*	getClone(ClonableObject const &obj)
	{
		return obj.clone();
	}
};

template <typename Key, typename ClonableObject>
struct DefaultGet
{
	static ClonableObject* get(Key key)
	{
		return nullptr;
	}
};

template <typename Key, typename ClonableObject, typename CloneFunction = DefaultClone<ClonableObject>, typename GetFunction = DefaultGet<Key, ClonableObject> >
class Factory
{
public:
	static void					add(Key key, ClonableObject const &obj)
	{
		_objects[key] = CloneFunction::addClone(obj);
	}

	static ClonableObject		*get(Key key)
	{
		auto it = _objects.find(key);
		//std::cout << _objects.size() << std::endl;
		return (it != _objects.end() ? CloneFunction::getClone(*it->second) : GetFunction::get(key));
	}

	static ClonableObject const	&getReference(Key key)
	{
		return *_objects[key];
	}

protected:
	Factory() {}
	static std::map<Key, ClonableObject*>	_objects;
};

template <typename Key, typename ClonableObject, typename CloneFunction, typename GetFunction>  std::map<Key, ClonableObject*> Factory<Key, ClonableObject, CloneFunction, GetFunction>::_objects;

template <typename ClonableObject, typename CloneFunction = DefaultClone<ClonableObject> >
class UniqueFactory
{
public:
	static void				initFactory(ClonableObject const &object)
	{
		_object = CloneFunction::addClone(object);
	}

	static ClonableObject	*getNew()
	{
		return CloneFunction::getClone(*_object);
	}

	static ClonableObject	&getReference()
	{
		return *_object;
	}

protected:
	static ClonableObject	*_object;
};

template <typename ClonableObject, typename CloneFunction>	ClonableObject*	UniqueFactory<ClonableObject, CloneFunction>::_object = nullptr;

NET_END_NAMESPACE
