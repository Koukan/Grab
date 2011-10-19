#include <algorithm>
#include "GameStateManager.hpp"

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

bool		GameStateManager::pushState(const std::string &name,
					    GameState::Pause paused)
{
  return push(name, true, paused);
}

bool		GameStateManager::changeState(const std::string &name,
					      GameState::Pause paused, bool del)
{
  pop(false, del);
  return push(name, false, paused);
}

void		GameStateManager::popState(bool del)
{
  pop(true, del);
}

void		GameStateManager::removeState(const std::string &name)
{
  for (std::list<GameState*>::iterator it = _currentStates.begin();
	it != _currentStates.end(); it++)
    if ((*it)->name == name)
    {
      (*it)->onEnd();
      it = _currentStates.erase(it);
    }
  _loadedStates.erase(find(_loadedStates.begin(), _loadedStates.end(), name));
  _keeper.erase(name);
}

GameState	&GameStateManager::getCurrentState()
{
  return *_currentStates.front();
}

void		GameStateManager::addDelete(GameState *state)
{
  if (state)
    _deleted.push_back(state);
}

void		GameStateManager::removeDelete()
{
  while (!_deleted.empty())
  {
    delete _deleted.front();
    _deleted.pop_front();
  }
}

bool		GameStateManager::push(const std::string &name, bool changed,
				       GameState::Pause paused)
{
  std::list<GameState*>::iterator	it;
  it = find(_loadedStates.begin(), _loadedStates.end(), name);
  if (it != _loadedStates.end())
  {
    if (changed && !_currentStates.empty())
    {
      _currentStates.front()->onChange();
      _currentStates.front()->pause(paused);
    }
    _currentStates.push_front(*it);
    _loadedStates.erase(it);
    (*it)->onResume();
    (*it)->play();
    return true;
  }
  instanceMap::iterator		lit = _keeper.find(name);
  if (lit != _keeper.end())
  {
    GameState	*state = lit->second->newInstance();
    if (changed && !_currentStates.empty())
    {
      _currentStates.front()->onChange();
      _currentStates.front()->pause(paused);
    }
    _currentStates.push_front(state);
    state->onStart();
    return true;
  }
  return false;
}

void		GameStateManager::pop(bool changed, bool del)
{
  if (!_currentStates.empty())
  {
    if (del)
    {
      _currentStates.front()->onEnd();
      addDelete(_currentStates.front());
    }
    else
    {
      _currentStates.front()->onChange();
      _currentStates.front()->pause();
      _loadedStates.push_back(_currentStates.front());
    }
    _currentStates.pop_front();
    if (changed && !_currentStates.empty())
    {
      _currentStates.front()->onResume();
      _currentStates.front()->play();
    }
  }
}

bool		operator==(GameState const * const & state, const std::string &name)
{
  if (state->name == name)
    return true;
  return false;
}
