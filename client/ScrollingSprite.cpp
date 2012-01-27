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
  for (std::vector<Sprite *>::iterator it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
    delete *it;
}

void ScrollingSprite::pushSprite(std::string const &spriteName)
{
  GameState &gameState = GameStateManager::get().getCurrentState();

  Sprite *tmp = gameState.getSprite(spriteName);
  if (!tmp)
	return ;
  this->_sprites.push_back(tmp);
}

void ScrollingSprite::draw(double elapseTime)
{
  if (!this->_sprites.empty())
  	(this->*(this->_scrolling))(elapseTime);
}

void ScrollingSprite::setSpeed(int speed)
{
  this->_speed = speed;
}

Sprite *ScrollingSprite::nextSprite()
{
  if (_current == this->_sprites.size() - 1)
    _current = 0;
  else
	_current++;
  return (_sprites[this->_current]);
}

Sprite *ScrollingSprite::prevSprite()
{
  if (_current == 0)
	_current = this->_sprites.size() - 1;
  else
	_current--;
  return (_sprites[this->_current]);
}

void ScrollingSprite::hScrolling(int elapseTime)
{
  Sprite	*sprite = _sprites[this->_current];
  int x2 = _offset;

  while (x2 < this->_width)
    {
      sprite->draw(x2 + this->_x, this->_y, elapseTime);
      sprite = this->nextSprite();
      x2 += sprite->getWidth();
    }
  this->_offset += this->_speed * elapseTime;
  if (this->_offset + sprite->getWidth() < 0)
    {
      while (this->_offset + sprite->getWidth() < 0)
	{
	  sprite = this->nextSprite();
	  this->_offset += sprite->getWidth();
	}
    }
  else if (this->_offset > 0)
    {
      while (this->_offset > 0)
	{
	  sprite = this->prevSprite();
	  this->_offset -= sprite->getWidth();
	}
    }
}

void ScrollingSprite::vScrolling(int elapseTime)
{
  Sprite	*sprite = _sprites[this->_current];
  int y2 = this->_offset;

  while (y2 < this->_height)
    {
      sprite->draw(this->_x, this->_y + y2, elapseTime);
	  sprite = this->nextSprite();
      y2 += sprite->getHeight();
    }
  this->_offset += this->_speed * elapseTime;
  if (this->_offset + sprite->getHeight() < 0)
    {
      while (this->_offset + sprite->getHeight() < 0)
	{
	  sprite = this->nextSprite();
	  this->_offset += sprite->getHeight();
	}
    }
  else if (this->_offset > 0)
    {
      while (this->_offset > 0)
	{
	  sprite = this->prevSprite();
	  this->_offset -= sprite->getHeight();
	}
    }
}
