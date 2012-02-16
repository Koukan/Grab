#ifndef _INPUTMODULE_
#define _INPUTMODULE_

//#include <ClanLib/core.h>
#include "Module.hpp"
#include "Input.hpp"

class InputModule : public Core::Module
{
public:
	InputModule();
	virtual ~InputModule();

	virtual void	init();
	virtual void 	update(double elapsedTime);
	virtual void	destroy();

private:

#if (SFML_VERSION_MAJOR != 2)
	std::map<sf::Key::Code, Core::Keyboard::Key> _dict;
#endif
};


#endif /* _INPUTMODULE_ */
