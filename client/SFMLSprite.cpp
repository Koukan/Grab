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
		if (nb >= size)
			nb = size - 1;
		this->_currentFrame = nb;
		#if (SFML_VERSION_MAJOR == 2)
		this->SetTextureRect(this->_rect[this->_currentFrame]);
		#else
		this->SetSubRect(this->_rect[this->_currentFrame]);
		#endif
	}
}

void		SFMLSprite::setScale(float x, float y)
{
	this->SetScale(x, y);
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
		this->SetTextureRect(this->_rect[this->_currentFrame]);
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
	this->SetPosition(static_cast<float>(this->_x + this->_tx * this->GetScale().x), static_cast<float>(this->_y + this->_ty * this->GetScale().y));
	//RendererManager::get().getShader().SetParameter("rt_w", this->getWidth());
	//RendererManager::get().getShader().SetParameter("rt_h", this->getHeight());
	//sf::RenderStates states;
	//states.Shader = &RendererManager::get().getShader();
	this->_window->Draw(*this/*, states*/);
}

void		SFMLSprite::draw(int x, int y, double elapsedTime)
{
	this->update(elapsedTime);
	this->SetPosition(x + this->_tx * this->GetScale().x, y + this->_ty * this->GetScale().y);
	this->_window->Draw(*this);
}

int	SFMLSprite::getWidth() const
{
	#if (SFML_VERSION_MAJOR == 2)
		return (static_cast<int>(this->GetGlobalBounds().Width));
	#else
		return (static_cast<int>(this->GetSize().x));
	#endif
}

int	SFMLSprite::getHeight() const
{
	#if (SFML_VERSION_MAJOR == 2)
		return (static_cast<int>(this->GetGlobalBounds().Height));
	#else
		return (static_cast<int>(this->GetSize().y));
	#endif
}

void	SFMLSprite::setTransparency(float transparency)
{
  sf::Color base = this->GetColor();

  base.a = transparency * 255;
  this->SetColor(base);
}

void	SFMLSprite::setColor(int r, int g, int b)
{
  sf::Color base = this->GetColor();

  base.r = r;
  base.g = g;
  base.b = b;
  this->SetColor(base);
}

int		SFMLSprite::getColor(int i) const
{
  sf::Color base = this->GetColor();

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
