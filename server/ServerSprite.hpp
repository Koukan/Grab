#pragma once

#include "Sprite.hpp"

class ServerSprite : public Core::Sprite
{
  public:
    ServerSprite();
    virtual ~ServerSprite();

	virtual Core::Resource	*clone() const;

	void					setWidth(int width);
	void					setHeight(int height);

	virtual int				getWidth() const;
	virtual int				getHeight() const;

  private:
	int			_width;
	int			_height;
};
