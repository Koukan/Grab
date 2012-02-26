#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include "Font.hpp"
#include "GameStateManager.hpp"
#include <string>

template <typename T>
class GUIButton : public Core::GUIElement
{
public:
  GUIButton(T &instance, void (T::*func)(), std::string const &name, std::string const &font, Core::ButtonSprite const &sprite, int x, int y, Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
    : Core::GUIElement(x, y, sprite.getWidth(), sprite.getHeight(), playerType), _instance(&instance), _func(func), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _pressed(false), _name(name)
  {
    if (this->_font)
      this->_font->setText(name);
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIButton(T &instance, void (T::*func)(), std::string const &name, std::string const &font, Core::ButtonSprite const &sprite, Core::GUILayout *layout, Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
    : Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout, playerType), _instance(&instance), _func(func), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _name(name)
  {
    if (this->_font)
      this->_font->setText(name);
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUIButton()
  {
    delete this->_font;
  }

  virtual bool handleGUICommand(Core::GUICommand const &command)
  {
    if (command.type == Core::GUICommand::ACTION && command.buttonAction == Core::GUICommand::PRESSED && command.action == Core::GUICommand::SELECT
			/*command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Return*/)
      {
	this->_sprite.updateState(Core::ButtonSprite::CLICKED);
	this->_pressed = true;
	return (true);
      }
    else if (command.type == Core::GUICommand::ACTION && command.buttonAction == Core::GUICommand::RELEASED && command.action == Core::GUICommand::SELECT
		/*command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Return*/)
      {
	if (this->_isFocused)
	  this->_sprite.updateState(Core::ButtonSprite::SELECTED);
	else
	  this->_sprite.updateState(Core::ButtonSprite::DEFAULT);
	if (this->_pressed)
	{
		(this->_instance->*(this->_func))();
		this->_pressed = false;
	}
	return (true);
      }
    return (false);
  }

  virtual void	draw(double elapseTime)
  {
      this->_sprite.draw(static_cast<int>(this->_x), static_cast<int>(this->_y), elapseTime);
    if (this->_font)
      {
	this->_font->draw(static_cast<int>(this->_x + (this->_width - this->_font->getWidth()) / 2),
			  static_cast<int>(this->_y + (this->_height - this->_font->getHeight()) / 2 - 5), elapseTime);
      }
  }

  virtual void	draw(int x, int y, double elapseTime)
  {
      this->_sprite.draw(x, y, elapseTime);
    if (this->_font)
      {
	this->_font->draw(x + (this->_width - this->_font->getWidth()) / 2 - 10,
			  y + (this->_height - this->_font->getHeight()) / 2 + 2, elapseTime);
      }
  }

  virtual void focus()
  {
    this->_sprite.updateState(Core::ButtonSprite::SELECTED);
    this->Core::GUIElement::focus();
  }

  virtual void unfocus()
  {
	this->_pressed = false;
	this->_sprite.updateState(Core::ButtonSprite::DEFAULT);
	this->Core::GUIElement::unfocus();
  }

  Core::CoreFont *getFont() const
  {
    return (this->_font);
  }

  void setFont(Core::CoreFont *font)
  {
    this->_font = font;
  }

  std::string const &getName() const
  {
    return _name;
  }

protected:
  T *_instance;
  void (T::*_func)();
  Core::ButtonSprite _sprite;
  Core::CoreFont *_font;
  bool	_pressed;
  std::string const _name;
};
