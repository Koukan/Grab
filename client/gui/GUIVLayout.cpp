#include "GUIVLayout.hpp"
#include "GameStateManager.hpp"

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements, std::string const &arrowUp, std::string const &arrowDown)
  : GUILayout(x, y, width, height, padding, layout, nbElements), _upArrow(GameStateManager::get().getCurrentState().getSprite(arrowUp)), _downArrow(GameStateManager::get().getCurrentState().getSprite(arrowDown))
{
}

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, int nbElements, std::string const &arrowUp, std::string const &arrowDown)
  : GUILayout(x, y, width, height, padding, nbElements), _upArrow(GameStateManager::get().getCurrentState().getSprite(arrowUp)), _downArrow(GameStateManager::get().getCurrentState().getSprite(arrowDown))
{
}

GUIVLayout::~GUIVLayout()
{
}

bool GUIVLayout::handleGUICommand(InputCommand const &command)
{
  if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Up)
    {
      this->prevElement();
      return (true);
    }
  else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Down)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::handleGUICommand(command));
}

void GUIVLayout::draw(double elapseTime)
{
  int x = this->_x;
  int y = this->_y;
  int nb = 0;

  if (this->_upArrow && this->_begin != this->_elements.begin())
    this->_upArrow->draw(x - this->_upArrow->getWidth() / 2, y - this->_upArrow->getHeight() - 5);
  std::list<GUIElement *>::iterator it = this->_begin;
  for (; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
      ++nb;
    }
  if (this->_downArrow && it != this->_elements.end())
    this->_downArrow->draw(x - this->_downArrow->getWidth() / 2, y + 5 - this->_padding);
}

void GUIVLayout::draw(int x, int y, double elapseTime)
{
  int nb = 0;

  if (this->_upArrow && this->_begin != this->_elements.begin())
    this->_upArrow->draw(x - this->_upArrow->getWidth() / 2, y - this->_upArrow->getHeight() - 5);
  std::list<GUIElement *>::iterator it = this->_begin;
  for (; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
      y += (*it)->getHeight() + this->_padding;
      ++nb;
    }
  if (this->_downArrow && it != this->_elements.end())
    this->_downArrow->draw(x - this->_downArrow->getWidth() / 2, y + 5 - this->_padding);
}
