#ifndef		_GAMESTATE_
#define 	_GAMESTATE_

#include <string>
#include "InputManager.hpp"
#include "GameObjectManager.hpp"

class GameState : public InputManager, public GameObjectManager
{
  public:
    GameState(const std::string &name) : name(name)
    {}
    virtual ~GameState(){}
    virtual void	onStart(){}
    virtual void	onEnd(){}
    virtual void	onChange(){}
    virtual void	onResume(){}
    virtual void	update(){}

    const std::string	name;
};

#endif		/* _GAMESTATE_ */
