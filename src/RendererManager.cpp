#if defined (_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <ClanLib/gl.h>
#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "DrawableObject.hpp"
#include "Game.hpp"

RendererManager::RendererManager() : GameStateObserver("RendererManager")
{
	this->_targetRate = 20;
	Game::get().loadModule(*this);
}

RendererManager::~RendererManager()
{
}

void				RendererManager::init()
{
	_gui_manager = CL_GUIManager("resource/theme");
	CL_GUITopLevelDescription desc;
	this->_width = 1024;
	this->_height = 768;
	desc.set_size(CL_Size(this->_width, this->_height), true);
	desc.set_title("Grab: The Power of the Lost Grapple");
	this->_window2 = new CL_MainWindow(&this->_gui_manager, desc);
	this->_window2->get_menubar()->set_visible(false);
	this->_gc = this->_window2->get_gc();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void				RendererManager::update(double elapsedTime)
{
	GameObjectManager::groupsDisplay::const_iterator	lit;
	Group::gameObjectSet::const_iterator				oit;
	double												time;

	this->clear();
	for (std::list<GameState*>::const_iterator it = this->_glist.begin();
		 it != this->_glist.end(); it++)
	{
		GameObjectManager::groupsDisplay const	&groups = (*it)->getDisplayObjects();
		for (lit = groups.begin(); lit != groups.end(); lit++)
		{
			if (lit->second->getLayer() >= 0)
			{
				time = lit->second->getTimeEffect() * elapsedTime;
				Group::gameObjectSet const	&objects = lit->second->getObjects();
				for (oit = objects.begin(); oit != objects.end(); oit++)
				{
					static_cast<DrawableObject*>(*oit)->draw(time);
				}
			}
		}
	}
	this->flip();
}

void				RendererManager::destroy()
{
}

void				RendererManager::clear()
{
	_gc.clear();
}

void				RendererManager::flip()
{
	_window2->paint();
}

CL_GraphicContext	&RendererManager::getGC()
{
	return _gc;
}

CL_DisplayWindow 	*RendererManager::getWindow()
{
	return new CL_DisplayWindow(_window2->get_display_window());
}

CL_GUIManager		&RendererManager::getGUIManager()
{
	return _gui_manager;
}

CL_GUIComponent		*RendererManager::getMainWindow()
{
	return _window2;
}

int					RendererManager::getWidth() const
{
	return this->_width;
}

int					RendererManager::getHeight() const
{
	return this->_height;
}
