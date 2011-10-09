#ifndef		_GAMESTATEMANAGER_
#define 	_GAMESTATEMANAGER_

#include <list>
#include <string>
#include "GameState.hpp"

class GameStateManager
{
public:
  GameStateManager();
  virtual ~GameStateManager();
  bool		pushState(const std::string &name);
  bool		changeState(const std::string &name);
  void		popState();
  void		removeState(const std::string &name);
  void		loadState(GameState &state);
  GameState	&getCurrentState();

private:
  bool		push(const std::string &name, bool changed);
  void		pop(bool changed);

protected:
  std::list<GameState*>	_loadedStates;
  std::list<GameState*>	_currentStates;
};

bool		operator==(GameState const * const & state, const std::string &name);

#endif		/* _GAMESTATEMANAGER_ */
