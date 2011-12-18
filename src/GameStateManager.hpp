#ifndef		_GAMESTATEMANAGER_
#define 	_GAMESTATEMANAGER_

#include <list>
#include <string>
#include "GameStateInstance.hpp"
#include "Module.hpp"
#include "Singleton.hpp"
#include "Observable.hpp"

class GameStateManager : public Module, public Singleton<GameStateManager>, public Observable<std::list<GameState*> >
{
public:

  GameStateManager();
  virtual ~GameStateManager();
  virtual void	init();
  virtual void	update(double elapsedTime = 0);
  virtual void	destroy();
  bool			pushState(const std::string &name, GameState::Pause paused = GameState::ALL);
  bool			changeState(const std::string &name, GameState::Pause paused = GameState::ALL,
				  			bool del = true);
  void			popState(bool del = true);

  template <class T>
  void			loadState(T &state);
  template <class T>
  void			loadState(const std::string &name);
  void			removeState(const std::string &name);

  //getter
  GameState		&getCurrentState();
  void			getGameState(std::list<GameState*> &list, GameState::Pause state = GameState::ALL) const;


protected:
  void			addDelete(GameState *state);
  void			removeDelete();

private:
  typedef std::map<std::string, GameStateKeeper*>	instanceMap;

  bool			push(const std::string &name, bool changed, GameState::Pause paused);
  void			pop(bool changed, bool del);

protected:
  instanceMap				_keeper;
  std::list<GameState*>		_loadedStates;
  std::list<GameState*>		_currentStates;
  std::list<GameState*>		_deleted;
};

#include "GameStateManager.ipp"

bool		operator==(GameState const * const & state, const std::string &name);

#endif		/* _GAMESTATEMANAGER_ */
