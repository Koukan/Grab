#include "Loading.hpp"
#include "Game.hpp"

Loading::Loading() : GameState("Loading")
{
}

Loading::~Loading()
{}

void	Loading::escape(const CL_InputEvent &event)
{
  Game::get().popState();
  Game::get().quit();
}

void	Loading::click(const CL_InputEvent &event)
{
  
}

void	Loading::update()
{

}


void	Loading::on_connected()
{
	
}

void	Loading::on_disconnected()
{
	
}

void	Loading::on_event_received(const CL_NetGameEvent &e)
{
	//cl_log_event("events", "Server sent event: %1", e.to_string());
	if (!game_events.dispatch(e))
	{
	   //cl_log_event("events", "Unhandled event: %1", e.to_string());
	}
}

void	Loading::arrowEvent(const CL_NetGameEvent &e)
{
  
}

void	Loading::onStart()
{
   this->registerInputCallback(CL_InputEvent::released, *(new CL_Callback_v1<const CL_InputEvent &>(this, &Loading::escape)), CL_InputDevice::keyboard, CL_KEY_ESCAPE);
   this->registerInputCallback(CL_InputEvent::released, *(new CL_Callback_v1<const CL_InputEvent &>(this, &Loading::click)), CL_InputDevice::pointer, CL_MOUSE_LEFT);
   slots.connect(network_client.sig_event_received(), this, &Loading::on_event_received);
   slots.connect(network_client.sig_connected(), this, &Loading::on_connected);
   slots.connect(network_client.sig_disconnected(), this, &Loading::on_disconnected);
   game_events.func_event("Arrow").set(this, &Loading::arrowEvent);
   network_client.connect("127.0.0.1", "4500");
}

