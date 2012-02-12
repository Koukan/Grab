#include "GUIBindButton.hpp"

GUIBindButton::GUIBindButton(int playerNb, std::string const &font, ButtonSprite const &sprite, int x, int y)
  : GUIButton(*this, &GUIBindButton::pushButton, "bind controls", font, sprite, x, y), _playerNb(playerNb)
{
  this->_bindingList.push_back("\"fire\"");
  this->_bindingList.push_back("\"grab\"");
  this->_bindingList.push_back("\"etc.\"");
  this->_iterator = this->_bindingList.end();
}

GUIBindButton::GUIBindButton(int playerNb, std::string const &font, ButtonSprite const &sprite, GUILayout *layout)
  : GUIButton(*this, &GUIBindButton::pushButton, "bind controls", font, sprite, layout), _playerNb(playerNb)
{
  this->_bindingList.push_back("\"fire\"");
  this->_bindingList.push_back("\"grab\"");
  this->_bindingList.push_back("\"etc.\"");
  this->_iterator = this->_bindingList.end();
}

GUIBindButton::~GUIBindButton()
{
}

bool GUIBindButton::handleGUICommand(InputCommand const &command)
{
  if (this->_iterator != this->_bindingList.end() && command.Type == InputCommand::KeyReleased)
    {

      // bind control

      ++this->_iterator;
      if (this->_font)
	{
	  if (this->_iterator != this->_bindingList.end())
	    this->_font->setText(*this->_iterator);
	  else
	    this->_font->setText("bind controls");
	}
      return (true);
    }
  return (this->GUIButton::handleGUICommand(command));
}

void GUIBindButton::pushButton()
{
  this->_iterator = this->_bindingList.begin();
  if (this->_font)
    this->_font->setText(*this->_iterator);
}
