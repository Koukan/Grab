#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

class SFMLSprite : public Sprite, public sf::Sprite
{
	public:
		SFMLSprite(double x = 0, double y = 0);
		virtual ~SFMLSprite();
		void			update(double elapsedTime);
		virtual void	setScale(float x, float y);
		virtual void	setSpeed(double rate);
		virtual void	setRepeat(bool repeat);
		virtual void	setPingpong(bool pingpong);
		virtual void	setUp(bool up);
		virtual void	setTranslate(int x, int y);
		virtual void	setGrid(uint32_t top, uint32_t left, uint32_t width,
								uint32_t height, uint32_t nbx, uint32_t nby,
								uint32_t spacex, uint32_t spacey);

		virtual void	draw(double elapsedTime = 0);
		virtual void	draw(int x, int y, double elapsedTime = 0);

		virtual int	getWidth() const;
		virtual int	getHeight() const;

	private:
		sf::RenderWindow			*_window;
		double						_frameRate;
		double						_lastTime;
		double						_currentTime;
		bool						_repeat;
		bool						_pingpong;
		bool						_up;
		uint32_t					_currentFrame;
		int							_tx;
		int							_ty;
		std::vector<sf::IntRect>	_rect;
};
