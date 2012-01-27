#pragma once

#include "GameState.hpp"
#include "GUITextBox.hpp"

class GSOptions : public GameState
{
public:
  GSOptions();
  ~GSOptions();

  void	onStart();

  void returnMenu();

private:
  GUITextBox<GSOptions> *_name;
  GUITextBox<GSOptions> *_ip;
  GUITextBox<GSOptions> *_port;
};
