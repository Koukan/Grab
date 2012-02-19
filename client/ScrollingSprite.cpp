#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"

ScrollingSprite::ScrollingSprite(int x, int y, int width, int height, ScrollingSprite::eDirection dir, double speed)
  : DrawableObject(x, y), _width(width), _height(height), _speed(speed), _offset(0), _current(0)
{
  if (dir == ScrollingSprite::HORIZONTAL)
    this->_scrolling = &ScrollingSprite::hScrolling;
  else
    this->_scrolling = &ScrollingSprite::vScrolling;
}

ScrollingSprite::~ScrollingSprite()
{
  for (std::vector<Core::Sprite *>::iterator it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
    delete *it;
}

void ScrollingSprite::pushSprite(std::string const &spriteName)
{
  Core::GameState &gameState = Core::GameStateManager::get().getCurrentState();

  Core::Sprite *tmp = gameState.getSprite(spriteName);
  if (!tmp)
	return ;
  this->_sprites.push_back(tmp);
}

void ScrollingSprite::draw(double elapseTime)
{
  if (!this->_sprites.empty())
  	(this->*(this->_scrolling))(static_cast<int>(elapseTime));
}

void ScrollingSprite::setSpeed(int speed)
{
  this->_speed = speed;
}

size_t ScrollingSprite::nextSprite(size_t i)
{
  if (i == this->_sprites.size() - 1)
    return (0);
  return (i + 1);
}

size_t ScrollingSprite::prevSprite(size_t i)
{
  if (i == 0)
	return (this->_sprites.size() - 1);
  return (i - 1);
}

void ScrollingSprite::hScrolling(int elapseTime)
{
  size_t	tmp = this->_current;
  int x2 = static_cast<int>(_offset);

  while (x2 < this->_width)
    {
      _sprites[tmp]->draw(static_cast<int>(x2 + this->_x), static_cast<int>(this->_y), elapseTime);
      x2 += _sprites[tmp]->getWidth();
      tmp = this->nextSprite(tmp);
    }
  this->_offset += this->_speed * elapseTime;
  if (this->_offset + _sprites[_current]->getWidth() < 0)
    {
      while (this->_offset + _sprites[_current]->getWidth() < 0)
	{
	  this->_offset += _sprites[_current]->getWidth();
	  _current = this->nextSprite(_current);
	}
    }
  else if (this->_offset > 0)
    {
      while (this->_offset > 0)
	{
	  this->_offset -= _sprites[_current]->getWidth();
	  _current = this->prevSprite(_current);
	}
    }
}

void ScrollingSprite::vScrolling(int elapseTime)
{
  size_t	tmp = this->_current;
  int y2 = static_cast<int>(this->_offset);

  while (y2 < this->_height)
    {
      _sprites[tmp]->draw(static_cast<int>(this->_x), static_cast<int>(this->_y + y2), elapseTime);
      y2 += _sprites[tmp]->getHeight();
	  tmp = this->nextSprite(tmp);
    }
  this->_offset += this->_speed * elapseTime;
  if (this->_offset + _sprites[_current]->getHeight() < 0)
    {
      while (this->_offset + _sprites[_current]->getHeight() < 0)
	{
	  this->_offset += _sprites[_current]->getHeight();
	  _current = this->nextSprite(_current);
	}
    }
  else if (this->_offset > 0)
    {
      while (this->_offset > 0)
	{
	  this->_offset -= _sprites[_current]->getHeight();
	  _current = this->prevSprite(_current);
	}
    }
}
