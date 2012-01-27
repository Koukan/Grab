#pragma once

namespace Resource
{
  enum type {
    P1 = 0,
    P2,
    P3,
    P4,
    SINGLE_MONSTER,
	BOMB_MONSTER,
	SINUSOIDAL_MONSTER,
	METROID_MONSTER,
	BOSS_METROID,
	RANDOM_MONSTER,
	TRON_MONSTER,
	DEFAULT_SHOT,
	BOSS_SHOT,
	ANIMATED_SHOT,
	SHOT,
	SHOOT
  };

  struct Monster
  {
	  const char *sprite;
	  int life;
  };

  extern const Monster monsters[];
}
