#ifndef _MODULE_
#define _MODULE_

#include <string>

class ModuleManager;

class Module
{
public:
	Module(std::string const &name, double targetRate = 0);
	virtual ~Module();
	virtual	void init() = 0;
	virtual void update(double elapsedTime = 0) = 0;
	virtual void resume();
	virtual void pause();
	virtual void destroy() = 0;
	bool	isPaused() const;
	double	getTargetRate() const;
	std::string const	&getName() const;

protected:
	double          _targetRate;
	double			_lastUpdate;
	bool			_paused;
	friend class	ModuleManager;

private:
	std::string		_name;
};


#endif /* _MODULE_ */
