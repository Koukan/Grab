#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateObserver.hpp"
#include "Singleton.hpp"

class RendererManager : public GameStateObserver, public Singleton<RendererManager>
{
	public:
		RendererManager();
		virtual ~RendererManager();
		virtual void		init();
		virtual void		update(double elapsedTime);
		virtual void		destroy();
		void				clear();
		void				flip();
		//CL_GraphicContext	&getGC();
		sf::RenderWindow	*getWindow();
		//CL_GUIManager		&getGUIManager();
		//CL_GUIComponent	*getMainWindow();
		int					getWidth() const;
		int					getHeight() const;

	protected:
		//CL_SetupDisplay 	_setup_display;
		//CL_SetupGL			_setup_gl;
		//CL_SetupGUI			_setup_gui;

		//CL_MainWindow		*_window2;
		//CL_DisplayWindow	*_window;
		//CL_GraphicContext	_gc;
		//CL_GUIManager 		_gui_manager;
		int					_width;
		int					_height;
		sf::RenderWindow	*_window;
};
