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

void	RendererManager::initGraphics(const std::string &name)
{
	//_window = new CL_DisplayWindow(name, 1024, 768, false, true);
	//_gc = _window->get_gc();
	CL_GUIWindowManagerSystem window_manager;
	CL_GUIThemeDefault theme;
	CL_GUIManager gui_manager;
	gui_manager.set_theme(theme);
	gui_manager.set_window_manager(window_manager);
	CL_GUITopLevelDescription desc;
	desc.set_title(name);
	_window2 = new CL_Window(&gui_manager, desc);
	_gc = _window2->get_display_window().get_gc();
}

void	RendererManager::update(GameState &state, int elapsedTime)
{
  if ((state.getPaused() & GameState::NODRAW) == GameState::NODRAW)
    return ;
  state.drawGameObject(elapsedTime);
}

void			RendererManager::clear(void)
{
  _gc.clear();
}

void			RendererManager::flip(void)
{
	//_window->flip(-1);
}

CL_GraphicContext	&RendererManager::getGC(void)
{
  return _gc;
}

CL_DisplayWindow 	*RendererManager::getWindow(void)
{
  return new CL_DisplayWindow(_window2->get_display_window());
}
