#include "SFMLFont.hpp"
#include "RendererManager.hpp"
#include <sstream>

SFMLFont::SFMLFont(std::string const &fileName, std::string const &strsize)
  : _window(RendererManager::get().getWindow())
{
  this->_font.LoadFromFile(fileName);
  this->_str.SetFont(this->_font);
  if (strsize != "")
    {
      unsigned int size;
      std::istringstream buffer(strsize);
      buffer >> size;
#if (SFML_VERSION_MAJOR == 2)
	  this->_str.SetCharacterSize(size);
#else
      this->_str.SetSize(size);
#endif
    }
}

SFMLFont::~SFMLFont()
{
}

void	SFMLFont::draw(double /*elapsedTime*/)
{
  this->_str.SetX(this->_x);
  this->_str.SetY(this->_y);
  this->_window->Draw(this->_str);
}

void	SFMLFont::draw(int x, int y, double /*elapsedTime*/)
{
  this->_str.SetX(x);
  this->_str.SetY(y);
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
  this->_str.SetColor(sf::Color(r, g, b));
}

int	SFMLFont::getWidth()
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.GetRect().Width);
   	#else
  	return (this->_str.GetRect().GetWidth());
	#endif
}

int	SFMLFont::getHeight()
{
	#if (SFML_VERSION_MAJOR == 2)
	return (this->_str.GetRect().Height);
	#else
  	return (this->_str.GetRect().GetHeight());
	#endif
}
