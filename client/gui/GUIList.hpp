#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"

template <typename T>
class GUIList : public GUIElement {
public:
  GUIList(std::string const & font, ButtonSprite &left_arrow, ButtonSprite &middle_sprite, ButtonSprite &right_arrow, int x, int y)
    : GUIElement(x, y, left_arrow.getWidth() + middle_sprite.getWidth() + right_arrow.getWidth() + 10, middle_sprite.getHeight()),  _leftArrow(left_arrow), _middleSprite(middle_sprite), _rightArrow(right_arrow), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(0), _func(0)
  {
    this->_focusLabel = this->_labels.begin();
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIList(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &left_arrow, ButtonSprite &middle_sprite, ButtonSprite &right_arrow, int x, int y)
    : GUIElement(x, y, left_arrow.getWidth() + middle_sprite.getWidth() + right_arrow.getWidth() + 10, middle_sprite.getHeight()),  _leftArrow(left_arrow), _middleSprite(middle_sprite), _rightArrow(right_arrow), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func)
  {
    this->_focusLabel = this->_labels.begin();
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIList(T &instance, void (T::*func)(std::string const &), std::string const & font, ButtonSprite &left_arrow, ButtonSprite &middle_sprite, ButtonSprite &right_arrow, GUILayout *layout)
    : GUIElement(0, 0, left_arrow.getWidth() + middle_sprite.getWidth() + right_arrow.getWidth() + 10, middle_sprite.getHeight(), layout), _leftArrow(left_arrow), _middleSprite(middle_sprite), _rightArrow(right_arrow), _font(GameStateManager::get().getCurrentState().getFont(font)), _instance(&instance), _func(func)
  {
    this->_focusLabel = this->_labels.begin();
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUIList()
  {
    delete this->_font;
  }

  virtual void addLabel(std::string const &label)
  {
    this->_labels.push_back(label);
    if (this->_focusLabel == this->_labels.end())
      {
	this->_focusLabel = this->_labels.begin();
	(this->_instance->*(this->_func))(*(_focusLabel));
      }
  }

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left)
      {
	this->_leftArrow.updateState(ButtonSprite::CLICKED);
	this->EventLeft();
	if (this->_instance)
	  (this->_instance->*(this->_func))(*(_focusLabel));
	return (true);
      }
    else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right)
      {
	this->_rightArrow.updateState(ButtonSprite::CLICKED);
	this->EventRight();
	if (this->_instance)
	  (this->_instance->*(this->_func))(*(_focusLabel));
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Left)
      {
	if (this->_isFocused)
	  this->_leftArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_leftArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Right)
      {
	if (this->_isFocused)
	  this->_rightArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_rightArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    return (false);
  }

  virtual void focus()
  {
    this->_leftArrow.updateState(ButtonSprite::SELECTED);
    this->_middleSprite.updateState(ButtonSprite::SELECTED);
    this->_rightArrow.updateState(ButtonSprite::SELECTED);
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_leftArrow.updateState(ButtonSprite::DEFAULT);
    this->_middleSprite.updateState(ButtonSprite::DEFAULT);
    this->_rightArrow.updateState(ButtonSprite::DEFAULT);
    this->GUIElement::unfocus();
  }

  virtual void draw(double elapseTime)
  {
    this->_leftArrow.draw(this->_x, this->_y + (this->_middleSprite.getHeight() - this->_leftArrow.getHeight()) / 2, elapseTime);
    this->_middleSprite.draw(this->_x + this->_leftArrow.getWidth() + 5, this->_y, elapseTime);
    this->_rightArrow.draw(this->_x + this->_middleSprite.getWidth() + this->_leftArrow.getWidth() + 10, this->_y
			   + (this->_middleSprite.getHeight() - this->_rightArrow.getHeight()) / 2, elapseTime);
    if (this->_font)
      {
	this->_font->setText(*(this->_focusLabel));
	this->_font->draw(this->_x + this->_leftArrow.getWidth() + ((this->_middleSprite.getWidth() - this->_font->getWidth()) / 2),
			  this->_y + ((this->_middleSprite.getHeight() - this->_font->getHeight()) / 2) - 5, elapseTime);
      }
  }

  virtual void draw(int x, int y, double elapseTime)
  {
    this->_leftArrow.draw(x, y + (this->_middleSprite.getHeight() - this->_leftArrow.getHeight()) / 2, elapseTime);
    this->_middleSprite.draw(x + this->_leftArrow.getWidth() + 5, y, elapseTime);
    this->_rightArrow.draw(x + this->_middleSprite.getWidth() + this->_leftArrow.getWidth() + 10, y
			   + (this->_middleSprite.getHeight() - this->_rightArrow.getHeight()) / 2, elapseTime);
    if (this->_font)
      {
	this->_font->setText(*(this->_focusLabel));
	this->_font->draw(x + this->_leftArrow.getWidth() + ((this->_middleSprite.getWidth() - this->_font->getWidth()) / 2),
			  y + ((this->_middleSprite.getHeight() - this->_font->getHeight()) / 2) - 5, elapseTime);
      }
  }

  std::string const &	getText()
  {
    return (*(_focusLabel));
  }

private:
  void EventLeft()
  {
    if (!this->_labels.size())
      return ;
    if (this->_focusLabel == this->_labels.begin())
      this->_focusLabel = this->_labels.end();
    --this->_focusLabel;
  }

  void EventRight()
  {
    if (!this->_labels.size())
      return ;
    ++this->_focusLabel;
    if (this->_focusLabel == this->_labels.end())
      this->_focusLabel = this->_labels.begin();
  }

  ButtonSprite				_leftArrow;
  ButtonSprite				_middleSprite;
  ButtonSprite				_rightArrow;
  Font *				_font;
  T *					_instance;
  void					(T::*_func)(std::string const &);
  std::list<std::string>		_labels;
  std::list<std::string>::iterator	_focusLabel;
};
