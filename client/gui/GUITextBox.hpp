#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"
#include "GUITextBoxCharMap.hpp"
#include "GameStateManager.hpp"

template <typename T>
class GUITextBox : public Core::GUIElement {
public:
  GUITextBox(std::string const & font, Core::ButtonSprite &sprite, int x, int y, int maxChar = 100, std::string const &text = "")
    : Core::GUIElement(x, y, sprite.getWidth(), sprite.getHeight()), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _instance(0), _func(0), _maxChar(maxChar), _text(text)
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUITextBox(std::string const & font, Core::ButtonSprite &sprite, Core::GUILayout *layout, int maxChar = 100, std::string const &text = "")
    : Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _instance(0), _func(0), _maxChar(maxChar), _text(text)
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUITextBox(T &instance, void (T::*func)(std::string const &), std::string const & font, Core::ButtonSprite &sprite, int x, int y, int maxChar = 100, std::string const &text = "")
    : Core::GUIElement(x, y, sprite.getWidth(), sprite.getHeight()), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func), _maxChar(maxChar), _text(text)
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUITextBox(T &instance, void (T::*func)(std::string const &), std::string const & font, Core::ButtonSprite &sprite, Core::GUILayout *layout, int maxChar = 100, std::string const &text = "")
    : Core::GUIElement(0, 0, sprite.getWidth(), sprite.getHeight(), layout), _sprite(sprite), _font(Core::GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func), _maxChar(maxChar), _text(text)
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUITextBox()
  {
    delete this->_font;
  }

  virtual bool handleGUICommand(Core::GUICommand const &command)
  {
	  if (command.buttonAction == Core::GUICommand::RELEASED &&
		  command.type == Core::GUICommand::ACTION &&
		  command.action == Core::GUICommand::BACK)
		  return (true);
    if (command.buttonAction == Core::GUICommand::PRESSED && ((command.type == Core::GUICommand::KEY && command.key == Core::Keyboard::Back) ||
		(command.type == Core::GUICommand::ACTION && command.action == Core::GUICommand::BACK)))
      {
	this->_text = this->_text.substr(0, this->_text.size() - 1);
	if (this->_instance)
	  (this->_instance->*(this->_func))(this->_text);
	return true;
      }
    if (command.type == Core::GUICommand::KEY && command.buttonAction == Core::GUICommand::PRESSED && GUITextBoxCharMap.find(command.key) != GUITextBoxCharMap.end() && this->_maxChar > this->_text.size())
      {
	this->_text += GUITextBoxCharMap[command.key];
	if (this->_instance)
	  (this->_instance->*(this->_func))(this->_text);
	return true;
      }
    return false;
  }

  virtual void focus()
  {
    this->_sprite.updateState(Core::ButtonSprite::SELECTED);
    this->Core::GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_sprite.updateState(Core::ButtonSprite::DEFAULT);
    this->Core::GUIElement::unfocus();
  }

  virtual void draw(double elapseTime)
  {
    this->_sprite.draw(static_cast<int>(this->_x), static_cast<int>(this->_y), elapseTime);
    if (this->_font)
      {
	this->_font->setText(this->_text);
	this->_font->draw(static_cast<int>(this->_x + ((this->_sprite.getWidth() - this->_font->getWidth()) / 2)),
			  static_cast<int>(this->_y + ((this->_sprite.getHeight() - this->_font->getHeight()) / 2) - 5), elapseTime);
      }
  }

  virtual void draw(int x, int y, double elapseTime)
  {
    this->_sprite.draw(x, y, elapseTime);
    if (this->_font)
      {
	this->_font->setText(this->_text);
	this->_font->draw(x + ((this->_sprite.getWidth() - this->_font->getWidth()) / 2),
			  y + ((this->_sprite.getHeight() - this->_font->getHeight()) / 2) - 5, elapseTime);
      }
  }

  virtual std::string const &	getText()
  {
    return (this->_text);
  }

private:
  Core::ButtonSprite				_sprite;
  Core::CoreFont *				_font;
  T *					_instance;
  void					(T::*_func)(std::string const &);
  unsigned int				_maxChar;
  std::string				_text;
};
