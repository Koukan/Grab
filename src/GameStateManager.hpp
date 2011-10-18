#ifndef		_GAMESTATEMANAGER_
#define 	_GAMESTATEMANAGER_

#include <list>
#include <string>
#include "GameStateInstance.hpp"

typedef std::map<std::string, GameStateKeeper*>	instanceMap;

class GameStateManager
{
public:
  GameStateManager();
  virtual ~GameStateManager();
  bool		pushState(const std::string &name,
		  	  GameState::Pause paused = GameState::ALL);
  bool		changeState(const std::string &name,
			    GameState::Pause paused = GameState::ALL, bool del = true);
  void		popState(bool del = true);
  void		removeState(const std::string &name);
  template <class T>
  void		loadState(T &state);
  template <class T>
  void		loadState(const std::string &name);
  GameState	&getCurrentState();
  void		addDelete(GameState *state);
  void		removeDelete();

private:
  bool		push(const std::string &name, bool changed, GameState::Pause paused);
  void		pop(bool changed, bool del);

protected:
  instanceMap		_keeper;
  std::list<GameState*>	_loadedStates;
  std::list<GameState*>	_currentStates;
  std::list<GameState*>	_deleted;
};

#include "GameStateManager.ipp"

bool		operator==(GameState const * const & state, const std::string &name);

#endif		/* _GAMESTATEMANAGER_ */
