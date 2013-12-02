#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_

#include <map>
#include <list>
#include <functional>
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
		CallbackElem(std::function<void (const InputCommand &event)> callback, int key, int joystickId) :
				callback(callback), key(key), joystickId(joystickId)
		{}
		std::function<void (const InputCommand &event)> callback;
		int				key;
		int				joystickId;
	};

	typedef std::map<InputCommand::EventType, std::list<CallbackElem> > InputMap;

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
  _inputCallbacks[eventType].emplace_back(std::bind(method, &instance, std::placeholders::_1), key, joystickId);
}

CORE_END_NAMESPACE

#endif /* _INPUTMANAGER_ */
