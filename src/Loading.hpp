#pragma once
#include "GameState.hpp"
#include "AudioManager.hpp"
#include <ClanLib/network.h>

class Loading : public GameState
{
public:
	Loading();
	~Loading();
	virtual void	onStart();

private:
	void			escape(const CL_InputEvent &event);

  AudioManager _audioManager;

};
