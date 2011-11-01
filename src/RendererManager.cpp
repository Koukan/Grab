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
  _window = new CL_DisplayWindow(name, 1024, 768, false, true);
  _gc = _window->get_gc();
}

void	RendererManager::update(GameState &state, double elapsedTime)
{
  if ((state.getPaused() & GameState::DRAW))
    return ;
  state.drawGameObject(elapsedTime);
}

void			RendererManager::clear(void)
{
  _gc.clear();
}

void			RendererManager::flip(void)
{
  _window->flip(-1);
}

CL_GraphicContext	&RendererManager::getGC(void)
{
  return _gc;
}

CL_DisplayWindow 	*RendererManager::getWindow(void)
{
  return _window;
}
