#include "GUIHLayout.hpp"

GUIHLayout::GUIHLayout(int x, int y, int width, int height, int padding, Core::GUILayout *layout, int nbElements,
	  Core::GUICommand::PlayerType playerType)
  : Core::GUILayout(x, y, width, height, padding, layout, nbElements, playerType)
{
}

GUIHLayout::GUIHLayout(int x, int y, int width, int height, int padding, int nbElements,
	  Core::GUICommand::PlayerType playerType)
  : Core::GUILayout(x, y, width, height, padding, nbElements, playerType)
{
}

GUIHLayout::~GUIHLayout()
{
}

bool GUIHLayout::handleGUICommand(Core::GUICommand const &command)
{
  if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::LEFT /*command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left*/)
    {
      this->prevElement();
      return (true);
    }
  else if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::RIGHT /*command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right*/)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::catchGUICommand(command));
}

void GUIHLayout::draw(double elapseTime)
{
  int x = static_cast<int>(this->_x);
  int y = static_cast<int>(this->_y);
  int nb = 0;

  for (std::list<Core::GUIElement *>::iterator it = this->_begin; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x, y - (*it)->getHeight() / 2, elapseTime);
      x += (*it)->getWidth() + this->_padding;
      ++nb;
    }
}

void GUIHLayout::draw(int x, int y, double elapseTime)
{
  int nb = 0;

  for (std::list<Core::GUIElement *>::iterator it = this->_begin; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x, y - (*it)->getHeight() / 2, elapseTime);
      x += (*it)->getWidth() + this->_padding;
      ++nb;
    }
}
