#include "GUILabel.hpp"

GUILabel::GUILabel(std::string const &name, std::string const &font, std::string const &sprite, int x, int y)
  : Core::GUIElement(x, y, 0, 0), _sprite(Core::GameStateManager::get().getCurrentState().getSprite(sprite)), _font(Core::GameStateManager::get().getCurrentState().getFont(font))
{
  if (this->_font)
    this->_font->setText(name);
  if (this->_sprite)
    {
      this->setWidth(this->_sprite->getWidth());
      this->setHeight(this->_sprite->getHeight());
    }
  else if (this->_font)
    {
      this->setWidth(this->_font->getWidth());
      this->setHeight(this->_font->getHeight());
    }
  this->setEnable(false);
}

GUILabel::GUILabel(std::string const &name, std::string const &font, std::string const &sprite, Core::GUILayout *layout)
  : Core::GUIElement(0, 0, 0, 0, layout), _sprite(Core::GameStateManager::get().getCurrentState().getSprite(sprite)), _font(Core::GameStateManager::get().getCurrentState().getFont(font))
{
  if (this->_font)
    this->_font->setText(name);
  if (this->_sprite)
    {
      this->setWidth(this->_sprite->getWidth());
      this->setHeight(this->_sprite->getHeight());
    }
  else if (this->_font)
    {
      this->setWidth(this->_font->getWidth());
      this->setHeight(this->_font->getHeight());
    }
  this->setEnable(false);
}

GUILabel::~GUILabel()
{
  delete this->_font;
  delete this->_sprite;
}

bool	GUILabel::handleGUICommand(Core::GUICommand const &)
{
  return (false);
}

void	GUILabel::draw(double elapseTime)
{
  if (this->_sprite)
    this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y), elapseTime);
  if (this->_font)
    {
      this->_font->draw(static_cast<int>(this->_x + (this->_width - this->_font->getWidth()) / 2),
			static_cast<int>(this->_y + (this->_height - this->_font->getHeight()) / 2 - 5), elapseTime);
    }
}

void	GUILabel::draw(int x, int y, double elapseTime)
{
  if (this->_sprite)
    this->_sprite->draw(x, y, elapseTime);
  if (this->_font)
    {
      this->_font->draw(x + (this->_width - this->_font->getWidth()) / 2,
			y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
    }
}

void	GUILabel::setText(std::string const &str)
{
  if (this->_font)
    this->_font->setText(str);
}

void	GUILabel::setColor(int r, int g, int b, int t)
{
	if (this->_font)
	{
		this->_font->setColor(r, g, b);
		this->_font->setTransparency(t);
	}
}
