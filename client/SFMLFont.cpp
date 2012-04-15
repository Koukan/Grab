#include "SFMLFont.hpp"
#include "RendererManager.hpp"
#include <sstream>

SFMLFont::SFMLFont(std::string const &fileName, unsigned int size)
  : _window(RendererManager::get().getWindow())
{
	#if (SFML_VERSION_MAJOR == 2)
		this->_font.loadFromFile(fileName);
		this->_str.setCharacterSize(size);
		this->_str.setFont(this->_font);
	#else
		this->_font.LoadFromFile(fileName, 40);
		this->_str.SetSize(static_cast<float>(size));
		this->_str.SetFont(this->_font);
	#endif
}

SFMLFont::~SFMLFont()
{
}

Core::Resource	*SFMLFont::clone() const
{
	return new SFMLFont(*this);
}

void	SFMLFont::draw(double /*elapsedTime*/)
{
		//this->_str.SetX(static_cast<float>(this->_x));
		//this->_str.SetY(static_cast<float>(this->_y));
  #if (SFML_VERSION_MAJOR == 2)
	this->_str.setPosition(static_cast<float>(this->_x), static_cast<float>(this->_y));
	this->_window->draw(this->_str);
  #else
  	this->_str.SetPosition(static_cast<float>(this->_x), static_cast<float>(this->_y));
  	this->_window->Draw(this->_str);
  #endif
}

void	SFMLFont::draw(int x, int y, double /*elapsedTime*/)
{
		//this->_str.SetX(static_cast<float>(x));
		//this->_str.SetY(static_cast<float>(y));
 	#if (SFML_VERSION_MAJOR == 2)
	this->_str.setPosition(static_cast<float>(x), static_cast<float>(y));
 	this->_window->draw(this->_str);
	#else
	this->_str.SetPosition(static_cast<float>(x), static_cast<float>(y));
 	this->_window->Draw(this->_str);
	#endif
}

void	SFMLFont::setText(std::string const & text)
{
  #if (SFML_VERSION_MAJOR == 2)
  this->_str.setString(text);
  #else
  this->_str.SetText(text);
  #endif
}

void	SFMLFont::setColor(int r, int g, int b)
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->_str.getColor();

  base.r = r;
  base.g = g;
  base.b = b;
  this->_str.setColor(base);
  #else
  sf::Color base = this->_str.GetColor();

  base.r = r;
  base.g = g;
  base.b = b;
  this->_str.SetColor(base);
  #endif
}

void	SFMLFont::setColor(Color const & color)
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->_str.getColor();

  base.r = color.r;
  base.g = color.g;
  base.b = color.b;
  this->_str.setColor(base);
  #else
  sf::Color base = this->_str.GetColor();

  base.r = color.r;
  base.g = color.g;
  base.b = color.b;
  this->_str.SetColor(base);
  #endif
}

void	SFMLFont::setTransparency(int a)
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->_str.getColor();

  base.a = a;
  this->_str.setColor(base);
  #else
  sf::Color base = this->_str.GetColor();

  base.a = a;
  this->_str.SetColor(base);
  #endif
}

int	SFMLFont::getWidth() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.getLocalBounds().width);
   	#else
  	return (static_cast<int>(this->_str.GetRect().GetWidth()));
	#endif
}

int	SFMLFont::getHeight() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.getLocalBounds().height);
	#else
  	return (static_cast<int>(this->_str.GetRect().GetHeight()));
	#endif
}
