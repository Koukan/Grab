#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "DrawableObject.hpp"

RendererManager::RendererManager() : Core::GameStateObserver("RendererManager")
{
	this->_targetRate = 20;
	this->_window = 0;
}

RendererManager::~RendererManager()
{
	if (_window)
	{
		_window->Close();
		delete _window;
	}
}

void				RendererManager::init()
{
	this->_width = 1280;
	this->_height = 720;
}

void				RendererManager::update(double elapsedTime)
{
  Core::GameObjectManager::groupsDisplay::const_iterator	lit;
  Core::Group::gameObjectSet::const_iterator				oit;
	double												time;

	this->clear();
	for (std::list<Core::GameState*>::const_iterator it = this->_glist.begin();
			it != this->_glist.end(); it++)
	{
	  if (((*it)->getPaused() & Core::GameState::DRAW) != 0)
				continue;
		Core::GameObjectManager::groupsDisplay const	&groups = (*it)->getDisplayObjects();
		for (lit = groups.begin(); lit != groups.end(); lit++)
		{
			if (lit->second->getLayer() >= 0)
			{
				time = lit->second->getTimeEffect() * elapsedTime;
				Core::Group::gameObjectSet const	&objects = lit->second->getObjects();
				for (oit = objects.begin(); oit != objects.end(); oit++)
				{
					static_cast<Core::DrawableObject*>(*oit)->draw(time);
				}
			}
		}
		(*it)->getGUI().draw(elapsedTime);
	}
	this->flip();
}

void				RendererManager::destroy()
{
}

void				RendererManager::clear()
{
	_window->Clear();
}

void				RendererManager::flip()
{
	_window->Display();
}

sf::RenderWindow	*RendererManager::getWindow()
{
	if (!_window)
	{
		_window = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height), "R-Type"/*, sf::Style::Fullscreen*/);
	}
	return _window;
}

int					RendererManager::getWidth() const
{
	return this->_width;
}

int					RendererManager::getHeight() const
{
	return this->_height;
}
