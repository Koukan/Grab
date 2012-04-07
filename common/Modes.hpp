#pragma once

#include <string>

namespace Modes
{
  enum Mode
  {
    STORY = 0,
    SURVIVAL_SCORING,
    SURVIVAL_HIGHLANDER,
    TRY_AND_RETRY
  };

  struct ModeSettings
  {
    Mode 	mode;
    int 	singleNbLife;
    int 	multiNbLife; // -1 == respawn if another player is still alive
    size_t 	nbCredits;
	std::string name;
  };

  static ModeSettings const	modesList[] = {
    {STORY, 3, -1, 1, "Story"},
    {SURVIVAL_SCORING, 3, 3, 0, "Survival scoring"},
    {SURVIVAL_HIGHLANDER, 3, 3, 0, "Survival Highlander"},
    {TRY_AND_RETRY, 3, -1, 0, "Try and retry"}
  };
}
