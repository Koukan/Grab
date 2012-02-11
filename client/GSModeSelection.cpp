#include "GameStateManager.hpp"
#include "GSMainMenu.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "GUIButton.hpp"
#include "ScrollingSprite.hpp"
#include "GSPartySettings.hpp"
#include "GSModeSelection.hpp"

GSModeSelection::GSModeSelection()
  : GameState("modeSelection")
{}

GSModeSelection::~GSModeSelection()
{}

void	GSModeSelection::onStart()
{
  this->addGroup("background", 1, 50000001, 59999999);

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
  layout->setY((768 - layout->getHeight()) / 2);
  Sprite *sp = this->getSprite("logo");
  sp->setX(280);
  sp->setY(100);
  this->addGameObject(sp, "gui", 20);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::story, "Story", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::survivalScoring, "Survival Scoring", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::survivalHighlander, "Survival Highlander", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::tryAndRetry, "Try and Retry", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::back, "Back", "buttonFont", *sprite, layout);
}

void	GSModeSelection::back()
{
  GameStateManager::get().popState();
}

void	GSModeSelection::story()
{
  GameState *partySettings = new GSPartySettings(Modes::STORY); //tmp, waiting for map selection
  GameStateManager::get().pushState(*partySettings);
}

void	GSModeSelection::survivalScoring()
{
  GameState *partySettings = new GSPartySettings(Modes::SURVIVAL_SCORING);
  GameStateManager::get().pushState(*partySettings);
}

void	GSModeSelection::survivalHighlander()
{
  GameState *partySettings = new GSPartySettings(Modes::SURVIVAL_SCORING);
  GameStateManager::get().pushState(*partySettings);
}

void	GSModeSelection::tryAndRetry()
{
}
