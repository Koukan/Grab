/*
 * GUIManager.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

#include <string>
#include <map>
#include <ClanLib/gui.h>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	template <typename T>
	T		*create(std::string const &name)
	{
	 CL_GUIComponent *res = this->getGUIComponent(name);
	 if (res)
		 delete res;
	  T		*tmp = new T(_parent);
	  _components[name] = tmp;
	  return (tmp);
	}

	CL_GUIComponent							*getGUIComponent(std::string const &name);
	template <typename T>
	T										*getGUIComponent(std::string const &name)
	{
		return dynamic_cast<T*>(this->getGUIComponent(name));
	}

private:
	CL_GUIComponent							*_parent;
	std::map<std::string, CL_GUIComponent*>	_components;
};

#endif /* GUIMANAGER_HPP_ */
