#pragma once

#include "GameState.hpp"
#include "GUITextBox.hpp"

class GSOptions : public Core::GameState
{
public:
  GSOptions();
  ~GSOptions();

  void	onStart();

  void 	returnMenu();
  void	fullscreen();
  void	applyResolution();
  void	changeResolution(Core::GUIElement &nb);

private:
  GUITextBox<GSOptions> *_name;
  GUITextBox<GSOptions> *_ip;
  GUITextBox<GSOptions> *_port;
};
