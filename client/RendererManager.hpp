#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateObserver.hpp"
#include "Singleton.hpp"
#if (SFML_VERSION_MAJOR == 2)
	#include <SFML/Graphics/Shader.hpp>
	typedef sf::Shader	Shader;
#else
	#include <SFML\Graphics\PostFX.hpp>
typedef sf::PostFX		Shader;
#endif

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
		Shader			&getShader();
		int					getWidth() const;
		int					getHeight() const;

	protected:
		int					_width;
		int					_height;
		sf::RenderWindow	*_window;
		Shader			_shader;

private:
	void drawQuadTree(Core::QuadTree const &quadTree);
	void drawNode(Core::Node *node);
};
