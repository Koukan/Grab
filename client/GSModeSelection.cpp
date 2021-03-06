#include "GameStateManager.hpp"
#include "GSMainMenu.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "GUIButton.hpp"
#include "ScrollingSprite.hpp"
#include "GSPartySettings.hpp"
#include "GSModeSelection.hpp"
#include "GSMapChoice.hpp"
#include "RendererManager.hpp"

GSModeSelection::GSModeSelection()
  : Core::GameState("modeSelection", true)
{}

GSModeSelection::~GSModeSelection()
{}

void	GSModeSelection::onStart()
{
  this->addGroup("background", 1, 50000001, 59999999);

  // load xml
  this->load("resources/xml/intro.xml");

  // add gui
  Core::GUILayout *layout = new GUIVLayout(VIEWX / 2,
	  (VIEWY - 300) / 2,
	  300, 300, 10, 100, "up arrow", "down arrow");
  Core::Sprite *sp = this->getSprite("logo");
  sp->setX((VIEWX - sp->getWidth()) / 2);
  sp->setY(50);
  this->addGameObject(sp, "gui");
  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::story, "Story", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::survivalScoring, "Survival Scoring", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::survivalHighlander, "Survival Highlander", "buttonFont", *sprite, layout);
  //  new GUIButton<GSModeSelection>(*this, &GSModeSelection::tryAndRetry, "Try and Retry", "buttonFont", *sprite, layout);
  new GUIButton<GSModeSelection>(*this, &GSModeSelection::back, "Back", "buttonFont", *sprite, layout);
}

void	GSModeSelection::back()
{
  Core::GameStateManager::get().popState();
}

void	GSModeSelection::story()
{
  Core::GameState *state = new GSPartySettings(Modes::STORY); //tmp, waiting for map selection
  Core::GameStateManager::get().pushState(*state);
}

void	GSModeSelection::survivalScoring()
{
  Core::GameState *partySettings = new GSPartySettings(Modes::SURVIVAL_SCORING);
  Core::GameStateManager::get().pushState(*partySettings);
}

void	GSModeSelection::survivalHighlander()
{
  Core::GameState *partySettings = new GSPartySettings(Modes::SURVIVAL_HIGHLANDER);
  Core::GameStateManager::get().pushState(*partySettings);
}

void	GSModeSelection::tryAndRetry()
{
  Core::GameState *partySettings = new GSPartySettings(Modes::TRY_AND_RETRY);
  Core::GameStateManager::get().pushState(*partySettings);
}
