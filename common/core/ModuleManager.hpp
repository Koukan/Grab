#ifndef _MODULEMANAGER_
#define _MODULEMANAGER_

#include <map>
#include <string>
#include "Module.hpp"
//#include "SharedLoader.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ ModuleManager : public Module
{
public:
	ModuleManager();
	virtual ~ModuleManager();
	void		init();
	void		update(double);
	void		destroy();

	void			loadModule(Module &module);
	void			loadModule(std::string const &path, double rate);
	void			unloadModule(std::string const &name);
	Module			*getModuleByName(std::string const &name) const;

private:
	void			load(std::string const &path, int rate);

//	SharedLoader						_loader;
	std::map<std::string, Module *>		_modules;
	bool								_stop;
};

CORE_END_NAMESPACE

#endif /* _MODULEMANAGER_ */
