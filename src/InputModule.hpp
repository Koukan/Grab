#ifndef _INPUTMODULE_
#define _INPUTMODULE_

#include <map>
#include <list>
#include <ClanLib/core.h>
#include "Module.hpp"

class InputModule : public Module
{
public:
	InputModule();
	virtual ~InputModule();

	virtual void	init();
	virtual void 	update(double elapsedTime);
	virtual void	destroy();

private:
	void			treatInput(const CL_InputEvent &event, const CL_InputState &state);
};


#endif /* _INPUTMODULE_ */
