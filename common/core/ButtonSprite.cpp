#include "ButtonSprite.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

ButtonSprite::ButtonSprite(std::string const &buttonSprite,
			   std::string const &buttonSelectedSprite,
			   std::string const &buttonClickedSprite)
  : _defaultName(buttonSprite), _selected(buttonSelectedSprite), _clicked(buttonClickedSprite), _state(ButtonSprite::DEFAULT)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());

  this->_defaultSprite = gameState->getSprite(buttonSprite);
  this->_selectedSprite = gameState->getSprite(buttonSelectedSprite);
  this->_clickedSprite = gameState->getSprite(buttonClickedSprite);

  gameState->getGUI().registerButtonSprite(*this);
}

ButtonSprite::~ButtonSprite()
{
  delete this->_defaultSprite;
  delete this->_selectedSprite;
  delete this->_clickedSprite;
}

ButtonSprite::ButtonSprite(ButtonSprite const &buttonSprite) :
 _defaultName(buttonSprite._defaultName), _selected(buttonSprite._selected), _clicked(buttonSprite._clicked), _state(ButtonSprite::DEFAULT)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());

  this->_defaultSprite = gameState->getSprite(_defaultName);
  this->_selectedSprite = gameState->getSprite(_selected);
  this->_clickedSprite = gameState->getSprite(_clicked);
}

void ButtonSprite::updateState(enum ButtonSprite::eState state)
{
  this->_state = state;
}

void ButtonSprite::draw(int x, int y, double elapseTime)
{
  if (_state == DEFAULT && this->_defaultSprite)
    this->_defaultSprite->draw(x, y, elapseTime);
  else if (_state == SELECTED && this->_selectedSprite)
    this->_selectedSprite->draw(x, y, elapseTime);
  else if (_state == CLICKED && this->_clickedSprite)
    this->_clickedSprite->draw(x, y, elapseTime);
}

int ButtonSprite::getWidth() const
{
  unsigned int defaultSp = (this->_defaultSprite) ? (this->_defaultSprite->getWidth()) : (0);
  unsigned int selectedSp = (this->_selectedSprite) ? (this->_selectedSprite->getWidth()) : (0);
  unsigned int clickedSp = (this->_clickedSprite) ? (this->_clickedSprite->getWidth()) : (0);

  if (defaultSp > selectedSp &&
      defaultSp > clickedSp)
    return (defaultSp);
  else if (clickedSp > defaultSp &&
	   clickedSp > selectedSp)
    return (clickedSp);
  return (selectedSp);
}

int ButtonSprite::getHeight() const
{
  unsigned int defaultSp = (this->_defaultSprite) ? (this->_defaultSprite->getHeight()) : (0);
  unsigned int selectedSp = (this->_selectedSprite) ? (this->_selectedSprite->getHeight()) : (0);
  unsigned int clickedSp = (this->_clickedSprite) ? (this->_clickedSprite->getHeight()) : (0);

  if (defaultSp > selectedSp &&
      defaultSp > clickedSp)
    return (defaultSp);
  else if (clickedSp > defaultSp &&
	   clickedSp > selectedSp)
    return (clickedSp);
  return (selectedSp);
}
