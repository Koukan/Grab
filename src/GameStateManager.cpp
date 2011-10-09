#include <algorithm>
#include "GameStateManager.hpp"

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

bool			GameStateManager::pushState(const std::string &name)
{
  return push(name, true);
}

bool			GameStateManager::changeState(const std::string &name)
{
  pop(false);
  return push(name, false);
}

void			GameStateManager::popState(void)
{
  pop(true);
}

void			GameStateManager::removeState(const std::string &name)
{
  for (std::list<GameState*>::iterator it = _currentStates.begin();
	it != _currentStates.end(); it++)
    if ((*it)->name == name)
    {
      (*it)->onEnd();
      it = _currentStates.erase(it);
    }
  _loadedStates.erase(find(_loadedStates.begin(), _loadedStates.end(), name));
}

void			GameStateManager::loadState(GameState &state)
{
  for (std::list<GameState*>::iterator it = _currentStates.begin();
	it != _currentStates.end(); it++)
    if ((*it)->name == state.name)
      (*it)->onEnd();
  _loadedStates.push_back(&state);
}

GameState	&GameStateManager::getCurrentState(void)
{
  return *_currentStates.front();
}

bool			GameStateManager::push(const std::string &name, bool changed)
{
  std::list<GameState*>::iterator	it;

  it = find(_loadedStates.begin(), _loadedStates.end(), name);
  if (it != _loadedStates.end())
  {
    if (changed && !_currentStates.empty())
      _currentStates.front()->onChange();
    _currentStates.push_front(*it);
    (*it)->onStart();
    return true;
  }
  return false;
}

void			GameStateManager::pop(bool changed)
{
  if (!_currentStates.empty())
  {
    _currentStates.front()->onEnd();
    _currentStates.pop_front();
    if (changed && !_currentStates.empty())
      _currentStates.front()->onResume();
  }
}

bool		operator==(GameState const * const & state, const std::string &name)
{
  if (state->name == name)
    return true;
  return false;
}
