#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "DrawableObject.hpp"
#include "PhysicObject.hpp"
#include "CircleHitBox.hpp"
#include "icon.c"
#include <GL/glu.h>

RendererManager::RendererManager() : Core::GameStateObserver("RendererManager")
{
	this->_targetRate = 20;
	this->_fullscreen = false;
}

RendererManager::~RendererManager()
{
}

void				RendererManager::init()
{
	sf::VideoMode video = sf::VideoMode::GetDesktopMode();
	this->_width = video.Width;
	this->_height = video.Height;
	this->updateWindow();
	//_shader.LoadFromFile("client/.fx", sf::Shader::Vertex);
	//_shader.LoadFromFile("client/hfragment.fx", sf::Shader::Fragment);
	//_shader.SetParameter("sceneTex", sf::Shader::CurrentTexture);
	//_shader.SetParameter("vx_offset", 0.0f);
}

void RendererManager::drawNode(Core::Node *node)
{
	#if (SFML_VERSION_MAJOR == 2)
		sf::RectangleShape  rect(sf::Vector2f(node->getSize(), node->getSize()));
		rect.SetOutlineColor(sf::Color(255, 255, 255, 50));
		rect.SetFillColor(sf::Color(0, 0, 0,0));
		rect.SetOutlineThickness(2.0);
		rect.SetPosition(node->getX(), node->getY());
		this->_window.Draw(rect);
	#else
		this->_window.Draw(sf::Shape::Rectangle(static_cast<float>(node->getX()), static_cast<float>(node->getY()),
			static_cast<float>(node->getX() + node->getSize()), static_cast<float>(node->getY() + node->getSize()),
			sf::Color(0, 0, 0, 0), 2.0, sf::Color(0, 255, 0, 50)));
	#endif

	for (int i = 0; i < 4; ++i)
	{
		Core::Node *child = node->getChilds()[i];
		if (child)
			this->drawNode(child);
	}
}

void RendererManager::drawQuadTree(Core::QuadTree const &quadTree)
{
	//for (int i = 0; i < 4; ++i)
	//{
		Core::Node *node = quadTree._mainNode->getChilds()[0];
		if (node)
			this->drawNode(node);
	//}
}

void				RendererManager::update(double elapsedTime)
{
  Core::GameObjectManager::groupsDisplay::const_iterator	lit;
  Core::Group::gameObjectSet::const_iterator				oit;
	double												time;

	this->clear();
	for (std::list<Core::GameState*>::const_iterator it = this->_glist.begin();
			it != this->_glist.end(); it++)
	{
	  if (((*it)->getPaused() & Core::GameState::DRAW) != 0)
				continue;
		Core::GameObjectManager::groupsDisplay const	&groups = (*it)->getDisplayObjects();
		for (lit = groups.begin(); lit != groups.end(); lit++)
		{
			if (lit->second->getLayer() >= 0)
			{
//				if (lit->second->getName() == "playerShots" || lit->second->getName() == "monster")
//				this->drawQuadTree(lit->second->getQuadTree());
				if (((*it)->getPaused() & Core::GameState::PHYSIC) != 0)
					time = 0;
				else
					time = lit->second->getTimeEffect() * elapsedTime;
				Core::Group::gameObjectSet const	&objects = lit->second->getObjects();
				for (oit = objects.begin(); oit != objects.end(); oit++)
				{
					static_cast<Core::DrawableObject*>(*oit)->draw(time);
					if (lit->second->getPhysic())
					  this->displayHitBox(oit);
				}
			}
		}
		(*it)->getGUI().draw(elapsedTime);
	}
	this->flip();
}

void				RendererManager::destroy()
{
}

void				RendererManager::clear()
{
	_window.Clear();
}

void				RendererManager::flip()
{
	_window.Display();
}

sf::RenderWindow	*RendererManager::getWindow()
{
	return &_window;
}

Shader			&RendererManager::getShader()
{
	return _shader;
}

int					RendererManager::getWidth() const
{
	return this->_width;
}

int					RendererManager::getHeight() const
{
  	return this->_height;
}

void				RendererManager::setResolution(int width, int height)
{
	this->_width = width;
	this->_height = height;
	this->updateWindow();
}

void				RendererManager::setFullscreen(bool fullscreen)
{
	if (fullscreen != _fullscreen)
		{
			_fullscreen = fullscreen;
			this->updateWindow();
		}
}

bool				RendererManager::isFullscreen() const
{
	return _fullscreen;
}

std::list<RendererManager::VideoMode>	RendererManager::getAvailableResolutions() const
{
	std::list<RendererManager::VideoMode>	ret;
	RendererManager::VideoMode tmp;
#if (SFML_VERSION_MAJOR == 2)
	std::vector<sf::VideoMode> modes = sf::VideoMode::GetFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		tmp.width = modes[i].Width;
		tmp.height = modes[i].Height;
		if (tmp.width >= 800 && tmp.height >= 600)
			ret.push_back(tmp);
	}
#else
	for (std::size_t i = 0; i < sf::VideoMode::GetModesCount(); ++i)
	{
		tmp.width = sf::VideoMode::GetMode(i).Width;
		tmp.height = sf::VideoMode::GetMode(i).Height;
		if (tmp.width >= 800 && tmp.height >= 600)
			ret.push_back(tmp);
	}
#endif
	return ret;
}

void				RendererManager::updateWindow()
{
#if (SFML_VERSION_MAJOR == 2)
	sf::Uint32 style = (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default;
#else
	sf::Uint32 style = (_fullscreen) ? sf::Style::Fullscreen : (sf::Style::Resize | sf::Style::Close);
#endif
	_window.Create(sf::VideoMode(this->_width, this->_height), "Grab", style);
	_window.ShowMouseCursor(!_fullscreen);
	_window.SetIcon(grab_icon.width, grab_icon.height, grab_icon.pixel_data);
#if (SFML_VERSION_MAJOR == 2)
	sf::View	view(sf::FloatRect(0, 0, VIEWX, VIEWY));
#else
	sf::View &view = this->_window.GetDefaultView();
	//sf::View	view(sf::FloatRect(0, 0, 1342, 742));
	view.SetFromRect(sf::FloatRect(0, 0, VIEWX, VIEWY));
#endif
	this->_window.SetView(view);
}

void	RendererManager::displayHitBox(Core::Group::gameObjectSet::const_iterator oit)
{
	Core::PhysicObject * tmp = static_cast<Core::PhysicObject*>(*oit);
	try
	{
		Core::CircleHitBox &hitbox = dynamic_cast<Core::CircleHitBox&>(tmp->getHitBox());
		#if (SFML_VERSION_MAJOR == 2)
		sf::CircleShape  circle(hitbox.getRadius());
		circle.SetOutlineColor(sf::Color(255, 255, 255));
		circle.SetFillColor(sf::Color(0, 0, 0, 0));
		circle.SetOutlineThickness(2.0);
		circle.SetPosition(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset());
		this->_window.Draw(circle);
		#else
		this->_window.Draw(sf::Shape::Circle(tmp->getX() + tmp->getXHitBoxOffset() + hitbox.getRadius(), tmp->getY() + tmp->getYHitBoxOffset() + hitbox.getRadius(), hitbox.getRadius(), sf::Color(0, 0, 0,0), 2.0, sf::Color(0, 255, 0)));
		#endif
	}
	catch (...)
	{
		try
		{
			Core::RectHitBox &hitbox = dynamic_cast<Core::RectHitBox&>(tmp->getHitBox());
			#if (SFML_VERSION_MAJOR == 2)
			sf::RectangleShape  rect(sf::Vector2f(hitbox.getWidth(), hitbox.getHeight()));
			rect.SetOutlineColor(sf::Color(255, 255, 255));
			rect.SetFillColor(sf::Color(0, 0, 0,0));
			rect.SetOutlineThickness(2.0);
			rect.SetPosition(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset());
			this->_window.Draw(rect);
			#else
			this->_window.Draw(sf::Shape::Rectangle(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset(), tmp->getX() + tmp->getXHitBoxOffset() + hitbox.getWidth(), tmp->getY() + tmp->getYHitBoxOffset() + hitbox.getHeight(), sf::Color(0, 0, 0,0), 2.0, sf::Color(0, 255, 0)));
			#endif
		}
		catch (...)
		{
		}
	}
}
