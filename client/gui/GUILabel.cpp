#include "GUILabel.hpp"

GUILabel::GUILabel(std::string const &name, std::string const &font, std::string const &sprite, int x, int y)
  : GUIElement(x, y, 0, 0), _sprite(GameStateManager::get().getCurrentState().getSprite(sprite)), _font(GameStateManager::get().getCurrentState().getFont(font))
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

GUILabel::GUILabel(std::string const &name, std::string const &font, std::string const &sprite, GUILayout *layout)
  : GUIElement(0, 0, 0, 0, layout), _sprite(GameStateManager::get().getCurrentState().getSprite(sprite)), _font(GameStateManager::get().getCurrentState().getFont(font))
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

bool	GUILabel::handleGUICommand(InputCommand const &)
{
  return (false);
}

void	GUILabel::draw(double elapseTime)
{
  if (this->_sprite)
    this->_sprite->draw(this->_x, this->_y, elapseTime);
  if (this->_font)
    {
      this->_font->draw(this->_x + (this->_width - this->_font->getWidth()) / 2,
			this->_y + (this->_height - this->_font->getHeight()) / 2 - 5, elapseTime);
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
