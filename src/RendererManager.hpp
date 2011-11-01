#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/gui.h>
#include "GameState.hpp"
#include "Manager.hpp"
#include "Singleton.hpp"

class GameObjectManager;

class RendererManager : public Manager, public Singleton<RendererManager>
{
  public:
    RendererManager(void);
    ~RendererManager(void);
    void		initGraphics(const std::string &);
    void		update(GameState &state, double elapsedTime);
    void		clear();
    void		flip();
    CL_GraphicContext	&getGC(void);
    CL_DisplayWindow	*getWindow(void);

  protected:
    CL_DisplayWindow	*_window;
    CL_GraphicContext	_gc;

    CL_SetupDisplay 	_setup_display;
    CL_SetupGL		_setup_gl;
};
