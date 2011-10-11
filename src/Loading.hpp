#pragma once
#include <list>
#include "GameState.hpp"
#include "AudioManager.hpp"
#include <ClanLib/network.h>
#include "Font.hpp"
#include "Monster.hpp"
#include "Pacman.hpp"

class Loading : public GameState
{
public:
	Loading();
	~Loading();
	virtual void	onStart();
	virtual	void	update(int elapseTime = 0);

private:
	void			escape(const CL_InputEvent &event);
	void			click(const CL_InputEvent &event);
	void			arrowEvent(const CL_NetGameEvent &e);
	void			on_connected();
	void			on_disconnected();
	void			on_event_received(const CL_NetGameEvent &e);

	CL_NetGameClient	network_client;
	CL_NetGameEventDispatcher_v0 game_events;
	CL_SlotContainer	slots;
};
