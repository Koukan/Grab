#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <exception>
#include "ModuleManager.hpp"
#include "Clock.hpp"

CORE_USE_NAMESPACE

ModuleManager::ModuleManager() : Module("ModuleManager"), _stop(false)
{
}

ModuleManager::~ModuleManager()
{
}

void	ModuleManager::init()
{
  std::ifstream        		file("./config/modules");
  std::string				line;
  //std::auto_ptr<std::vector<std::string> > tab;

 /* while (file.good())
  {
    getline(file, line, '\n');
    tab = Converter::explode(line, ' ');
    if (tab->size() == 3)
      this->load((*tab)[0], (*tab)[1], Converter::toInt<double>((*tab)[2]));
  }*/
  file.close();
}

void    ModuleManager::loadModule(Module &module)
{
  _modules[module.getName()] = &module;
  module._lastUpdate = module.getTargetRate();
  module.init();
}

void    ModuleManager::loadModule(std::string const &, double )
{
  //Module *tmp = _loader.load<Module*>(path, "export_instance");
  //if (tmp)
  //{
  //  tmp->_targetRate = rate;
  //  this->loadModule(*tmp);
  //}
}

void    ModuleManager::unloadModule(std::string const &name)
{
  std::map<std::string, Module*>::iterator it = _modules.find(name);

  if (it != _modules.end())
  {
    (*it).second->destroy();
    delete (*it).second;
    _modules.erase(it);
  }
}

void    ModuleManager::update(double)
{
  Net::Clock		clock;
  double	towait;
  double	diff;
  Module	*module;

  while (!_stop)
  {
    towait = -1;
    diff = static_cast<double>(clock.getElapsedTime());
    clock.update();
    for (std::map<std::string, Module*>::iterator it = _modules.begin();
		    it != _modules.end();)
    {
	  module = (*it).second;
	  ++it;
      if (!module->isPaused() && module->_targetRate > 0)
		{
		  	module->_lastUpdate -= diff;
       	 	if (module->_lastUpdate <= 0)
	  		{
				int n = static_cast<int>(-1 * module->_lastUpdate / module->_targetRate + 1);
				double tmpUpdate = module->_lastUpdate;
				module->_lastUpdate += n * module->_targetRate;
				module->update(module->_lastUpdate - tmpUpdate);
				if (_stop)
					break ;
				if (module->isStopped())
				{
					this->unloadModule(module->_name);
					continue ;
				}
 	  		}
	  		if (towait == -1 || module->_lastUpdate < towait)
	    		towait = module->_lastUpdate;
		}
    }
	Net::Clock::sleep((towait < 0) ? 10 : static_cast<int>(towait));
  }
  for (std::map<std::string, Module*>::iterator it = _modules.begin(); it != _modules.end(); ++it)
  {
    (*it).second->destroy();
    delete (*it).second;
  }
}

void    ModuleManager::destroy()
{
   _stop = true;
}

Module  *ModuleManager::getModuleByName(std::string const &name) const
{
  std::map<std::string, Module*>::const_iterator it = _modules.find(name);

  return ((it == _modules.end()) ? 0 : (*it).second);
}
