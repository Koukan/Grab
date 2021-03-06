#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

class SFMLSprite : public Core::Sprite, public sf::Sprite
{
	public:
		SFMLSprite(double x = 0, double y = 0);
		virtual ~SFMLSprite();
		void				update(double elapsedTime);
  virtual Core::Resource	*clone() const;
		virtual void		setScale(float x, float y);
		virtual void		setSpeed(double rate);
		virtual void		setRepeat(bool repeat);
		virtual void		setPingpong(bool pingpong);
		virtual void		setUp(bool up);
		virtual void		setTranslate(int x, int y);
		virtual void		setGrid(uint32_t top, uint32_t left, uint32_t width,
								uint32_t height, uint32_t nbx, uint32_t nby,
								uint32_t spacex, uint32_t spacey);
		virtual void		setBack(bool val);
		virtual void		setVanish(bool vanish);

		virtual void		setTransparency(float transparency);
		virtual void		setColor(int r, int g, int b);
		virtual void		setColor(Color const & color);
		virtual void		setRotation(double angle);
		virtual void		rotate(double angle);
		virtual void		setCenter(double x, double y);
		virtual void		setCenter();
		virtual void		draw(double elapsedTime = 0);
		virtual void		draw(int x, int y, double elapsedTime = 0);

		virtual int			getWidth() const;
		virtual int			getHeight() const;
		int					getColor(int i) const;
		virtual double		getRotation() const;
		virtual bool		isFinished() const;

private:
		sf::RenderWindow			*_window;
		double						_frameRate;
		double						_currentTime;
		bool						_repeat;
		bool						_pingpong;
		bool						_up;
		uint32_t					_currentFrame;
		int							_tx;
		int							_ty;
		std::vector<sf::IntRect>	_rect;
		bool						_vanish;
		bool						_finished;
};
