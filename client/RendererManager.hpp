#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateObserver.hpp"
#include "Singleton.hpp"

class RendererManager : public Core::GameStateObserver, public Net::Singleton<RendererManager>
{
	public:
		RendererManager();
		virtual ~RendererManager();
		virtual void		init();
		virtual void		update(double elapsedTime);
		virtual void		destroy();
		void				clear();
		void				flip();
		sf::RenderWindow	*getWindow();
		int					getWidth() const;
		int					getHeight() const;

	protected:
		int					_width;
		int					_height;
		sf::RenderWindow	*_window;
};
