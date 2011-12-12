#if defined (_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <ClanLib/gl.h>
#include "RendererManager.hpp"
#include "GameObjectManager.hpp"
#include "DrawableObject.hpp"
#include "Game.hpp"

RendererManager::RendererManager()
{
}

RendererManager::~RendererManager()
{
}

void	RendererManager::initGraphics(const std::string &name, int x, int y)
{
	_gui_manager = CL_GUIManager("resource/theme");
	CL_GUITopLevelDescription desc;
	this->_width = x;
	this->_height = y;
	desc.set_size(CL_Size(x, y), true);
	desc.set_title(name);
	_window2 = new CL_MainWindow(&_gui_manager, desc);
	_window2->get_menubar()->set_visible(false);
	_gc = _window2->get_gc();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1, 1, 0);
	glMatrixMode(GL_MODELVIEW);

}

void	RendererManager::update(GameState &state, double elapsedTime)
{
  if ((state.getPaused() & GameState::DRAW))
    return ;
  state.drawGameObject();
}

void			RendererManager::clear()
{
	_gc.clear();
}

void			RendererManager::flip()
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

int							RendererManager::getWidth() const
{
	return this->_width;
}

int							RendererManager::getHeight() const
{
	return this->_height;
}
