#include "GUIBindButton.hpp"

GUIBindButton::GUIBindButton(int playerNb, std::string const &font, Core::ButtonSprite const &sprite, int x, int y)
  : GUIButton(*this, &GUIBindButton::pushButton, "bind controls", font, sprite, x, y), _playerNb(playerNb)
{
  this->_bindingList.push_back("\"fire\"");
  this->_bindingList.push_back("\"grab1\"");
  this->_bindingList.push_back("\"grab2\"");
  this->_bindingList.push_back("\"grab3\"");
  this->_bindingList.push_back("\"special power\"");
  this->_bindingList.push_back("\"etc.\"");
  this->_iterator = this->_bindingList.end();
}

GUIBindButton::GUIBindButton(int playerNb, std::string const &font, Core::ButtonSprite const &sprite, Core::GUILayout *layout)
  : GUIButton(*this, &GUIBindButton::pushButton, "bind controls", font, sprite, layout), _playerNb(playerNb)
{
  this->_bindingList.push_back("\"fire\"");
  this->_bindingList.push_back("\"grab1\"");
  this->_bindingList.push_back("\"grab2\"");
  this->_bindingList.push_back("\"grab3\"");
  this->_bindingList.push_back("\"special power\"");
  this->_bindingList.push_back("\"etc.\"");
  this->_iterator = this->_bindingList.end();
}

GUIBindButton::~GUIBindButton()
{
}

bool GUIBindButton::handleGUICommand(Core::GUICommand const &command)
{
/*  if (this->_iterator != this->_bindingList.end() && command.Type == InputCommand::KeyReleased)
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
*/
  return (this->GUIButton::handleGUICommand(command));
}

void GUIBindButton::pushButton()
{
  this->_iterator = this->_bindingList.begin();
  if (this->_font)
    this->_font->setText(*this->_iterator);
}
