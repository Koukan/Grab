#include "GSSplashScreen.hpp"
#include "RendererManager.hpp"
#include "GSPreload.hpp"
#include "GSMainMenu.hpp"
#include "GameStateManager.hpp"

GSSplashScreen::GSSplashScreen() : Core::GameState("SplashScreen"), _update(false)
{
}

GSSplashScreen::~GSSplashScreen()
{}

void	GSSplashScreen::update(double)
{
	if (_update)
	{
		Core::GameStateManager::get().popState();
		Core::GameStateManager::get().pushState(*new GSPreload);
		Core::GameStateManager::get().pushState(*new GSMainMenu, GameState::NONE);
	}
	_update = true;
}

void	GSSplashScreen::onStart()
{
	this->addGroup("gui", 2);
	this->addGroup("background", 1);
	this->load("resources/xml/splashScreen.xml");
	Core::Sprite *sp = this->getSprite("title");
	sp->setX((VIEWX - sp->getWidth()) / 2);
	sp->setY(400);
	this->addGameObject(sp, "gui");
	sp = this->getSprite("subTitle");
	sp->setX((VIEWX - sp->getWidth()) / 2);
	sp->setY(550);
	this->addGameObject(sp, "gui");
	sp = this->getSprite("screen");
	this->addGameObject(sp, "background");
}
