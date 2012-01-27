#ifndef _MODULE_
#define _MODULE_

#include <string>
#include "CommandHandler.hpp"

class ModuleManager;

class Module : public CommandHandler
{
public:
	Module(std::string const &name, double targetRate = 0);
	virtual ~Module();
	virtual	void		init() = 0;
	virtual void		update(double elapsedTime = 0) = 0;
	virtual void		resume();
	virtual void		pause();
	virtual void		destroy() = 0;
	void				stop();
	bool				isPaused() const;
	double				getTargetRate() const;
	std::string const	&getName() const;
	bool				isStopped() const;

protected:
	double				_targetRate;
	double				_lastUpdate;
	bool				_paused;

private:
	std::string			_name;
	bool				_stop;
	friend class		ModuleManager;
};


#endif /* _MODULE_ */
