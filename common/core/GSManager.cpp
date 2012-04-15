#include <algorithm>
#include "GSManager.hpp"
#include "CommandDispatcher.hpp"

CORE_BEGIN_NAMESPACE

GSManager::GSManager() : Module("GSManager", 20)
{
}

GSManager::~GSManager()
{

	this->removeDelete();
	for (std::list<GameState*>::iterator it = this->_currentStates.begin();
		 it != this->_currentStates.end(); it++)
		delete *it;
	for (std::list<GameState*>::iterator it = this->_loadedStates.begin();
		 it != this->_loadedStates.end(); it++)
		delete *it;
}

void		GSManager::init()
{
}

void		GSManager::update(double elapsedTime)
{
	std::list<GameState*>::const_iterator tmp;
	for (std::list<GameState*>::const_iterator it = this->_currentStates.begin();
		 it != this->_currentStates.end();)
	{
		tmp = it++;
		(*tmp)->handle(elapsedTime);
		(*tmp)->update(elapsedTime);
	}
	if (!this->_currentStates.empty())
		this->_currentStates.back()->getGUI().update(elapsedTime);
	this->removeDelete();
}

void		GSManager::destroy()
{
}

bool		GSManager::pushState(std::string const &name,
								 GameState::Pause paused)
{
	std::list<GameState*>::iterator it = find(_loadedStates.begin(), _loadedStates.end(), name);

	if (it != this->_loadedStates.end())
	{
		push(**it, true, paused, true);
		this->_loadedStates.erase(it);
		return true;
	}
	return false;
}

bool		GSManager::pushState(GameState &state,
						GameState::Pause paused)
{
	push(state, true, paused, false);
	return true;
}

bool		GSManager::changeState(GameState &state,
					      GameState::Pause paused, bool del)
{
	pop(false, del);
	push(state, false, paused, false);
	return true;
}

void		GSManager::popState(bool del)
{
	pop(true, del);
	if (!_currentStates.empty())
		this->registerHandler(*_currentStates.back());
}

void		GSManager::removeLoadedState(std::string const &name)
{
	std::list<GameState*>::iterator it = find(_loadedStates.begin(), _loadedStates.end(), name);

	if (it != _loadedStates.end())
	{
		addDelete(*it);
		this->_loadedStates.erase(it);
	}
}

GameState	&GSManager::getCurrentState() const
{
	return *_currentStates.back();
}

GameState	*GSManager::getGameState(std::string const &name) const
{
	std::list<GameState*>::const_iterator it = find(_currentStates.begin(), _currentStates.end(), name);
	if (it != _currentStates.end())
		return *it;
	return 0;
}

GameState	*GSManager::getLoadedState(std::string const &name) const
{
	std::list<GameState*>::const_iterator it = find(_loadedStates.begin(), _loadedStates.end(), name);

	if (it != _loadedStates.end())
		return *it;
	return 0;
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

bool		operator==(Core::GameState const * const & state, const std::string &name)
{
	if (state->name == name)
		return true;
	return false;
}

CORE_END_NAMESPACE

