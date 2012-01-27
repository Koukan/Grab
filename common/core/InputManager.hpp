#ifndef _INPUTMANAGER_
#define _INPUTMANAGER_

#include <map>
#include <list>
#include "Callback.hpp"
#include "Input.hpp"
#include "CommandHandler.hpp"

class GameState;

class InputManager : public CommandHandler
{
public:
	InputManager(GameState &game);
	~InputManager();

	void	handleInput(const InputCommand &event);
	void	flushInput();
	virtual bool	handleCommand(Command const &cmd);

	template <typename T>
	void        registerInputCallback(InputCommand::EventType eventType, T &instance,
				   	void (T::*method)(const InputCommand &event), int key = -1);

private:
	struct	CallbackElem
	{
		Callback		*callback;
		int				key;
	};

	typedef std::map<InputCommand::EventType, std::list<CallbackElem*> > InputMap;
	
	GameState	&_gs;
	bool		_flush;
	InputMap  	_inputCallbacks;
};

template <typename T>
void		InputManager::registerInputCallback(InputCommand::EventType eventType,
		T &instance, void (T::*method)(const InputCommand &event), int key)
{
  if (!method)
    return ;
  CallbackElem	*tmp = new CallbackElem();
  tmp->callback = new Callback(instance, method);
  tmp->key = key;
  _inputCallbacks[eventType].push_back(tmp);
}

#endif /* _INPUTMANAGER_ */
