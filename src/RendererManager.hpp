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
    RendererManager();
    virtual ~RendererManager();
    void		initGraphics(const std::string &, int x = 1024, int y = 768);
    void		update(GameState &state, double elapsedTime);
    void		clear();
    void		flip();
    CL_GraphicContext	&getGC();
    CL_DisplayWindow	*getWindow();
    CL_GUIManager		&getGUIManager();
    CL_GUIComponent		*getMainWindow();

  protected:
    CL_SetupDisplay 	_setup_display;
    CL_SetupGL			_setup_gl;
    CL_SetupGUI			_setup_gui;

    CL_MainWindow			*_window2;
    CL_DisplayWindow		*_window;
    CL_GraphicContext		_gc;
    CL_GUIManager 			_gui_manager;
};
