#pragma once

#include "DrawableObject.hpp"
#include "Sprite.hpp"
#include <vector>
#include <string>

class ScrollingSprite : public Core::DrawableObject
{
public:
  enum eDirection
    {
      HORIZONTAL,
      VERTICAL
    };

  ScrollingSprite(int x, int y, int width, int height, ScrollingSprite::eDirection dir, double speed = 0);
  ~ScrollingSprite();

  void pushSprite(std::string const &spriteName);
  void draw(double elapseTime);
  void setSpeed(int speed);

private:
  int		_width;
  int		_height;
  double	_speed;
  double	_offset;

  std::vector<Core::Sprite *> _sprites;
  size_t				_current;
  void (ScrollingSprite::*_scrolling)(int elapseTime);

  void hScrolling(int elapseTime);
  void vScrolling(int elapseTime);
  size_t nextSprite(size_t i);
  size_t prevSprite(size_t i);
};
