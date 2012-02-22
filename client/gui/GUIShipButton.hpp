#pragma once

#include "GUIButton.hpp"

template <typename T>
class GUIShipButton : public GUIButton<T>
{
public:
	GUIShipButton(unsigned int shipNb, T &instance, void (T::*func)(), std::string const &name,
		std::string const &font, Core::ButtonSprite const &sprite, Core::GUILayout *layout,
		Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
		: GUIButton<T>(instance, func, name, font, sprite, layout, playerType), _shipNb(shipNb)
	{
	}

	~GUIShipButton()
	{
	}

	unsigned int getShipNb() const
	{
		return (this->_shipNb);
	}

private:
	unsigned int _shipNb;
};