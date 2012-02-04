#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include "Font.hpp"

class SFMLFont : public CoreFont
{
public:
  SFMLFont(std::string const &fileName, unsigned int size);
  ~SFMLFont();

  virtual Resource	*clone() const;
  virtual void		draw(double elapsedTime = 0);
  virtual void		draw(int x, int y, double elapsedTime = 0);
  virtual void		setText(std::string const & text);
  virtual void		setColor(int, int, int);

  virtual int		getWidth() const;
  virtual int		getHeight() const;

private:
  #if (SFML_VERSION_MAJOR == 2)
  sf::Text			_str;
  #else
  sf::String		_str;
  #endif
  sf::Font			_font;
  sf::RenderWindow	*_window;
};
