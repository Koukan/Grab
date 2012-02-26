#include "SFMLFont.hpp"
#include "RendererManager.hpp"
#include <sstream>

SFMLFont::SFMLFont(std::string const &fileName, unsigned int size)
  : _window(RendererManager::get().getWindow())
{
	#if (SFML_VERSION_MAJOR == 2)
		this->_font.LoadFromFile(fileName);
	#else
		this->_font.LoadFromFile(fileName, 40);
	#endif
	this->_str.SetFont(this->_font);
	#if (SFML_VERSION_MAJOR == 2)
		this->_str.SetCharacterSize(size);
	#else
		this->_str.SetSize(static_cast<float>(size));
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
  this->_str.SetPosition(this->_x, this->_y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::draw(int x, int y, double /*elapsedTime*/)
{
		//this->_str.SetX(static_cast<float>(x));
		//this->_str.SetY(static_cast<float>(y));
  this->_str.SetPosition(x, y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::setText(std::string const & text)
{
  #if (SFML_VERSION_MAJOR == 2)
  this->_str.SetString(text);
  #else
  this->_str.SetText(text);
  #endif
}

void	SFMLFont::setColor(int r, int g, int b)
{
  sf::Color base = this->_str.GetColor();

  base.r = r;
  base.g = g;
  base.b = b;
  this->_str.SetColor(base);
}

void	SFMLFont::setTransparency(int a)
{
  sf::Color base = this->_str.GetColor();

  base.a = a;
  this->_str.SetColor(base);
}

int	SFMLFont::getWidth() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.GetLocalBounds().Width);
   	#else
  	return (static_cast<int>(this->_str.GetRect().GetWidth()));
	#endif
}

int	SFMLFont::getHeight() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.GetLocalBounds().Height);
	#else
  	return (static_cast<int>(this->_str.GetRect().GetHeight()));
	#endif
}
