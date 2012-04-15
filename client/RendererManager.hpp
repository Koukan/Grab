#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateObserver.hpp"
#include "Singleton.hpp"
#if (SFML_VERSION_MAJOR == 2)
	#include <SFML/Graphics/Shader.hpp>
	typedef sf::Shader	Shader;
#else
	#include <SFML/Graphics/PostFX.hpp>
typedef sf::PostFX		Shader;
#endif
#define		VIEWX	1680
#define		VIEWY	1050

class RendererManager : public Core::GameStateObserver, public Net::Singleton<RendererManager>
{
	public:
		struct VideoMode
		{
			int	width;
			int	height;
		};

		RendererManager();
		virtual ~RendererManager();
		virtual void		init();
		virtual void		update(double elapsedTime);
		virtual void		destroy();
		void				clear();
		void				flip();
		sf::RenderWindow	*getWindow();
		Shader				&getShader();
		int					getWidth() const;
		int					getHeight() const;
		void				setResolution(int width, int height);
		void				setFullscreen(bool fullscreen);
		bool				isFullscreen() const;
		std::list<VideoMode>	getAvailableResolutions() const;

	protected:
		int					_width;
		int					_height;
		bool				_fullscreen;
		sf::RenderWindow	_window;
		Shader				_shader;

private:
		void				updateWindow();
		void 				drawQuadTree(Core::QuadTree const &quadTree);
		void 				drawNode(Core::Node *node);
		void				displayHitBox(Core::Group::gameObjectSet::const_iterator oit);
};
