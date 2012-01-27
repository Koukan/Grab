#include <algorithm>
#include "GSManager.hpp"

GSManager::GSManager() : Module("GSManager")
{
	this->_targetRate = 20;
}

GSManager::~GSManager()
{
}

void		GSManager::init()
{
}

void		GSManager::update(double elapsedTime)
{
	for (std::list<GameState*>::const_iterator it = this->_currentStates.begin();
		 it != this->_currentStates.end(); it++)
	{
		(*it)->update(elapsedTime);
	}
}

void		GSManager::destroy()
{
}

bool		GSManager::pushState(const std::string &name,
					    GameState::Pause paused)
{
	return push(name, true, paused);
}

bool		GSManager::pushState(GameState &state,
						GameState::Pause paused)
{
	return push(state, true, paused, false);
}

bool		GSManager::changeState(const std::string &name,
					      GameState::Pause paused, bool del)
{
	pop(false, del);
	return push(name, false, paused);
}

bool		GSManager::changeState(GameState &state,
					      GameState::Pause paused, bool del)
{
	pop(false, del);
	return push(state, false, paused, false);
}

void		GSManager::popState(bool del)
{
	pop(true, del);
	if (!_currentStates.empty())
		this->registerHandler(*_currentStates.back());
}

void		GSManager::removeState(const std::string &name)
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

GameState	&GSManager::getCurrentState()
{
	return *_currentStates.back();
}

void		GSManager::getGameState(std::list<GameState*> &list, GameState::Pause state) const
{
	for (std::list<GameState*>::const_iterator it = this->_currentStates.begin();
		 it != this->_currentStates.end(); it++)
	{
		if (((*it)->getPaused() & state))
			list.push_back(*it);
	}
}

void		GSManager::addDelete(GameState *state)
{
	if (state)
		_deleted.push_back(state);
}

void		GSManager::removeDelete()
{
	while (!_deleted.empty())
	{
		delete _deleted.front();
		_deleted.pop_front();
	}
}

bool		GSManager::push(const std::string &name, bool changed,
				       GameState::Pause paused)
{
	std::list<GameState*>::iterator	it;
	it = find(_loadedStates.begin(), _loadedStates.end(), name);
	if (it != _loadedStates.end())
	{
		this->push(**it, changed, paused, true);
		_loadedStates.erase(it);
		return true;
	}
	instanceMap::iterator		lit = _keeper.find(name);
	if (lit != _keeper.end())
	{
		this->push(*lit->second->newInstance(), changed, paused, false);
		return true;
	}
	return false;
}

bool		GSManager::push(GameState &state, bool changed,
							GameState::Pause paused, bool resume)
{
	if (changed && !_currentStates.empty())
	{
		_currentStates.back()->onChange();
		_currentStates.back()->pause(paused);
		this->removeHandler(*_currentStates.back());
	}
	_currentStates.push_back(&state);
	if (resume)
	{
		state.onResume();
		state.play();
	}
	else
		state.onStart();
	this->registerHandler(state);
	notify(this->_currentStates);
	return true;
}

void		GSManager::pop(bool changed, bool del)
{
	if (!_currentStates.empty())
	{
		this->removeHandler(*_currentStates.back());
		if (del)
		{
			_currentStates.back()->onEnd();
			addDelete(_currentStates.back());
		}
		else
		{
			_currentStates.back()->onChange();
			_currentStates.back()->pause();
			_loadedStates.push_back(_currentStates.back());
		}
		_currentStates.pop_back();
		if (changed && !_currentStates.empty())
		{
			_currentStates.back()->onResume();
			_currentStates.back()->play();
		}
	}
	notify(this->_currentStates);
}

bool		operator==(GameState const * const & state, const std::string &name)
{
	if (state->name == name)
		return true;
	return false;
}
