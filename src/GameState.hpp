#ifndef		_GAMESTATE_
#define 	_GAMESTATE_

#include <string>
#include "InputManager.hpp"
#include "GameObjectManager.hpp"
#include "EventDispatcher.hpp"

class Game;

class GameState : public InputManager, public GameObjectManager, public CL_ResourceManager,
		  public EventDispatcher
{
public:
  enum Pause
  {
    NONE = 0,
    DRAW = 1,
    NODRAW = 2,
    ALL = 3
  };

  GameState(const std::string &name);
  virtual ~GameState();
  virtual void	onStart();
  virtual void	onEnd();
  virtual void	onChange();
  virtual void	onResume();
  virtual void	update(int elapseTime = 0);
  void		pause(Pause paused = ALL);
  void		play();
  Pause		getPaused();

  const std::string	name;

private:
  Pause		_paused;
};

#endif		/* _GAMESTATE_ */
