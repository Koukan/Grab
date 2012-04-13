#include <iostream>
#include "SFMLSprite.hpp"
#include "RendererManager.hpp"

SFMLSprite::SFMLSprite(double x, double y)
	: _window(RendererManager::get().getWindow()), _frameRate(-1),
	  _currentTime(0), _repeat(false), _pingpong(false),
	  _up(true), _currentFrame(0), _tx(0), _ty(0), _vanish(false), _finished(false)
{
  this->_x = x;
  this->_y = y;
}

SFMLSprite::~SFMLSprite()
{
}

Core::Resource	*SFMLSprite::clone() const
{
	return new SFMLSprite(*this);
}

void		SFMLSprite::update(double elapsedTime)
{
	if (this->_frameRate == -1 || elapsedTime == 0)
		return ;
	unsigned int	size = this->_rect.size();
	if (size < 2 || (!this->_pingpong && !this->_repeat && this->_up &&
					 this->_currentFrame >= (size - 1)) ||
					(!this->_pingpong && !this->_repeat && !this->_up &&
					this->_currentFrame == 0))
	{
		if (this->_vanish)
			this->erase();
		if (size > 1)
			this->_finished = true;
		return ;
	}
	this->_currentTime += elapsedTime;
	double			time = this->_frameRate / size;
	int				nb = this->_currentFrame;
	if (this->_currentTime > time)
	{
		uint32_t nbr = static_cast<int>(this->_currentTime) / static_cast<int>(time);
		this->_currentTime -= time * nbr;
		if (this->_pingpong)
		{
			while (nbr)
			{
				nb += (this->_up) ? 1 : -1;
				if (static_cast<uint32_t>(nb) == size - 1)
					this->_up = false;
				else if (nb <= 0)
					this->_up = true;
				nbr--;
			}
		}
		else if (this->_repeat)
			nb = (nb + nbr) % (size);
		else if (this->_up)
			nb += nbr;
		else
			nb -= nbr;
		if (static_cast<uint32_t>(nb) >= size)
			nb = size - 1;
		this->_currentFrame = nb;
		#if (SFML_VERSION_MAJOR == 2)
		this->setTextureRect(this->_rect[this->_currentFrame]);
		#else
		this->SetSubRect(this->_rect[this->_currentFrame]);
		#endif
	}
}

void		SFMLSprite::setScale(float x, float y)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::Transformable::setScale(x, y);
	#else
	this->SetScale(x, y);
	#endif
	this->setCenter();
}

void		SFMLSprite::setSpeed(double rate)
{
	this->_frameRate = rate;
}

void		SFMLSprite::setRepeat(bool repeat)
{
	this->_repeat = repeat;
}

void		SFMLSprite::setPingpong(bool pingpong)
{
	this->_pingpong = pingpong;
}

void		SFMLSprite::setUp(bool up)
{
	this->_up = up;
}

void		SFMLSprite::setTranslate(int x, int y)
{
	this->_tx = x;
	this->_ty = y;
	this->setCenter();
}

void		SFMLSprite::setGrid(uint32_t left, uint32_t top, uint32_t width,
								uint32_t height, uint32_t nbx, uint32_t nby,
								uint32_t spacex, uint32_t spacey)
{
	uint32_t		nb;
	uint32_t		x;

	_rect.clear();
	for (; nby != 0; nby--)
	{
		x = left;
		for (nb = nbx; nb != 0; nb--)
		{
			#if SFML_VERSION_MAJOR == 2
			this->_rect.push_back(sf::IntRect(x, top, width, height));
			#else
			this->_rect.push_back(sf::IntRect(x, top, x + width, top + height));
			#endif
			x += spacex + width;
		}
		top += spacey + height;
	}
#if (SFML_VERSION_MAJOR == 2)
	this->setCenter(width / this->getScale().x / 2, height / this->getScale().y / 2);
#else
	this->setCenter(width / this->GetScale().x / 2, height / this->GetScale().y / 2);
#endif
}

void		SFMLSprite::setBack(bool val)
{
	if (val)
	{
		this->_currentFrame = this->_rect.size() - 1;
		this->_up = false;
	}
	else
	{
		this->_currentFrame = 0;
		this->_up = true;
	}
	if (!this->_rect.empty())
	{
		#if (SFML_VERSION_MAJOR == 2)
		this->setTextureRect(this->_rect[this->_currentFrame]);
		#else
		this->SetSubRect(this->_rect[this->_currentFrame]);
		#endif
	}
}

void		SFMLSprite::setVanish(bool vanish)
{
	this->_vanish = vanish;
}

void		SFMLSprite::draw(double elapsedTime)
{
	this->update(elapsedTime);
#if (SFML_VERSION_MAJOR == 2)
	this->sf::Transformable::setPosition(static_cast<float>(this->_x + this->_tx * this->getScale().x), static_cast<float>(this->_y + this->_ty * this->getScale().y));
	this->_window->draw(*this/*, states*/);
#else
	this->SetPosition(static_cast<float>(this->_x + this->_tx * this->GetScale().x), static_cast<float>(this->_y + this->_ty * this->GetScale().y));
	this->_window->Draw(*this/*, states*/);
#endif
}

void		SFMLSprite::draw(int x, int y, double elapsedTime)
{
	this->update(elapsedTime);
#if (SFML_VERSION_MAJOR == 2)
	this->sf::Transformable::setPosition(x + this->_tx * this->getScale().x, y + this->_ty * this->getScale().y);
	this->_window->draw(*this);
#else
	this->SetPosition(x + this->_tx * this->GetScale().x, y + this->_ty * this->GetScale().y);
	this->_window->Draw(*this);
#endif
}

int	SFMLSprite::getWidth() const
{
	#if (SFML_VERSION_MAJOR == 2)
		return (static_cast<int>(this->getGlobalBounds().width));
	#else
		return (static_cast<int>(this->GetSize().x));
	#endif
}

int	SFMLSprite::getHeight() const
{
	#if (SFML_VERSION_MAJOR == 2)
		return (static_cast<int>(this->getGlobalBounds().height));
	#else
		return (static_cast<int>(this->GetSize().y));
	#endif
}

void	SFMLSprite::setTransparency(float transparency)
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->sf::Sprite::getColor();
  #else
  sf::Color base = this->GetColor();
  #endif

  base.a = static_cast<sf::Uint8>(transparency * 255);
  #if (SFML_VERSION_MAJOR == 2)
  this->sf::Sprite::setColor(base);
  #else
  this->SetColor(base);
  #endif
}

void	SFMLSprite::setColor(int r, int g, int b)
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->sf::Sprite::getColor();
  #else
  sf::Color base = this->GetColor();
  #endif

  base.r = r;
  base.g = g;
  base.b = b;
  #if (SFML_VERSION_MAJOR == 2)
  this->sf::Sprite::setColor(base);
  #else
  this->SetColor(base);
  #endif
}

void	SFMLSprite::setRotation(double angle)
{
	#if (SFML_VERSION_MAJOR == 2)
		this->sf::Transformable::setRotation(static_cast<float>(-angle));
	#else
		this->SetRotation(static_cast<float>(angle));
	#endif	
}

void	SFMLSprite::setCenter(double x, double y)
{
	#if (SFML_VERSION_MAJOR == 2)
		this->setOrigin(x, y);
	#else
		this->SetCenter(x, y);
	#endif	
}

void	SFMLSprite::setCenter()
{
	#if (SFML_VERSION_MAJOR == 2)
	this->setCenter(this->getWidth() / this->getScale().x / 2, this->getHeight() / this->getScale().y / 2);
	#else
	this->setCenter(this->getWidth() / this->GetScale().x / 2, this->getHeight() / this->GetScale().y / 2);
	#endif
}

void	SFMLSprite::rotate(double angle)
{
	#if (SFML_VERSION_MAJOR == 2)
	this->sf::Transformable::rotate(static_cast<float>(angle));
	#else
	this->Rotate(static_cast<float>(angle));
	#endif
}

int		SFMLSprite::getColor(int i) const
{
  #if (SFML_VERSION_MAJOR == 2)
  sf::Color base = this->sf::Sprite::getColor();
  #else
  sf::Color base = this->GetColor();
  #endif
  if (i == 0)
	  return (base.r);
  else if (i == 1)
	  return (base.g);
  return (base.b);
}

bool		SFMLSprite::isFinished() const
{
	return (this->_finished);
}

double	SFMLSprite::getRotation() const
{
	#if (SFML_VERSION_MAJOR == 2)
	return this->sf::Transformable::getRotation();
	#else
	return this->GetRotation();
	#endif
}
