#include "RendererManager.hpp"
#include "GameObjectManager.hpp"
#include "DrawableObject.hpp"
#include "Game.hpp"

RendererManager::RendererManager(void)
{
  Game::get().loadManager(this);
}

RendererManager::~RendererManager(void)
{
}

void	RendererManager::initGraphics(const std::string &name, int x, int y)
{
	//_window = new CL_DisplayWindow(name, 1024, 768, false, true);
	//_gc = _window->get_gc();
	_gui_manager = CL_GUIManager("resource/theme");
	//_gui_manager.set_window_manager(_window_manager);
	CL_GUITopLevelDescription desc;
	desc.set_size(CL_Size(x, y), true);
	desc.set_title(name);
	_window2 = new CL_MainWindow(&_gui_manager, desc);
	_gc = _window2->get_gc();
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
	//_window->flip(-1);
	//_window2->get_display_window().flip(-1);
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
