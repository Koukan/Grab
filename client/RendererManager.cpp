#include "RendererManager.hpp"
#include "GameStateManager.hpp"
#include "DrawableObject.hpp"
#include "PhysicObject.hpp"
#include "CircleHitBox.hpp"

RendererManager::RendererManager() : Core::GameStateObserver("RendererManager")
{
	this->_targetRate = 20;
	this->_window = 0;
}

RendererManager::~RendererManager()
{
	if (_window)
	{
		_window->Close();
		delete _window;
	}
}

void				RendererManager::init()
{
	this->_width = 1280;
	this->_height = 720;
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
		this->_window->Draw(rect);
	#else
		this->_window->Draw(sf::Shape::Rectangle(static_cast<float>(node->getX()), static_cast<float>(node->getY()),
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
				time = lit->second->getTimeEffect() * elapsedTime;
				Core::Group::gameObjectSet const	&objects = lit->second->getObjects();
				for (oit = objects.begin(); oit != objects.end(); oit++)
				{
					static_cast<Core::DrawableObject*>(*oit)->draw(time);
					//Core::PhysicObject * tmp = dynamic_cast<Core::PhysicObject*>(*oit);
					//if (tmp)
					//{
					//		try
					//		{
					//			Core::CircleHitBox &hitbox = dynamic_cast<Core::CircleHitBox&>(tmp->getHitBox());
					//			#if (SFML_VERSION_MAJOR == 2)
					//			sf::CircleShape  circle(hitbox.getRadius());
					//			circle.SetOutlineColor(sf::Color(255, 255, 255));
					//			circle.SetFillColor(sf::Color(0, 0, 0, 0));
					//			circle.SetOutlineThickness(2.0);
					//			circle.SetPosition(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset());
					//			this->_window->Draw(circle);
					//			#else
					//			this->_window->Draw(sf::Shape::Circle(tmp->getX() + tmp->getXHitBoxOffset() + hitbox.getRadius(), tmp->getY() + tmp->getYHitBoxOffset() + hitbox.getRadius(), hitbox.getRadius(), sf::Color(0, 0, 0,0), 2.0, sf::Color(0, 255, 0)));
					//			#endif
					//		}
					//		catch (...)
					//		{
					//			try
					//			{
					//				Core::RectHitBox &hitbox = dynamic_cast<Core::RectHitBox&>(tmp->getHitBox());
					//				#if (SFML_VERSION_MAJOR == 2)
					//				sf::RectangleShape  rect(sf::Vector2f(hitbox.getWidth(), hitbox.getHeight()));
					//				rect.SetOutlineColor(sf::Color(255, 255, 255));
					//				rect.SetFillColor(sf::Color(0, 0, 0,0));
					//				rect.SetOutlineThickness(2.0);
					//				rect.SetPosition(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset());
					//				this->_window->Draw(rect);
					//				#else
					//				this->_window->Draw(sf::Shape::Rectangle(tmp->getX() + tmp->getXHitBoxOffset(), tmp->getY() + tmp->getYHitBoxOffset(), tmp->getX() + tmp->getXHitBoxOffset() + hitbox.getWidth(), tmp->getY() + tmp->getYHitBoxOffset() + hitbox.getHeight(), sf::Color(0, 0, 0,0), 2.0, sf::Color(0, 255, 0)));
					//				#endif
					//			}
					//			catch (...)
					//			{
					//			}
					//		}
					//}
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
	_window->Clear();
}

void				RendererManager::flip()
{
	_window->Display();
}

sf::RenderWindow	*RendererManager::getWindow()
{
	if (!_window)
	{
		_window = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height), "Grab"/*, sf::Style::Fullscreen*/);
	}
	return _window;
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
