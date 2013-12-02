#pragma once

#include <string>
#include <chrono>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

/*!
	\brief Utility to manipulate time
*/
class NET_DLLREQ Clock
{
public:
	/*!
		\brief Construct an empty clock
	*/
	Clock();
	~Clock();

	/*!
	 	\brief Resume the clock
	*/
	void	play();
	/*!
	 	\brief Pause the clock
	*/
	void	pause();
	/*!
	 	\brief Update the clock
	*/
	void	update();
	/*!
	 	\brief Reset the clock
	*/
	void	reset();
	/*!
	 	\brief Check if the clock is paused
	 	\return true if paused, false otherwise 
	*/
	bool	isPaused() const;
	/*!
	 	\brief Get the number of miliseconds since last update
	 	\return the number of miliseconds since last update 
	*/
	uint64_t	getElapsedTime() const;
	/*!
	 	\brief Get the number of miliseconds since EPOCH
	 	\details EPOCH is January, 1st, 1970 at 00:00
	 	\return the number of miliseconds since EPOCH
	*/
	static uint64_t getMsSinceEpoch();
	/*!
	 	\brief Get the current date in a string
	 	\return a string containing the formatted time 
	*/
	static std::string getTimeInStr(std::string const &format = "%c");
	/*!
	 	\brief OS agnostic sleep
	 	\param ms number of miliseconds to sleep
	*/
	static void			sleep(int ms);

private:
	bool											_paused;
#if defined (_WIN32)
	typedef std::chrono::system_clock clock;
#else
	typedef std::chrono::steady_clock clock;
#endif
	std::chrono::time_point<clock>					_clock;
};

NET_END_NAMESPACE
