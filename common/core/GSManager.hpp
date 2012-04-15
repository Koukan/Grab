#pragma once

#include <list>
#include <queue>
#include <string>
#include "GameState.hpp"
#include "Module.hpp"
#include "Observable.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ GSManager : public Module, public Observable<std::list<GameState*> >
{
public:
  GSManager();
  virtual ~GSManager();
  virtual void	init();
  virtual void	update(double elapsedTime = 0);
  virtual void	destroy();
  bool			pushState(std::string const &name, GameState::Pause paused = GameState::ALL);
  bool			pushState(GameState &state, GameState::Pause paused = GameState::ALL);
  bool			changeState(GameState &state, GameState::Pause paused = GameState::ALL,
				  			bool del = true);
  void			popState(bool del = true);
  void			removeLoadedState(std::string const &name);

  //getter
  GameState		&getCurrentState() const;
  GameState		*getGameState(std::string const &name) const;
  void			getGameState(std::list<GameState*> &list, GameState::Pause state = GameState::ALL) const;
  std::list<GameState *> const & getCurrentStates() const;
  GameState		*getLoadedState(std::string const &name) const;

protected:
  void			addDelete(GameState *state);
  void			removeDelete();

private:
  bool			push(GameState &state, bool changed, GameState::Pause paused, bool resume);
  void			pop(bool changed, bool del);

protected:
  std::list<GameState*>		_loadedStates;
  std::list<GameState*>		_currentStates;
  std::list<GameState*>		_deleted;
};

bool		operator==(Core::GameState const * const & state, const std::string &name);

CORE_END_NAMESPACE
