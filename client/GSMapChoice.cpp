#include "GSMapChoice.hpp"
#include "RendererManager.hpp"
#include "GUIVLayout.hpp"
#include "GUIList.hpp"
#include "GUIButton.hpp"
#include "GSBindPlayer.hpp"
#include "Game.hpp"

GSMapChoice::GSMapChoice(Modes::Mode mode, int nbPlayers, bool online)
	: Core::GameState("mapChoice", true), _mode(mode), _nbPlayers(nbPlayers), _online(online)
{
}


GSMapChoice::~GSMapChoice()
{
	if (this->_online)
		Game::get().unloadModule("NetworkModule");
}

void		GSMapChoice::onStart()
{
	this->load("resources/xml/intro.xml");

	this->_maps["Map 1"] = "resources/map/map1.xml";
	this->_maps["Map 2"] = "resources/map/map2.xml";

	Core::GUILayout *layout = new GUIVLayout(VIEWX / 2, (VIEWY - 100) / 2, 300, 300, 0);
	layout->setY((VIEWY - layout->getHeight()) / 2);

	Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
	Core::ButtonSprite *leftArrow = new Core::ButtonSprite("left list arrow", "selected left list arrow", "pressed left list arrow");
	Core::ButtonSprite *rightArrow = new Core::ButtonSprite("right list arrow", "selected right list arrow", "pressed right list arrow");

	GUIList<GSMapChoice> *guilist = new GUIList<GSMapChoice>(*this, &GSMapChoice::mapChoice, *leftArrow, *rightArrow, 0);
	for (std::map<std::string, std::string>::iterator it = this->_maps.begin();
		 it != this->_maps.end(); it++)
		 guilist->addElement(*(new GUIButton<GSMapChoice>(*this, &GSMapChoice::createParty, it->first, "buttonFont", *sprite, 0)));
	this->_map = this->_maps.begin()->second;
	layout->insertElementAtEnd(*guilist);

	new GUIButton<GSMapChoice>(*this, &GSMapChoice::createParty, "Next", "buttonFont", *sprite, layout);
	new GUIButton<GSMapChoice>(*this, &GSMapChoice::back, "Back", "buttonFont", *sprite, layout);
}

void		GSMapChoice::mapChoice(Core::GUIElement &elem)
{
	this->_map = this->_maps[static_cast<GUIButton<GSMapChoice> const &>(elem).getName()];
}

void		GSMapChoice::createParty()
{
	Core::GameStateManager::get().pushState(*new GSBindPlayer(this->_mode, this->_map, _nbPlayers, _online));
}

void		GSMapChoice::back()
{
	Core::GameStateManager::get().popState();
}
