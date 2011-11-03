/*
 * GUIManager.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "RendererManager.hpp"
#include "GUIManager.hpp"

GUIManager::GUIManager() : _parent(RendererManager::get().getMainWindow())
{

}

GUIManager::~GUIManager()
{
  for (std::map<std::string, CL_GUIComponent*>::iterator it = _components.begin(); it != _components.end(); ++it)
   {
	  delete (*it).second;
   }
}

CL_GUIComponent							*GUIManager::getGUIComponent(std::string const &name)
{
	std::map<std::string, CL_GUIComponent*>::const_iterator it = _components.find(name);
	return ((it != _components.end()) ? (*it).second : 0);
}

