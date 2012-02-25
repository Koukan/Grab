#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_

#include <map>
#include <list>
#include "Callback.hpp"
#include "Input.hpp"
#include "CommandHandler.hpp"

CORE_BEGIN_NAMESPACE

class GameState;

class CORE_DLLREQ InputManager : public CommandHandler
{
public:
	InputManager(GameState &game);
	~InputManager();

	void	handleInput(const InputCommand &event);
	void	flushInput();
	virtual bool	handleCommand(Command const &cmd);

	template <typename T>
	void        registerInputCallback(InputCommand::EventType eventType, T &instance,
				   	void (T::*method)(const InputCommand &event), int key = -1, int joystickId = -1);

private:
	struct	CallbackElem
	{
		Callback		*callback;
		int				key;
		int				joystickId;
	};

	typedef std::map<InputCommand::EventType, std::list<CallbackElem*> > InputMap;
	
	GameState	&_gs;
	bool		_flush;
	InputMap  	_inputCallbacks;
};

template <typename T>
void		InputManager::registerInputCallback(InputCommand::EventType eventType,
		T &instance, void (T::*method)(const InputCommand &event), int key, int joystickId)
{
  if (!method)
    return ;
  CallbackElem	*tmp = new CallbackElem();
  tmp->callback = new Callback(instance, method);
  tmp->key = key;
  tmp->joystickId = joystickId;
  _inputCallbacks[eventType].push_back(tmp);
}

CORE_END_NAMESPACE

#endif /* _INPUTMANAGER_ */
