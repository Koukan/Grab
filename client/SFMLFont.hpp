#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "Font.hpp"

class SFMLFont : public Font
{
public:
  SFMLFont(std::string const &fileName, std::string const &size);
  ~SFMLFont();

  virtual void	draw(double elapsedTime = 0);
  virtual void	draw(int x, int y, double elapsedTime = 0);
  virtual void	setText(std::string const & text);
  virtual void	setColor(int, int, int);

  virtual int	getWidth();
  virtual int	getHeight();

private:
  #if (SFML_VERSION_MAJOR == 2)
  sf::Text			_str;
  #else
  sf::String		_str;
  #endif
  sf::Font			_font;
  sf::RenderWindow	*_window;
};
