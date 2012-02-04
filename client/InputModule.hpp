#ifndef _INPUTMODULE_
#define _INPUTMODULE_

//#include <ClanLib/core.h>
#include "Module.hpp"
#include "Input.hpp"

class InputModule : public Module
{
public:
	InputModule();
	virtual ~InputModule();

	virtual void	init();
	virtual void 	update(double elapsedTime);
	virtual void	destroy();

private:
	void			translateFromSFML1_6(InputCommand &cmd) const;
	//void			treatInput(const CL_InputEvent &event, const CL_InputState &state);

#if (SFML_VERSION_MAJOR != 2)
	std::map<sf::Key::Code, Keyboard::Key> _dict;
#endif
};


#endif /* _INPUTMODULE_ */
