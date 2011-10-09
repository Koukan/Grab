#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_

#include <map>
#include <list>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

struct	CallbackElem
{
  public:
	CL_InputEvent::Type eventType;
	CL_Callback_v1<const CL_InputEvent &>  callback;
	CL_InputDevice::Type inputType;
	int key;
};

typedef std::map<CL_InputEvent::Type, std::list<CallbackElem*> > InputMap;

class InputManager 
{
public:
	InputManager();
	~InputManager();
    void		handleInput(const CL_InputEvent &event, const CL_InputState &state);
    void		registerInputCallback(CL_InputEvent::Type eventType, 
		    	CL_Callback_v1<const CL_InputEvent &>  callback,
			CL_InputDevice::Type inputType = CL_InputDevice::unknown, int key = -1);
	void		unmapInput(CL_InputEvent::Type eventType, CL_InputDevice::Type inputType = CL_InputDevice::unknown, int key = -1);
	void		flushCallbacks();

private:
	InputMap _inputCallbacks;
};


#endif /* _INPUTMANAGER_ */
