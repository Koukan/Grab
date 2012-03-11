#include "ServerSprite.hpp"

ServerSprite::ServerSprite()
{
}

ServerSprite::~ServerSprite()
{
}

Core::Resource	*ServerSprite::clone() const
{
	return new ServerSprite(*this);
}

void		ServerSprite::setWidth(int width)
{
	this->_width = width;
}

void		ServerSprite::setHeight(int height)
{
	this->_height = height;
}

int			ServerSprite::getWidth() const
{
	return this->_width;
}

int			ServerSprite::getHeight() const
{
	return this->_height;
}
