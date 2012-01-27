#include <iostream>
#include "SFMLSprite.hpp"
#include "RendererManager.hpp"

SFMLSprite::SFMLSprite(double x, double y)
	: _window(RendererManager::get().getWindow()), _frameRate(-1),
	  _lastTime(0), _currentTime(0), _repeat(false), _pingpong(false),
	  _up(true), _currentFrame(0), _tx(0), _ty(0)
{
	this->setX(x);
	this->setY(y);
}

SFMLSprite::~SFMLSprite()
{
}

void		SFMLSprite::update(double elapsedTime)
{
	if (this->_frameRate == -1 || elapsedTime == 0)
		return ;
	unsigned int	size = this->_rect.size();
	if (size < 2 || (!this->_pingpong && !this->_repeat &&
					 this->_currentFrame >= (size - 1)))
		return ;
	this->_currentTime += elapsedTime;
	double		tmp = this->_currentTime - this->_lastTime;
	double		time = this->_frameRate / size;
	uint32_t	nbr;
	unsigned int			nb = this->_currentFrame;
	if (tmp > time)
	{
		nbr = static_cast<int>(tmp) / static_cast<int>(time);
		this->_lastTime += time * nbr;
		if (this->_pingpong)
		{
			while (nbr)
			{
				nb += (this->_up) ? 1 : -1;
				if (nb == size - 1)
					this->_up = false;
				else if (nb == 0)
					this->_up = true;
				nbr--;
			}
		}
		else if (this->_repeat)
			nb = (nb + nbr) % (size);
		else
		{
			nb = nb + nbr;
			if (nb > size)
				nb = size;
		}
		this->_currentFrame = nb;
		this->SetSubRect(this->_rect[this->_currentFrame]);
		//this->SetTextureRect(this->_rect[this->_currentFrame]);
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
	//this->SetTextureRect(this->_rect[0/*this->_currentFrame*/]);
	if (!this->_rect.empty())
		this->SetSubRect(this->_rect[0/*this->_currentFrame*/]);
}

void		SFMLSprite::draw(double elapsedTime)
{
	this->update(elapsedTime);
	this->SetPosition(this->_x + this->_tx * this->GetScale().x, this->_y + this->_ty * this->GetScale().y);
	this->_window->Draw(*this);
}

void		SFMLSprite::draw(int x, int y, double elapsedTime)
{
	this->update(elapsedTime);
	this->SetPosition(x + this->_tx * this->GetScale().x, y + this->_ty * this->GetScale().y);
	this->_window->Draw(*this);
}

int	SFMLSprite::getWidth() const
{
  return (this->GetSize().x);
}

int	SFMLSprite::getHeight() const
{
  return (this->GetSize().y);
}
