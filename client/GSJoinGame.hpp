#pragma once

#include "GameState.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"

class GSJoinGame : public Core::GameState
{
public:
  GSJoinGame();
  ~GSJoinGame();

  void	onStart();
  bool	handleCommand(Core::Command const &command);

private:
  void	returnMainMenu();
  void	refresh();

  GUIVLayout *_vlayout;
  GUIHLayout *_hlayout;
  Core::ButtonSprite const *_sprite;
  Core::ButtonSprite const *_longbutton;
  bool _isListed;
};
