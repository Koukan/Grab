#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_

#include <map>
#include <list>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include "Callback.hpp"

class InputManager
{
public:
	InputManager();
	~InputManager();
    void		handleInput(const CL_InputEvent &event, const CL_InputState &state);
    template <typename T>
    void		registerInputCallback(CL_InputEvent::Type eventType,
		    	T &instance, void (T::*method)(const CL_InputEvent &event),
			CL_InputDevice::Type inputType = CL_InputDevice::unknown, int key = -1);
	void		unmapInput(CL_InputEvent::Type eventType, CL_InputDevice::Type inputType = CL_InputDevice::unknown, int key = -1);
	void		flushInput();

private:

	struct	CallbackElem
	{
 	 public:
		CL_InputEvent::Type	eventType;
		Callback		*callback;
		CL_InputDevice::Type	inputType;
		int			key;
	};

	typedef std::map<CL_InputEvent::Type, std::list<CallbackElem*> > InputMap;


	bool		_flush;
	InputMap	_inputCallbacks;
};

#include "InputManager.ipp"

#endif /* _INPUTMANAGER_ */
